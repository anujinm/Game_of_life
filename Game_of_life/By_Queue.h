#pragma once

#include "newGame.h"
#include <deque>



#ifndef BY_QUEUE_H
#define BY_QUEUE_H



class By_Queue : public newGame
{
private:
	int resurrection_rate;
	std::deque<cell> dead_queue;

public:
	By_Queue() : newGame() {}
	By_Queue(const int size_row, const int size_col) : newGame(size_row, size_col) {}
	~By_Queue() {}


	void set_state_queue() {

	}


	// wait....  do we add them to the queue   when they die   or   when they are resurrected ?
	
	void rule_1() {
		int live = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (matrix->get(i, j) == 1) {
					live = live_count(i, j);
					if (live < 2) {
						next_matrix->set(i, j, 0);
						// ADD TO QUEUE
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
						// ADD TO QUEUE
					}
				}
			}
		}
	}
	void rule_4() {

	}

};



#endif // !BY_QUEUE_H
