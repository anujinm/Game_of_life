#pragma once

#include "newGame.h"
#include <map>
#include <list>



#ifndef BY_GENERATION_H
#define BY_GENERATION_H



class By_Generation : public newGame
{
private:
	int zombie_mode_wait_rate = 5;
	int generation;
	// HASHMAP
	std::map<int, std::list<int>> dead_generation_map;
	std::list<int> temp_dead_list;

public:
	By_Generation() : newGame() {
		generation = 1;
	}
	By_Generation(const int size_row, const int size_col) : newGame(size_row, size_col) {
		generation = 1;
	}
	~By_Generation() {}




	virtual void iterate() {
		temp_dead_list = {};

		rule_1();
		rule_2();
		rule_3();
		dead_generation_map[generation] = temp_dead_list;
		rule_4();
		copy_backward();

		generation++;
	}

	void rule_1() {
		int live = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (matrix->get(i, j) == 1) {
					live = live_count(i, j);
					if (live < 2) {
						next_matrix->set(i, j, 0);
						// ADD TO HASHMAP ???
						temp_dead_list.push_back(i);
						temp_dead_list.push_back(j);
					}
				}
			}
		}
		// FIX THIS. OVERWRITES THE LIST ALREADY THERE IN THAT INDEX
		dead_generation_map[generation] = temp_dead_list;
	}
	void rule_3() {
		int live = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (matrix->get(i, j) == 1) {
					live = live_count(i, j);
					if (live > 3) {
						next_matrix->set(i, j, 0);
						// ADD TO HASHMAP ???
						temp_dead_list.push_back(i);
						temp_dead_list.push_back(j);
					}
				}
			}
		}
		// FIX THIS. OVERWRITES THE LIST ALREADY THERE IN THAT INDEX
		dead_generation_map[generation] = temp_dead_list;
	}
	void rule_4() {
		//COPIED FROM BY QUEUE NOT FIXED YET 
		//resurrect first n (or less) dead cells from queue in every generation
		for (int i = 0; i < resurrection_rate; i++) {
			if (dead_queue.empty() == false) {
				int r = dead_queue.front();
				dead_queue.pop_front();
				int c = dead_queue.front();
				dead_queue.pop_front();

				next_matrix->set(r, c, 1);
			}
		}


		if (generation - zombie_mode_wait_rate >= 1) {
			for (int i = 0; i < dead_generation_map[generation-zombie_mode_wait_rate].size(); i++) {

			}
		}
	}


};



#endif // !BY_GENERATION_H
