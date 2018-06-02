#pragma once
#include "grid.h"

enum class direction { UP, RIGHT, DOWN, LEFT, NONE };
class game;

//snake structure
struct node {
	int x;
	int y;
	char part;
	node *next;
};

class snake {
public:
	node * head;
	direction face = direction::NONE;

	void move(game& g);
	void updateBody(game &g, node * tmp);
};