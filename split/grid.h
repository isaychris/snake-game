#pragma once

const int ROW = 15;
const int COLUMN = 30;

class map {
public:
	char grid[ROW][COLUMN] = { ' ' };

	void draw(int x, int y, char c)
	{
		grid[x][y] = c;
	}
};
