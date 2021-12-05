// matrix.cpp 
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "matrix.h"
using namespace std;


template<class T>
matrix<T>::matrix(const int m, const int n, const T init): rows(m), cols(n)
{
	values = new T*[rows];
	for (int i = 0; i < rows; i++)
		values[i] = new T[cols];
	for (int i = 0; i <rows; i++)
		for (int j = 0; j < cols; j++)
			values[i][j] = init;
}

template<class T>
matrix<T>::matrix(istream& is) {
		vector<T> temp;
		T invoer;
		
		//first row
		int colcount = 0;
		while (is.peek() != '\r' && is.peek() != '\n') {
			is >> invoer;
			temp.push_back(invoer);
			colcount++;
		}
		int rowcount = 1;
		while (!is.eof()) {
			for (int j = 0; j < colcount; j++) {
				is >> invoer;
				temp.push_back(invoer);
			}
			rowcount++;
		}
		rows = rowcount;
		cols = colcount;
		
		values = new T*[rows];
		for (int i = 0; i < rows; i++)
			values[i] = new T[cols];
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++) {
				values[i][j] = temp[i*cols + j];
				
			}		
	}

template<class T>
matrix<T>::matrix(const matrix& m): rows(m.rows), cols(m.cols) {
		values = new T*[rows];
		for (int i = 0; i < rows; i++)
			values[i] = new T[cols];
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++) 
				values[i][j] = m.values[i][j];
	}

template<class T>
matrix<T>::~matrix() {
	for (int i = 0; i < rows; i++) delete[] values[i];
	delete[] values;
}

template<class T>
ostream& operator<<(ostream& os, const matrix<T>& m) {
	for (int i = 0; i < m.rows; i++) {
		for (int j = 0; j < m.cols; j++) {
			os << m.values[i][j] << " ";
		}
		os << endl;
	}
	return os;
}


template<class T>
matrix<T> & matrix<T>::operator=(const matrix<T>& m) {
	for (int i = 0; i < rows; i++) delete[] values[i];
	delete[] values;
	cols = m.cols;
	rows = m.rows;
	values = new T*[rows];
	for (int i = 0; i < rows; i++)
		values[i] = new T[cols];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			values[i][j] = m.values[i][j];
	return *this;
}

	





