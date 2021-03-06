#pragma once

#include <map>
#include <list>

#include "newGame.h"



#ifndef BY_GENERATION_H
#define BY_GENERATION_H



class By_Generation : public newGame
{
private:
	int zombie_mode_wait_rate;
	std::map<int, std::list<int>> dead_generation_map;
	std::list<int> temp_dead_list;

public:
	// constructors and stuff
	By_Generation() : newGame() {
		zombie_mode_wait_rate = 5;
	}
	By_Generation(const int size_row, const int size_col, int zombie_mode_wait_rate1) : newGame(size_row, size_col) {
		zombie_mode_wait_rate = zombie_mode_wait_rate1;
	}
	~By_Generation() {}


	// set / get
	void set_zombie_mode_wait_rate(int wr) {
		zombie_mode_wait_rate = wr;
	}
	int get_zombie_mode_wait_rate() {
		return zombie_mode_wait_rate;
	}



	// the simulation
	void iterate() {
		temp_dead_list = {};
		generation++;
		count_live_cells();

		rule_1();
		rule_2();
		rule_3();
		dead_generation_map[generation] = temp_dead_list;   // add to hashmap
		rule_4();
		copy_backward();
	}

	void rule_1() {
		// death by loneliness :(
		int live = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (matrix->get(i, j) == 1) {
					live = live_count(i, j);
					if (live < 2) {
						next_matrix->set(i, j, 0);
						temp_dead_list.push_back(i);
						temp_dead_list.push_back(j);
					}
				}
			}
		}
	}
	void rule_3() {
		// death by party party party :)
		int live = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (matrix->get(i, j) == 1) {
					live = live_count(i, j);
					if (live > 3) {
						next_matrix->set(i, j, 0);
						temp_dead_list.push_back(i);
						temp_dead_list.push_back(j);
					}
				}
			}
		}
	}
	void rule_4() {
		// resurrection by generation  O:)
		int resr_gen = generation - zombie_mode_wait_rate;

		if (generation - zombie_mode_wait_rate >= 1) {
			for (int i = 0; i < dead_generation_map[resr_gen].size(); i++) {
				int r = dead_generation_map[resr_gen].front();
				dead_generation_map[resr_gen].pop_front();
				int c = dead_generation_map[resr_gen].front();
				dead_generation_map[resr_gen].pop_front();

				next_matrix->set(r, c, 1);
			}
		}
	}


};



#endif // !BY_GENERATION_H
