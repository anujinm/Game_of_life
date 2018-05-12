#include "newGame.h"


void newGame::set_state_random() {
	srand(time(NULL));
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (rand() % 3 == 0)
				set(i, j, 1);
			else
				set(i, j, 0);
		}
	}
}

void newGame::set_state_full() {
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			set(i, j, 1);
		}
	}
}

void newGame::set_state_1() {
	set(5, 0, 1);
	set(5, 1, 1);
	set(6, 0, 1);
	set(6, 1, 1);

	set(4, 5, 1);
	set(4, 6, 1);
	set(5, 5, 1);
	set(5, 6, 1);
	set(6, 5, 1);
	set(6, 6, 1);
	set(3, 7, 1);
	set(2, 8, 1);
	set(3, 9, 1);
	set(4, 10, 1);
	set(5, 10, 1);
	set(6, 10, 1);
	set(7, 7, 1);
	set(8, 8, 1);
	set(7, 9, 1);

	set(3, 15, 1);
	set(3, 16, 1);
	set(5, 15, 1);
	set(6, 16, 1);
	set(6, 17, 1);
	set(5, 17, 1);
	set(8, 17, 1);

	set(5, 19, 1);
	set(5, 20, 1);
	set(6, 21, 1);
	set(7, 20, 1);
	set(8, 20, 1);

	set(0, 24, 1);
	set(1, 24, 1);
	set(1, 25, 1);
	set(1, 26, 1);
	set(1, 27, 1);
	set(2, 25, 1);
	set(2, 26, 1);
	set(2, 27, 1);
	set(2, 28, 1);

	set(3, 25, 1);
	set(3, 28, 1);
	set(4, 25, 1);
	set(4, 26, 1);
	set(4, 27, 1);
	set(4, 28, 1);

	set(5, 24, 1);
	set(5, 25, 1);
	set(5, 26, 1);
	set(5, 27, 1);
	set(6, 24, 1);

	set(3, 34, 1);
	set(3, 35, 1);
	set(4, 34, 1);
	set(4, 35, 1);
}