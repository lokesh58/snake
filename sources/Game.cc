#include "../headers/Game.h"
#include <iostream>

namespace {
	constexpr int width = 200;
	constexpr int height = 200;
}

Game::Game() : head(nullptr), _ux(0, width), _uy(0, height), dir(none), gameOver(false) {
	int choice;
	do {
		std::cout << "----------WELCOME--TO--SNAKE--GAME------------\n";
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
	dir = none;
	gameOver = false;
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
			case 75:
				if (dir != right) {
					dir = left;
				}
				break;
			case 77:
				if (dir != left) {
					dir = right;
				}
				break;
			case 72:
				if (dir != down) {
					dir = up;
				}
				break;
			case 80:
				if (dir != up) {
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
	//TODO
}

void Game::display() {
	//TODO
}

int Game::getRandomX() {
	return _ux(_e);
}

int Game::getRandomY() {
	return _uy(_e);
}
