#pragma once
#include <iostream>
#include <random>
#include <ctime>
#include <map>
#include <fstream>

#include "matrix.h"



class newGame {
protected:
	int row;
	int col;
	Matrix *matrix;
	Matrix *next_matrix;
	std::map<int,int> live_count_map;    // map of number of live cells every generation
	int generation;

public:
	// constructors and destructors
	newGame() {
		matrix = NULL;
		next_matrix = NULL;
		row = 0;
		col = 0;
		generation = 0;
	}
	newGame(const int size_row, const int size_col) {
		next_matrix = new Matrix(size_row, size_col);
		matrix = new Matrix(size_row, size_col);
		row = size_row;
		col = size_col;
		generation = 0;
	}
	~newGame() {
		delete matrix;
		delete next_matrix;
		matrix = NULL;
		next_matrix = NULL;
	}



	// set/get functions
	void set(int i, int j, int num) {
		matrix->set(i, j, num);
		next_matrix->set(i, j, num);
	}

	int get(int row, int col) {
		return matrix->get(row, col);
	}

	

	// initial states
	void set_state_1();   // State 1 has to be bigger than 20 rows and 35 columns
	void set_state_random();
	void set_state_full();



	// print
	void print() {
		matrix->print_pretty();
	}
	void show_stats() {
		std::cout << "\ngeneration : " << generation << "                 " << std::endl;
		std::cout << "\nlive count : " << live_count_map[generation] << "                 " << std::endl;
	}


	void export_data(int i) {
		// export data to text file
		std::ofstream file1;

		if (i == 1) {
			file1.open("\\\\cs1\\2021\\asthapit21\\CS-273-1\\Game_of_life\\Game_of_life\\original_data.csv", std::ios::out);
		}
		else if (i == 2) {
			file1.open("\\\\cs1\\2021\\asthapit21\\CS-273-1\\Game_of_life\\Game_of_life\\by_generation_data.csv", std::ios::out);
		}
		else if (i == 3) {
			file1.open("\\\\cs1\\2021\\asthapit21\\CS-273-1\\Game_of_life\\Game_of_life\\by_queue_data.csv", std::ios::out);
		}

		for (int i = 0; i < 301; i++) {
			file1 << i << ", " << live_count_map[i] << "\n";
		}
		file1.close();

		if (file1.is_open()){

		}
	}



	// the simulation
	virtual void iterate() {
		generation++;
		count_live_cells();

		rule_1();
		rule_2();
		rule_3();
		rule_4();
		copy_backward();
	}
	//Rule 1: Any live cell with fewer than two live neighbors dies, as if caused by under population.
	virtual void rule_1() {
		int live = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (matrix->get(i, j) == 1) {
					live = live_count(i, j);
					if (live < 2)
						next_matrix->set(i, j, 0);
				}
			}
		}
	}
	// Rule 2:	Any live cell with two or three live neighbors lives on to the next generation.
	void rule_2() {
		int live = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (matrix->get(i, j) == 1) {
					live = live_count(i, j);
					if (live == 2 || live == 3)
						next_matrix->set(i, j, 1);
				}
			}
		}
	}
	// Rule 3: Any live cell with more than three live neighbors dies, as if by overpopulation.
	virtual void rule_3() {
		int live = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (matrix->get(i, j) == 1) {
					live = live_count(i, j);
					if (live > 3)
						next_matrix->set(i, j, 0);
				}
			}
		}
	}
	// Rule 4: Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.		
	virtual void rule_4() {
		int live = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				//if dead
				if (matrix->get(i, j) == 0) {
					live = live_count(i, j);
					if (live == 3)
						next_matrix->set(i, j, 1);
				}
			}
		}
	}


	void count_live_cells() {
		// count number of live cells in each generation and store in map
		int live_number = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (matrix->get(i, j) == 1) {
					live_number += 1;
				}
			}
		}
		live_count_map[generation] = live_number;
	}

protected:
	int live_count(int i, int j) {
		int count = 0; //count neighbours

		if (i - 1 >= 0 && matrix->get(i - 1, j) == 1)	//check the top
			count++;
		if (j - 1 >= 0 && matrix->get(i, j - 1) == 1)	//check the left
			count++;
		if (i + 1 < row && matrix->get(i + 1, j) == 1)	//check the bottom
			count++;
		if (j + 1 < col && matrix->get(i, j + 1) == 1)	//check the right
			count++;
		if (i - 1 >= 0 && j-1 >= 0 && matrix->get(i - 1, j - 1) == 1)	//check top lefft
			count++;
		if (j - 1 >= 0 && i + 1 < row && matrix->get(i + 1, j - 1) == 1)	//check bottom left
			count++;
		if (i - 1 >= 0 && j + 1 < col && matrix->get(i - 1, j + 1) == 1)	//check top right
			count++;
		if (i + 1 < row && j + 1 < col && matrix->get(i + 1, j + 1) == 1)	//check bottom right
			count++;
		return count;
	}
	
	void copy_forward() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++)
				next_matrix->set(i, j, matrix->get(i, j));
		}
	}
	void copy_backward() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++)
				matrix->set(i, j, next_matrix->get(i, j));
		}
	}
	
};