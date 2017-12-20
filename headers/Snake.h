#ifndef SNAKE_H
#define SNAKE_H

#include <memory>
#include <utility>

class Snake {
	using Direction = std::pair<int, int>;

	public:
		Snake();
		Snake(int x, int y);
		~Snake();
		void addTail();
		void move(Direction delta);

	private:
		void setPos(int x, int y);

		int _x, _y;
		std::unique_ptr<Snake> _prev;
};

#endif //SNAKE_H
