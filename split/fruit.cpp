#include "fruit.h"
#include <time.h> 
#include "game.h"
#include <stdlib.h>

// generates a new fruit
void fruit::createFruit() {
	srand((unsigned)time(nullptr));

	int x = rand() % (ROW - 2) + 1;
	int y = rand() % (COLUMN - 2) + 1;

	map.draw(x, y, 'x');
}
