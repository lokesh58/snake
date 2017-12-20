#ifndef GAME_H
#define GAME_H

#include <utility>
#include "Snake.h"

class Game {
	public:
		Game();
		~Game();
		void play();

	private:
		void reset();
		void gameLoop();

		std::unique_ptr<Snake> head;
};

#endif //GAME_H
