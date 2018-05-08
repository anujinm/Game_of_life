#pragma once

#include "newGame.h"



#ifndef BY_GENERATION_H
#define BY_GENERATION_H



class By_Generation : public newGame
{
private:
	int zombie_mode_wait_rate;

public:
	By_Generation() : newGame() {}
	By_Generation(const int size_row, const int size_col) : newGame(size_row, size_col) {}
	~By_Generation() {}


	void set_state_generation() {

	}

	void rule_1() {
		int live = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (matrix->get(i, j) == 1) {
					live = live_count(i, j);
					if (live < 2) {
						next_matrix->set(i, j, 0);
						// ADD TO HASHMAP
					}
				}
			}
		}
	}
	void rule_3() {
		int live = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (matrix->get(i, j) == 1) {
					live = live_count(i, j);
					if (live > 3) {
						next_matrix->set(i, j, 0);
						// ADD TO HASHMAP
					}
				}
			}
		}
	}
	void rule_4() {

	}


};



#endif // !BY_GENERATION_H
