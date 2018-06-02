#pragma once
#include "fruit.h"
#include "snake.h"

class game {
public:
	map my_map;
	bool running;

	void init();
	void processInput();
	void update();
	void render();

private:
	snake my_snake;
	fruit * my_fruit;

	int score = 0;

	void collisionCheck();
	void fillBorders();
};