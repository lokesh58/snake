#ifndef GAME_H
#define GAME_H

#include <utility>
#include <random>
#include "Snake.h"

enum Direction {
	none, up, down, left, right
};

class Game {
	public:
		Game();
		~Game();
		void play();

	private:
		void generateFood();
		void reset();
		void gameLoop();
		void input();
		void logic();
		void display();

		int getRandomX();
		int getRandomY();

		std::unique_ptr<Snake> head;
		int foodX, foodY;
		Direction dir;
		bool gameOver;

		std::uniform_int_distribution<int> _ux, _uy;
		std::default_random_engine _e;
};

#endif //GAME_H
