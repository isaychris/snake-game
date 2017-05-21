#pragma once
enum class direction { UP, RIGHT, DOWN, LEFT, NONE };

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

	void move();
	void updateBody(node * tmp);
};