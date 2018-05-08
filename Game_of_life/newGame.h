#pragma once
#include <iostream>
#include "matrix.h"

class newGame {
protected:
	int row;
	int col;
	Matrix *matrix;
	Matrix *next_matrix;

	struct cell {
		int row;
		int col;
	};

public:
	newGame() {
		matrix = NULL;
		next_matrix = NULL;
		row = 0;
		col = 0;
	}

	newGame(const int size_row, const int size_col) {
		next_matrix = new Matrix(size_row, size_col);
		matrix = new Matrix(size_row, size_col);
		row = size_row;
		col = size_col;
	}

	~newGame() {
		delete matrix;
		delete next_matrix;
		matrix = NULL;
		next_matrix = NULL;
	}

	void set(int i, int j, int num) {
		matrix->set(i, j, num);
		next_matrix->set(i, j, num);
	}

	int get(int row, int col) {
		return matrix->get(row, col);
	}

	// State 1 has to be bigger than 20 rows and 35 columns
	void set_state_1() {
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

	void print() {
		matrix->print_pretty();
	}

	void iterate() {
		rule_1();
		rule_2();
		rule_3();
		rule_4();
		copy_backward();
	}
	//Rule 1: Any live cell with fewer than two live neighbors dies, as if caused by under population.
	void rule_1() {
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
	void rule_3() {
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
	void rule_4() {
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