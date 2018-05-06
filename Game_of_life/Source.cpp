#include<iostream>
#include "matrix.h"
#include<stdlib.h>
#include<Windows.h>

#include "newGame.h"
using namespace std;

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

int main()
{
	hidecursor();
	newGame *game = new newGame(30, 40);

	game->set_state_1();
	for (int i = 0; i < 100; i++) {
		system("CLS");
		game->print();
		game->iterate();
		Sleep(100);
	}


	return 0;
}
