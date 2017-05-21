#pragma once
#include "fruit.h"
#include "snake.h"

const int ROW = 15;
const int COLUMN = 30;
class snake;
class fruit;

class game {

public:
	bool running;

	void init();
	void processInput();
	void update();
	void render();

private:
	snake my_snake;
	fruit my_fruit;

	int score = 0;

	void collisionCheck();
	void fillBorders();
};