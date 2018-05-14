#pragma once

#include <deque>

#include "newGame.h"



#ifndef BY_QUEUE_H
#define BY_QUEUE_H



class By_Queue : public newGame
{
private:
	int resurrection_rate = 10;
	std::deque<int> dead_queue;   // we're using a queue here !! notice it ! thank you !

public:
	By_Queue() : newGame() {}
	By_Queue(const int size_row, const int size_col) : newGame(size_row, size_col) {}
	~By_Queue() {}



	void set_resurrection_rate(int r) {
		resurrection_rate = r;
	}
	int get_resurrection_rate() {
		return resurrection_rate;
	}


	
	void iterate() {
		rule_1();
		rule_2();
		rule_3();
		rule_4();
		copy_backward();
	}

	void rule_1() {
		// death by underpopulation
		int live = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (matrix->get(i, j) == 1) {
					live = live_count(i, j);
					if (live < 2) {
						next_matrix->set(i, j, 0);
						// ADD TO QUEUE
						dead_queue.push_back(i);
						dead_queue.push_back(j);
					}
				}
			}
		}
	}
	void rule_3() {
		// death by overpopulation
		int live = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (matrix->get(i, j) == 1) {
					live = live_count(i, j);
					if (live > 3) {
						next_matrix->set(i, j, 0);
						// ADD TO QUEUE
						dead_queue.push_back(i);
						dead_queue.push_back(j);
					}
				}
			}
		}
	}
	void rule_4() {
		//resurrect first n (or less) dead cells from queue in every generation
		for (int i = 0; i < resurrection_rate; i++){
			if (dead_queue.empty() == false) {
				int r = dead_queue.front();
				dead_queue.pop_front();
				int c = dead_queue.front();
				dead_queue.pop_front();

				next_matrix->set(r, c, 1);
			}
		}
	}

};



#endif // !BY_QUEUE_H
