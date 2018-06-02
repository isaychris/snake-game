#include "fruit.h"
#include <time.h> 
#include <stdlib.h>
#include "grid.h"

// generates a new fruit
void fruit::createFruit() {
	srand((unsigned)time(nullptr));

	int x = rand() % (ROW - 2) + 1;
	int y = rand() % (COLUMN - 2) + 1;

	my_map.draw(x, y, 'x');
}
