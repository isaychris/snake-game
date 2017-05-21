// ===============================================================
// Author: https://github.com/isaychris
// Date: 1/16/17
//
// Project: snake game
// Version: 0.8.1
//
// TODO: 
// - snake body [done]
//
//================================================================
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <random>
#include <conio.h>
#include <windows.h>

const size_t ROW = 15;
const size_t COLUMN = 30;
enum class Direction { UP, DOWN, LEFT, RIGHT, NONE };

class Game;

//snake structure
struct node {
	int x;
	int y;
	char part;
	node *next;
};


// the class for snake game;
class Game {
public:
	void processInput();
	void draw();
	void update();
	void init();
	bool running;

	char grid[ROW][COLUMN] = { ' ' };

private:

	node * head;
	Fruit apple;
	Direction face = Direction::NONE;

	int score = 0;

	void move();
	void collisionCheck();
	void updateBody(node * tmp);
	void fillBorders();
};

// fruit structure
class Fruit {
public:
	Game g;
	void set(Game &a) {
		g = a;
	}
	int x, y;

	void createFruit();
};

// generates a new fruit
void Fruit::createFruit() {
	std::mt19937 mt;
	mt.seed(time(nullptr));

	x = mt() % (ROW - 2) + 1;
	y = mt() % (COLUMN - 2) + 1;
	g.grid[x][y] = 'x';

}

// checks for directional input
void Game::processInput() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			face = Direction::UP;
			break;
		case 'd':
			face = Direction::RIGHT;
			break;
		case 's':
			face = Direction::DOWN;
			break;
		case 'a':
			face = Direction::LEFT;
			break;
		}
	}
}


// updates the body of the snake
void Game::updateBody(node* pre) {
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
		grid[root->x][root->y] = root->part;
		pre->x = x;
		pre->y = y;
		root = root->next;
	}

	grid[x][y] = ' ';

}

//moves the snake
void Game::move() {

	//current position before moving,
	//used for passing into updatebody();
	node *pre = new node;
	pre->part = head->part;
	pre->x = head->x;
	pre->y = head->y;

	// to update display, erase current position
	// and update head position.

	if (face == Direction::UP) {
		grid[head->x][head->y] = ' ';
		head->x--;
		grid[head->x][head->y] = '^';
	}

	else if (face == Direction::DOWN) {
		grid[head->x][head->y] = ' ';
		head->x++;
		grid[head->x][head->y] = 'v';
	}

	else if (face == Direction::RIGHT) {
		grid[head->x][head->y] = ' ';
		head->y++;;
		grid[head->x][head->y] = '>';
	}

	else if (face == Direction::LEFT) {
		grid[head->x][head->y] = ' ';
		head->y--;
		grid[head->x][head->y] = '<';
	}

	updateBody(pre);
}

// updates the game
void Game::update() {
	move();
	collisionCheck();
}

// draws the screen
void Game::draw() {
	using namespace std;

	// draws the grid
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			cout << grid[i][j];
		}
		cout << endl;
	}

	// draws the text
	cout << " Use WASD to control the snake" << endl;
	cout << " - score: " << score << endl;
	cout << " - snake: [" << head->x << ", " << head->y << "] " << endl;
	cout << " - fruit: [" << apple.x << ", " << apple.y << "] " << endl;
	cout << " ";

	// draws the length of the snake
	node * root = head;
	while (root != nullptr) {
		cout << root->part;
		root = root->next;
	}
}

//checks for collisions in regards to head position
void Game::collisionCheck() {

	//fruit collision
	if (head->x == apple.x && head->y == apple.y) {
		score++;

		// if collision, fruit deleted and new one created.
		apple.createFruit();

		//snake body created
		node * body = new node();
		body->part = 'o';
		body->next = nullptr;

		//snake body set to the back of snake;
		node *root = head;
		while (root->next != nullptr) {
			root = root->next;
		}
		root->next = body;

	}

	//body collision
	//compares the head positions to its body poisitions
	//if collission, game over.
	node * root = head;
	root = root->next;
	while (root != nullptr) {
		if (head->x == root->x && head->y == root->y) {
			running = false;
			break;
		}
		root = root->next;

	}

	//border collision
	//if head collides with border, game over.
	if (head->x <= 0 || head->x > ROW - 2 || head->y <= 0 || head->y > COLUMN - 2) {
		running = false;
	}

}

//dills out the borders
void Game::fillBorders() {
	for (int i = 0; i < COLUMN; i++) {
		grid[0][i] = char(219);
	}

	for (int i = 0; i < COLUMN; i++) {
		grid[ROW - 1][i] = char(219);
	}

	for (int i = 0; i < ROW; i++) {
		grid[i][0] = char(219);
	}
	for (int i = 0; i < ROW; i++) {
		grid[i][COLUMN - 1] = char(219);
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

	std::this_thread::sleep_for(std::chrono::milliseconds(30));

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;

	Position.X = 0;
	Position.Y = 0;

	SetConsoleCursorPosition(hOut, Position);
}

// initiates the snake game
void Game::init() {
	srand((unsigned)time(nullptr));
	fillBorders();
	apple.set(*this);
	apple.createFruit();

	//creates snake body
	head = new node;
	head->part = '<';
	head->x = ROW / 2;
	head->y = COLUMN / 2;
	head->next = nullptr;
	grid[head->x][head->y] = head->part;

	//sets the game to running.
	running = true;
}

// snake game driver
int main() {
	Game g;
	hidecursor();
	g.init();


	while (g.running) {
		g.processInput();
		g.update();
		g.draw();
		refresh();
	}
}