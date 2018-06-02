// ===============================================================
// Author: https://github.com/isaychris
// Date: 6/2/18
//
// Project: snake game split
// Version: 1.0.0
//
//================================================================
#include <chrono>
#include <thread>
#include <windows.h>
#include "game.h"

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
