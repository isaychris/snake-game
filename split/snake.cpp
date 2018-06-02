#include "snake.h"
#include "grid.h"
#include "game.h"

//moves the snake
void snake::move(game &g) {
	//current position before moving,
	//used for passing into updatebody();
	node *pre = new node;
	pre->part = head->part;
	pre->x = head->x;
	pre->y = head->y;

	// to update display, erase current position
	// and update head position.

	switch (face) {
	case direction::UP:
		head->x--;
		g.my_map.draw(head->x, head->y, '^');
		break;
	case direction::DOWN:
		head->x++;
		g.my_map.draw(head->x, head->y, 'v');
		break;
	case direction::RIGHT:
		head->y++;;
		g.my_map.draw(head->x, head->y, '>');
		break;
	case direction::LEFT:
		head->y--;
		g.my_map.draw(head->x, head->y, '<');
		break;
	}

	g.my_map.draw(pre->x, pre->y, ' ');

	updateBody(g, pre);
}

// updates the body of the snake
void snake::updateBody(game & g, node* pre) {
	int x = 0;
	int y = 0;

	// sets the prev position to its current.
	node * root = head;
	root = root->next;
	while (root != nullptr) {
		x = root->x;
		y = root->y;
		root->x = pre->x;
		root->y = pre->y;
		g.my_map.draw(root->x, root->y, root->part);
		pre->x = x;
		pre->y = y;
		root = root->next;
	}

	g.my_map.draw(x, y, ' ');
}
