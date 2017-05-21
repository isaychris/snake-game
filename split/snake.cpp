#include "snake.h"
#include "game.h"

//moves the snake
void snake::move() {
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
		map.draw(head->x, head->y, '^');
		break;
	case direction::DOWN:
		head->x++;
		map.draw(head->x, head->y, 'v');
	case direction::RIGHT:
		head->y++;;
		map.draw(head->x, head->y, '>');
		break;
	case direction::LEFT:
		head->y--;
		map.draw(head->x, head->y, '<');
		break;
	}

	map.draw(pre->x, pre->y, ' ');

	updateBody(pre);
}

// updates the body of the snake
void snake::updateBody(node* pre) {
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
		map.draw(root->x, root->y, root->part);
		pre->x = x;
		pre->y = y;
		root = root->next;
	}

	map.draw(x, y, ' ');
}
