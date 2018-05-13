#pragma once
#define MATRIX_H

#include <iostream>
#include <Windows.h>
#include <random>
#include <ctime>



class Matrix {
private:
	int row;
	int col;
	int** matrix;

public:
	Matrix() {
		matrix = NULL;
		row = 0;
		col = 0;
	}
	Matrix(const int size_row, const int size_col) {
		matrix = NULL;
		row = size_row;
		col = size_col;

		matrix = new int*[row];
		for (int i = 0; i < row; i++) {
			matrix[i] = new int[col];
			for (int j = 0; j < col; j++) {
				matrix[i][j] = 0;
			}
		}
	}

	~Matrix() {
		for (int i = 0; i < row; i++) {
			delete matrix[i];
			// matrix[i] = NULL ?   just wondering...
		}
		delete matrix;
		matrix = NULL;
	}



	int get(int i, int j) {
		if (matrix != NULL && i >= 0 && i < row && j >= 0 && j < col) {
			return matrix[i][j];
		}
		else {
			std::cout << "Index out of range";
		}
	}

	void set(int i, int j, int num) {
		if (matrix != NULL && i >= 0 && i < row && j >= 0 && j < col) {
			matrix[i][j] = num;
		}
		else {
			std::cout << "Index out of range";
		}
	}

	int get_row() {
		return row;
	}

	int get_col() {
		return col;
	}

	void print() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				printf("%d ", matrix[i][j]);
			}
			printf("\n");
		}
	}

	void print_pretty() {
		//srand(time(NULL));

		char c = 219;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (matrix[i][j] == 1) {
					//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (rand() % 7) + 9);   // random color (9-15)
					std::cout << c << c;
				}
				else {
					printf("  ");
				}
			}
			printf("\n");
		}
	}
};
