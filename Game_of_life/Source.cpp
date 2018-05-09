#include<iostream>
#include "matrix.h"
#include<stdlib.h>
#include<Windows.h>

#include "newGame.h"
#include "By_Queue.h"
using namespace std;



void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void move_cursor_to_zero() {
	// I'M USING THIS TO TRY TO REDUCE THE CONSOLE FLICKERING ON EVERY SCREEN REFRESH
	// https://stackoverflow.com/questions/34842526/update-console-without-flickering-c/34843392?noredirect=1#comment57465505_34843392    might wanna check this ???
	// http://www.cplusplus.com/forum/articles/10515/
	// OR COULD TRY   DOUBLE BUFFERING   TOO ...

	// code from cs2 final project lol
	//change console cursor's position
	static CONSOLE_SCREEN_BUFFER_INFO csbi;
	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), csbi.dwCursorPosition);
}

int main()
{
	hidecursor();
	newGame *game = new By_Queue(30, 40);

	game->set_state_random();
	for (int i = 0; i < 100; i++) {
		//system("CLS");
		move_cursor_to_zero();
		game->print();
		game->iterate();
		Sleep(300);
	}


	return 0;
}

