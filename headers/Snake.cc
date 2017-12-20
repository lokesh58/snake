#include "Snake.h"

Snake::Snake() : _x(0), _y(0), _prev(nullptr) {
	//ctor
}

Snake::Snake(int x, int y) : _x(x), _y(y), _prev(nullptr) {
	//ctor
}

Snake::~Snake() {
	//dtor
}

void Snake::addTail() {
	//TODO
}

void Snake::move(Direction delta) {
	if (_prev != nullptr) {
		_prev->setPos(_x, _y);
	}
	_x += delta.first;
	_y += delta.second;
}

void Snake::setPos(int x, int y) {
	if (_prev != nullptr) {
		_prev->setPos(_x, _y);
	}
	_x = x, _y = y;
}
