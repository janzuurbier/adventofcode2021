// dag25.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
//#include <vector>
#include <sstream>
#include <fstream>
//#include <set>
//#include <stack>
#include "../matrix/matrix.h"
//#include <algorithm>

using namespace std;

const int ROWS = 137;
const int COLS = 139;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	matrix <char, ROWS, COLS> m('.');

	input >> m;
	matrix<char, ROWS, COLS> n = m;

	int steps = 0;
	bool changed = true;
	while(changed) {
		changed = false;
		for (int i = 0; i < ROWS ; i++) {
			for (int j = 0; j < COLS - 1; j++) {
				if (m[i][j] == '>' && m[i][j + 1] == '.') {
					n[i][j + 1] = '>';
					n[i][j] = '.';
					changed = true;
				}
			}
			if (m[i][COLS - 1] == '>' && m[i][0] == '.') {
				n[i][0] = '>';
				n[i][COLS - 1] = '.';
				changed = true;
			}			
		}	
		m = n;
		for (int j = 0; j < COLS; j++) {
			for (int i = 0; i < ROWS - 1; i++) {
				if (m[i][j] == 'v' && m[i + 1][j] == '.') {
					n[i + 1][j] = 'v';
					n[i][j] = '.';
					changed = true;
				}
			}
			if (m[ROWS - 1 ][j] == 'v' && m[0][j] == '.') {
				n[ROWS - 1][j] = '.';
				n[0][j] = 'v';
				changed = true;
			}			
		}
		m = n;
		steps++;		
	}
	cout << steps << endl;
}


