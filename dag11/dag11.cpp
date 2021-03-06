// dag11.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
//#include <set>
//#include <stack>
#include "../matrix/matrix.h"

using namespace std;

const int ROWS = 10, COLS = 10;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	matrix<char, ROWS, COLS> map('0');	
	int flashes = 0;

	input >> map;

	for (int step = 0; step < 1000; step++) {
		
		matrix<bool, ROWS, COLS> hasflashed(false);

		for(int i = 0; i < COLS; i++)
			for (int j = 0; j < ROWS; j++) {
				map[i][j]++;
			}
	
		bool changed = true;
		while (changed) {
			changed = false;
		
			for (int i = 0; i < COLS; i++)
				for (int j = 0; j < ROWS; j++) {
					if (map[i][j] > '9'  && !hasflashed[i][j]) {
						flashes++;
						changed = true;
						hasflashed[i][j] = true;

						for (int m = i - 1; m <= i + 1; m++)
							for (int n = j - 1; n <= j + 1; n++) {
								if (map.isInRange(m, n) && !(m == i && n == j) )
									map[m][n]++;
							}
						
					}
				}			
		}//while
		
		for (int i = 0; i < COLS; i++)
			for (int j = 0; j < ROWS; j++) {
				if (map[i][j] > '9') map[i][j] = '0';
			}
		
		if (step + 1 == 100) cout << flashes << endl;

		bool have_all_flashed = true;
		for (int i = 0; i < COLS; i++)
			for (int j = 0; j < ROWS; j++) {
				if (!hasflashed[i][j]) have_all_flashed = false;

			}
		if (have_all_flashed) {
			cout << step + 1 << endl;
			break;
		}
		
	}//steps
	
	return 0;
}