#pragma once

#include <iostream>



namespace welcome {

	static void draw_start_button(int x) {
		// draw the start button
		if (x==0) {
			std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
			std::cout << "                                    ****************************************" << std::endl;
			std::cout << "                                    *      ____ _____  _    ____ _____     *" << std::endl;
			std::cout << "                                    *     / ___|_   _|/ \\  |  _ \\_   _|    *" << std::endl;
			std::cout << "                                    *     \\___ \\ | | / _ \\ | |_) || |      *" << std::endl;
			std::cout << "                                    *      ___) || |/ ___ \\|  _ < | |      *" << std::endl;
			std::cout << "                                    *     |____/ |_/_/   \\_\\_| \\_\\|_|      *" << std::endl;
			std::cout << "                                    *                                      *" << std::endl;
			std::cout << "                                    ****************************************" << std::endl;
		}
		else if (x==1) {
			std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
			std::cout << "                                 ~** * ****     *   /*****    /**      %*****//~" << std::endl;
			std::cout << "                                    * *  **********/*  ******** ******* *  *" << std::endl;
			std::cout << "                                    *      ____ _____  _    ____ _____     **" << std::endl;
			std::cout << "                                   /      / ___|_   _|/ \\  |  _ \\_   _|      *" << std::endl;
			std::cout << "                                   \\*     \\___ \\ | | / _ \\ | |_) || |       *" << std::endl;
			std::cout << "                                    *      ___) || |/ ___ \\|  _ < | |      *" << std::endl;
			std::cout << "                                   **     |____/ |_/_/   \\_\\_| \\_\\|_|       /" << std::endl;
			std::cout << "                                    *                                      *" << std::endl;
			std::cout << "                                   * *************  *%****** ******    /** *" << std::endl;
			std::cout << "                                 %****%        ******      ****   ****%  * **\\" << std::endl;
		}
	}

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
			The problem was being caused by this 'Quick Edit Mode' option which was enabled(checkbox is checked) by default on my Windows 10. And in this enabled status, this
			'Quick Edit Mode' was consuming all the Mouse-Events and wasn't dispatching any to my '.exe' .
			When this 'Quick Edit Mode' options' checkbox is unchecked (disabled), then program runs fine as intended/coded in this sample-code here, telling/printing all Mouse events.
			NOTE: The change in 'Console Properties' requires relaunch of the console, to take effect.*/
		


		draw_start_button(0);
		int x = 36; int x_size = 39;
		int y = 12; int y_size = 7;   // location and size of this button

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
					//std::cout << coord.X << std::endl;
					//std::cout << coord.Y << std::endl;
					if (coord.X>x && coord.X<(x+x_size) && coord.Y>y && coord.Y<(y+y_size)) {   // if clicked inside box
						flag = false;
						system("cls");
						draw_start_button(1);
						Sleep(500);
						system("cls");
						break;
					}
				}
			}
			///FlushConsoleInputBuffer(hin);
		}
		SetConsoleMode(hin, fdwSaveOldMode);

	}



	static int choose_what_to_do() {
		// type of simulation
		std::cout << "*******************************" << std::endl;
		std::cout << "*******************************" << std::endl;
		std::cout << "***                         ***" << std::endl;
		std::cout << "***   1. Original game      ***" << std::endl;
		std::cout << "***   2. By_Generation      ***" << std::endl;
		std::cout << "***   3. By_Queue           ***" << std::endl;
		std::cout << "***                         ***" << std::endl;
		std::cout << "*******************************" << std::endl;
		std::cout << "*******************************" << std::endl;

		std::cout << "\n\n\n\n\nEnter you choice: ";
		int choice;
		do {
			// input validation
			std::cin >> choice;
		} while (choice<1 || choice>3);
		
		return choice;
	}


	static int ask_wait_rate() {
		// ask for by_generation wait rate
		int zombie_mode_wait_rate;
		std::cout << "How long do you want to keep a dead cell in a zombie mode before resurrecting it?  ";
		do {
			//input validation
			std::cin >> zombie_mode_wait_rate;
		} while (zombie_mode_wait_rate<1);
		return zombie_mode_wait_rate;
	}


	static int ask_res_rate() {
		// ask for by_queue res rate
		int resurrection_rate;
		std::cout << "How many cells do you want to resurrect per generation?  ";
		do {
			// input validation
			std::cin >> resurrection_rate;
		} while (resurrection_rate<1);
		return resurrection_rate;
	}




}