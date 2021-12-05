#ifndef MATRIXH
#define MATRIXH

#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;


template <class T, int rows, int cols>
class matrix {
private:
	T * *values;

public:
	matrix(const T init) {
			values = new T*[rows];
		for (int i = 0; i < rows; i++)
			values[i] = new T[cols];
		for (int i = 0; i <rows; i++)
			for (int j = 0; j < cols; j++)
				values[i][j] = init;
	}
	

	matrix(const matrix& m) {
		values = new T*[rows];
		for (int i = 0; i < rows; i++)
			values[i] = new T[cols];
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				values[i][j] = m.values[i][j];
	}

	~matrix() {
		for (int i = 0; i < rows; i++) delete[] values[i];
		delete[] values;
	}

	friend ostream& operator<<(ostream& os, const matrix& m) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				os << m.values[i][j] << " ";
			}
			os << endl;
		}
		return os;
	}

	friend istream& operator>>(istream& is, matrix& m) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				is >> m.values[i][j];
			}
		}
		return is;
	}

	T* operator[] (const int n) const { 
		return values[n]; 
	}

	matrix& operator=(const matrix& m){
		//for (int i = 0; i < rows; i++) delete[] values[i];
		////delete[] values;
		//values = new T*[rows];
		//for (int i = 0; i < rows; i++)
			//values[i] = new T[cols];
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				values[i][j] = m.values[i][j];
		return *this;
	}

	bool isInRange(int i, int j) {
		return 0 <= i && i < rows && 0 <= j && j < cols;
	}

	int getRows() {
		return rows;
	}

	int getCols() {
		return cols;
	}
};

#endif // !MATRIXH