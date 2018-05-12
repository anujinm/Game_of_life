#pragma once

#include <iostream>


namespace welcome {

	static void start_screen() {
		//ascii
		//http://patorjk.com/software/taag/#p=display&f=Standard&t=START
		//mouse click
		//https://stackoverflow.com/questions/6285270/how-can-i-get-the-mouse-position-in-a-console-program
		//https://stackoverflow.com/questions/11391262/the-meaning-of-enable-processed-input-in-setconsolemode-flags
		//https://docs.microsoft.com/en-us/windows/console/reading-input-buffer-events

		//IF NOT WORKING, TRY:
		/*Opening command-prompt and right-clicking on its title-bar and then clicking 'Defaults'
			A Dialog box would appear, titled 'Console Windows Properties'. There in Options tab, under Edit Options sub-heading, you would find 'Quick Edit Mode' checkbox!
			The problem was being caused by this 'Quick Edit Mode' option which was enabled(checkbox is checked) by default on my Windows 10. And in this enabled status, this 'Quick Edit Mode' was consuming all the Mouse-Events and wasn't dispatching any to my '.exe' .
			When this 'Quick Edit Mode' options' checkbox is unchecked (disabled), then program runs fine as intended/coded in this sample-code here, telling/printing all Mouse events.
			NOTE: The change in 'Console Properties' requires relaunch of the console, to take effect.*/
		

		std::cout << "****************************************" << std::endl;
		std::cout << "*      ____ _____  _    ____ _____     *" << std::endl;
		std::cout << "*     / ___|_   _|/ \\  |  _ \\_   _|    *" << std::endl;
		std::cout << "*     \\___ \\ | | / _ \\ | |_) || |      *" << std::endl;
		std::cout << "*      ___) || |/ ___ \\|  _ < | |      *" << std::endl;
		std::cout << "*     |____/ |_/_/   \\_\\_| \\_\\|_|      *" << std::endl;
		std::cout << "*                                      *" << std::endl;
		std::cout << "****************************************" << std::endl;



		// GET MOUSE CLICK
		HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
		INPUT_RECORD input_record;
		DWORD events;
		COORD coord;

		// current (default) state to restore later
		DWORD fdwSaveOldMode;
		GetConsoleMode(hin, &fdwSaveOldMode);
		// new state
		SetConsoleMode(hin, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

		bool flag = true;
		while (true) {
			// infinite loop to wait for user input
			ReadConsoleInput(hin, &input_record, 1, &events);
			if (input_record.EventType == MOUSE_EVENT) {   // if clicked
				if (input_record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {   // if left-click
					///std::cout << "sup bruh" << std::endl;
					coord.X = input_record.Event.MouseEvent.dwMousePosition.X;   // get positions
					coord.Y = input_record.Event.MouseEvent.dwMousePosition.Y;
					///std::cout << coord.X << std::endl;
					///std::cout << coord.Y << std::endl;
					if (coord.X>0 && coord.X<39 && coord.Y>0 && coord.Y<7) {   // if clicked inside box
						flag = false;
						break;
					}
				}
			}
			//FlushConsoleInputBuffer(hin);
		}
		SetConsoleMode(hin, fdwSaveOldMode);

	}



	static int choose_what_to_do() {
		std::cout << "1. newGame" << std::endl;
		std::cout << "2. By_Generation" << std::endl;
		std::cout << "3. By_Queue" << std::endl;

		int choice;
		std::cin >> choice;

		return choice;
	}

}