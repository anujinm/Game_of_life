#include<iostream>
#include<stdlib.h>
#include<Windows.h>

#include "matrix.h"
#include "newGame.h"
#include "By_Queue.h"
#include "By_Generation.h"
//using namespace std;
#include "welcome_screen.h"



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
	static HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(consoleHandle, csbi.dwCursorPosition);
}

int main()
{
	system("cls");
	hidecursor();
	welcome::start_screen();

	newGame *game;
	int choice = welcome::choose_what_to_do();
	if (choice==1)
		game = new newGame(30, 40);
	else if (choice == 2)
		game = new By_Generation(30, 40);
	else if (choice==3)
		game = new By_Queue(30, 40);

	/* couple options to try out 
	uncomment one of these and comment out the rest */

	//game->set_state_1();
	//game->set_state_full();
	game->set_state_random();

	for (int i = 0; i < 100; i++) {
		//system("CLS");
		move_cursor_to_zero();
		game->print();
		game->iterate();
		Sleep(300);
	}

	delete game; game = NULL;

	return 0;
}

