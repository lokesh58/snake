#ifndef SNAKE_H
#define SNAKE_H

#include <memory>

class Snake {
	public:
		Snake();
		Snake(int x, int y);
		~Snake();
		void addTail();
		void move(int dx, int dy);

		int getX() const;
		int getY() const;

	private:
		void setPos(int x, int y);

		int _x, _y;
		std::unique_ptr<Snake> _prev;
};

#endif //SNAKE_H
