#pragma once
#include "game.h"

class map {
public:
	char grid[ROW][COLUMN] = { ' ' };

	void draw(int x, int y, char c) {
		grid[x][y] = c;
	}

} map;