#include "../headers/Game.h"
#include <iostream>
#include <conio.h>

namespace {
	constexpr int width = 200;
	constexpr int height = 200;
}

Game::Game() : head(nullptr), _ux(0, width), _uy(0, height) {
	//ctor
}

Game::~Game() {
	//dtor
}

void Game::play() {
	//TODO
}

void Game::generateFood() {
	do {
		foodX = getRandomX();
		foodY = getRandomY();
	} while (head->checkTail(foodX, foodY));
}

void Game::reset() {
	head = std::make_unique<Snake>(width/2, height/2);
	generateFood();
}

void Game::gameLoop() {
	bool gameOver = false;

	while (!gameOver) {
		input();
		display();
	}
}

void Game::input() {
	if (kbhit()) {
		switch(getch()) {
			case 'a':
			case 'A':
				head->move(-1, 0);
				break;
			case 'd':
			case 'D':
				head->move(1, 0);
				break;
			case 'w':
			case 'W':
				head->move(0, -1);
				break;
			case 's':
			case 'S':
				head->move(0, 1);
				break;
			default:
				break;
		}
	}
}

void Game::display() {

}

int Game::getRandomX() {
	return _ux(_e);
}

int Game::getRandomY() {
	return _uy(_e);
}
