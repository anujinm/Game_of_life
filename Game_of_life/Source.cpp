/*
	Anujin Munkhbat , Amon Ratna Sthapit
	Simulation of Conway's Game of Life with some interesting modifications.
*/

#include<iostream>
#include<stdlib.h>
#include<Windows.h>

#include "matrix.h"
#include "newGame.h"
#include "By_Queue.h"
#include "By_Generation.h"
#include "welcome_screen.h"



void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

/*
* change console cursor's position
-- https://stackoverflow.com/questions/34842526/update-console-without-flickering-c/34843392?noredirect=1#comment57465505_34843392
-- http://www.cplusplus.com/forum/articles/10515/
*/
void move_cursor_to_zero() {
	static CONSOLE_SCREEN_BUFFER_INFO csbi;
	static HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(consoleHandle, csbi.dwCursorPosition);
}

/*
* move and resize console window
-- https://stackoverflow.com/questions/25912721/set-console-window-size-on-windows
-- https://stackoverflow.com/questions/21238806/how-to-set-output-console-width-in-visual-studio
*/
void resize_console() {
	HWND console_window = GetConsoleWindow();
	RECT r;
	GetWindowRect(console_window, &r); //stores the console's current dimensions

	if (console_window != NULL) {
		MoveWindow(console_window, r.left, r.top, 1000, 650, TRUE);   
	}
}

int main()
{
	// console stuff
	resize_console();
	system("cls");
	hidecursor();

	
	// start
	welcome::start_screen();

	newGame *game;
	int choice = welcome::choose_what_to_do();

	if (choice == 1)
		game = new newGame(30, 40);
	else if (choice == 2) {
		game = new By_Generation(30, 40, welcome::ask_wait_rate());
	}
	else if (choice == 3) {
		game = new By_Queue(30, 40, welcome::ask_res_rate());
	}



	/* couple options to try out 
	uncomment one of these and comment out the rest */

	//game->set_state_1();
	//game->set_state_full();
	game->set_state_random();

	for (int i = 0; i < 1000; i++) {
		///system("CLS");
		move_cursor_to_zero();
		game->print();
		game->iterate();
		//show_stats();
		Sleep(100);
	}



	delete game; game = NULL;

	return 0;
}

