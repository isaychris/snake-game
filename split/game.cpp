#include <iostream>
#include <string>
#include <conio.h>
#include "game.h"

// initiates the game
void game::init() {

	fillBorders();
	my_fruit = new fruit();
	my_fruit->createFruit(*this);

	//creates snake body
	my_snake.head = new node;
	my_snake.head->part = '<';
	my_snake.head->x = ROW / 2;
	my_snake.head->y = COLUMN / 2;
	my_snake.head->next = nullptr;
	my_map.draw(my_snake.head->x, my_snake.head->y, my_snake.head->part);

	//sets the game to running.
	running = true;
}

// checks for directional input
void game::processInput() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			my_snake.face = direction::UP;
			break;
		case 'd':
			my_snake.face = direction::RIGHT;
			break;
		case 's':
			my_snake.face = direction::DOWN;
			break;
		case 'a':
			my_snake.face = direction::LEFT;
			break;
		}
	}
}

// updates the game
void game::update() {
	my_snake.move(*this);
	collisionCheck();
}

// draws the screen
void game::render() {
	using namespace std;

	// draws the grid
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			cout << my_map.grid[i][j];
		}
		cout << endl;
	}
	// draws the text
	cout << " Use WASD to control the snake" << endl;
	cout << " - score: " << score << endl;
	cout << " - snake: [" << my_snake.head->x << ", " << my_snake.head->y << "] " << endl;
	cout << " - fruit: [" << my_fruit->x << ", " << my_fruit->y << "] " << endl;
	cout << " ";

	// draws the length of the snake
	node * root = my_snake.head;
	while (root != nullptr) {
		cout << root->part;
		root = root->next;
	}
}

//checks for collisions in regards to head position
void game::collisionCheck() {

	//fruit collision
	if (my_snake.head->x == my_fruit->x && my_snake.head->y == my_fruit->y) {
		score++;

		// if collision, fruit deleted and new one created.
		my_fruit = new fruit();
		my_fruit->createFruit(*this);

		//snake body created
		node * body = new node();
		body->part = 'o';
		body->next = nullptr;

		//snake body set to the back of snake;
		node *root = my_snake.head;
		while (root->next != nullptr) {
			root = root->next;
		}
		root->next = body;
	}

	//body collision
	//compares the head positions to its body poisitions
	//if collission, game over.
	node * root = my_snake.head;
	root = root->next;
	while (root != nullptr) {
		if (my_snake.head->x == root->x && my_snake.head->y == root->y) {
			running = false;
			break;
		}
		root = root->next;
	}

	//border collision
	//if head collides with border, game over.
	if (my_snake.head->x <= 0 || my_snake.head->x > ROW - 2 || my_snake.head->y <= 0 || my_snake.head->y > COLUMN - 2) {
		running = false;
	}

}

//dills out the borders
void game::fillBorders() {
	const char block = (char(219));

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			my_map.grid[i][0] = block;
			my_map.grid[0][j] = block;
			my_map.grid[i][COLUMN - 1] = block;
			my_map.grid[ROW - 1][j] = block;
		}
	}
}