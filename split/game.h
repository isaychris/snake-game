#pragma once
#include "fruit.h"
#pragma once
#include "snake.h"
#include "grid.h"

class game {

public:
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