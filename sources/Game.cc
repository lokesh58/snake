#include "../headers/Game.h"

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

void Game::reset() {
	head = std::make_unique<Snake>(width/2, height/2);
	
}

void Game::gameLoop() {
	//TODO
}

int Game::getRandomX() {
	return _ux(_e);
}

int Game::getRandomY() {
	return _uy(_e);
}
