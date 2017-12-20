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
	if (_prev == nullptr) {
		_prev = std::make_unique<Snake>(_x, _y+1);
	} else if (_prev->_prev != nullptr) {
		_prev->addTail();
	} else {
		_prev->_prev = std::make_unique<Snake>(2*(_prev->getX()) - getX(), 2*(_prev->getY()) - getY());
	}
}

void Snake::move(int dx, int dy) {
	if (_prev != nullptr) {
		_prev->setPos(_x, _y);
	}
	_x += dx;
	_y += dy;
}

void Snake::setPos(int x, int y) {
	if (_prev != nullptr) {
		_prev->setPos(_x, _y);
	}
	_x = x, _y = y;
}

int Snake::getX() const {
	return _x;
}

int Snake::getY() const {
	return _y;
}
