#include "../headers/Game.h"
#include <iostream>
#include <cstdlib>

namespace {
	constexpr int width = 20;
	constexpr int height = 20;
}

#ifdef _WIN32
	const char* command = "cls";
#else
	const char* command = "clear";
#endif //_WIN32

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
	gameLoop();
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
	}
}

void Game::input() {
	char ch;
	if ((ch = std::cin.get())/*if a key is hit*/) {
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
