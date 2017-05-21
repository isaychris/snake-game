// ===============================================================
// Author: https://github.com/isaychris
// Date: 1/16/17
//
// Project: snake game split
// Version: 0.8
//
// TODO: 
// - snake body [done]
//================================================================
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>
#include <windows.h>

#include "game.h"

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
	my_snake.move();
	collisionCheck();
}

// draws the screen
void game::render() {
	using namespace std;

	// draws the grid
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			cout << map.grid[i][j];
		}
		cout << endl;
	}
	// draws the text
	cout << " Use WASD to control the s" << endl;
	cout << " - score: " << score << endl;
	cout << " - s: [" << my_snake.head->x << ", " << my_snake.head->y << "] " << endl;
	cout << " - f: [" << my_fruit.x << ", " << my_fruit.y << "] " << endl;
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
	if (my_snake.head->x == my_fruit.x && my_snake.head->y == my_fruit.y) {
		score++;

		// if collision, fruit deleted and new one created.
		my_fruit.createFruit();

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
			map.grid[i][0] = block;
			map.grid[0][j] = block;
			map.grid[i][COLUMN - 1] = block;
			map.grid[ROW - 1][j] = block;
		}
	}
}

// hides the blinking cursor in console
void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

// refreshes display
void refresh()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;

	Position.X = 0;
	Position.Y = 0;

	SetConsoleCursorPosition(hOut, Position);
}

// initiates the s game
void game::init() {

	fillBorders();
	my_fruit.createFruit();

	//creates snake body
	my_snake.head = new node;
	my_snake.head->part = '<';
	my_snake.head->x = ROW / 2;
	my_snake.head->y = COLUMN / 2;
	my_snake.head->next = nullptr;
	map.draw(my_snake.head->x, my_snake.head->y, my_snake.head->part);

	//sets the game to running.
	running = true;
}

// snake game driver
int main() {
	game g;

	hidecursor();
	g.init();


	while (g.running) {
		g.processInput();
		g.update();
		g.render();
		refresh();
	}
}

