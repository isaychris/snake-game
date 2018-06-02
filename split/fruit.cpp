#include <time.h> 
#include <stdlib.h>
#include "fruit.h"
#include "game.h"

// generates a new fruit
void fruit::createFruit(game &game) {
	srand((unsigned)time(nullptr));

	x = rand() % (ROW - 2) + 1;
	y = rand() % (COLUMN - 2) + 1;
	game.my_map.draw(x, y, 'x');
}
