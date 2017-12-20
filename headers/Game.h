#ifndef GAME_H
#define GAME_H

#include <utility>
#include <random>
#include "Snake.h"

class Game {
	public:
		Game();
		~Game();
		void play();

	private:
		void reset();
		void gameLoop();

		int getRandomInt();

		std::unique_ptr<Snake> head;
		int foodX, foodY;

		std::uniform_int_distriubution<int> _uid;
		std::default_random_engine _e;
};

#endif //GAME_H
