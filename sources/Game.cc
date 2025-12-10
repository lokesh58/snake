#include "../headers/Game.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

#ifdef _WIN32
	#include <conio.h>
	#include <windows.h>
#else
	#include <termios.h>
	#include <unistd.h>
	#include <fcntl.h>
#endif

namespace {
	constexpr int width = 20;
	constexpr int height = 20;
}

#ifdef _WIN32
	const char* command = "cls";
#else
	const char* command = "clear";
#endif //_WIN32

// Non-blocking input functions
#ifdef _WIN32
	bool kbhit() {
		return _kbhit();
	}

	char getch() {
		return _getch();
	}
#else
	bool kbhit() {
		int ch = getchar();
		if (ch != EOF) {
			ungetc(ch, stdin);
			return true;
		}
		return false;
	}

	char getch() {
		return getchar();
	}

	void setNonBlockingInput(bool enable) {
		static struct termios old_termios, new_termios;
		static int old_flags;

		if (enable) {
			// Save current terminal settings
			tcgetattr(STDIN_FILENO, &old_termios);
			new_termios = old_termios;

			// Disable canonical mode and echo
			new_termios.c_lflag &= ~(ICANON | ECHO);
			tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

			// Set stdin to non-blocking
			old_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
			fcntl(STDIN_FILENO, F_SETFL, old_flags | O_NONBLOCK);
		} else {
			// Restore original terminal settings
			tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
			fcntl(STDIN_FILENO, F_SETFL, old_flags);
		}
	}
#endif

Game::Game() : head(nullptr), _ux(0, width), _uy(0, height), dir(none), gameOver(false), score(0) {
	int choice;
	do {
		system(command);
		std::cout << "\n----------WELCOME--TO--SNAKE--GAME------------\n";
		std::cout << "1) Play\n";
		std::cout << "2) How to play\n";
		std::cout << "3) Exit\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
			case 1:
				play();
				break;
			case 2:
				std::cout << "\n-------------HELP--------------------\nUse arrow keys to move and eat food\n";
				std::cout << "\nPress any key to return to main menu ...";
				std::cin.ignore(); // Clear any remaining input
				std::cin.get(); // Wait for user input
				break;
			case 3:
				std::cout << "\nThanks for playing :)\n";
				break;
			default:
				std::cout << "Invalid choice!\n";
				break;
		}
	} while (choice != 3);
}

Game::~Game() {
	//dtor
}

void Game::play() {
	reset();

#ifndef _WIN32
	setNonBlockingInput(true);
#endif

	gameLoop();

#ifndef _WIN32
	setNonBlockingInput(false);
#endif
}

void Game::generateFood() {
	do {
		foodX = getRandomX();
		foodY = getRandomY();
	} while (head->checkTail(foodX, foodY));
}

void Game::reset() {
	head = std::make_unique<Snake>(width/2, height/2);
	head->addTail();
	head->addTail();
	dir = none;
	gameOver = false;
	score = 0;
	generateFood();
}

void Game::gameLoop() {
	while (!gameOver) {
		input();
		logic();
		display();

		// Add delay to control game speed (150ms)
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}

void Game::input() {
	if (kbhit()) {
		char ch = getch();
		switch(ch) {
			case 'A':
			case 'a':
				if (dir != right) {
					dir = left;
				}
				break;
			case 'D':
			case 'd':
				if (dir != left) {
					dir = right;
				}
				break;
			case 'W':
			case 'w':
				if (dir != down) {
					dir = up;
				}
				break;
			case 'S':
			case 's':
				if (dir != up && dir != none) {
					dir = down;
				}
				break;
			case 'x':
			case 'X':
				gameOver = true;
				break;
			default:
				break;
		}
	}
}

void Game::logic() {
	//Move
	switch (dir) {
		case up:
			head->move(0, -1);
			break;
		case down:
			head->move(0, 1);
			break;
		case left:
			head->move(-1, 0);
			break;
		case right:
			head->move(1, 0);
			break;
		default:
			break;
	}

	//Eat food
	if (head->getX() == foodX && head->getY() == foodY) {
		head->addTail();
		generateFood();
		score += 10;
	}

	//Condition for getting out
	if ((head->checkTail(head->getX(), head->getY())) || head->getX() < 0 || head->getX() >= width || head->getY() < 0 || head->getY() >= height) {
		gameOver = true;
	}
}

void Game::display() {
	system("clear");
	for (int i = 0; i < width+2; ++i) {
		std::cout << '#';
	}
	std::cout << '\n';

	for (int y = 0; y < height; ++y) {
		std::cout << '#';
		for (int x = 0; x < width; ++x) {
			if (x == head->getX() && y == head->getY()) {
				std::cout << 'O';
			} else if (head->checkTail(x, y)) {
				std::cout << 'o';
			} else if (x == foodX && y == foodY) {
				std::cout << 'F';
			} else {
				std::cout << ' ';
			}
		}
		std::cout << "#\n";
	}

	for (int i = 0; i < width+2; ++i) {
		std::cout << '#';
	}
	std::cout << "\nScore: " << score << '\n';
}

int Game::getRandomX() {
	return _ux(_e);
}

int Game::getRandomY() {
	return _uy(_e);
}
