// dag15.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
//#include <vector>
//#include <sstream>
#include <fstream>
#include <set>
//#include <stack>
#include "../matrix/matrix.h"
//#include <algorithm>

using namespace std;

const int MAX = 100;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	matrix<char, MAX, MAX> m('0');
	matrix<int, MAX, MAX> h(0);
	matrix<int, 5*MAX, 5*MAX> g(0);
	matrix<int, 5*MAX, 5*MAX> d(1000000);

	//read chars
	input >> m;

	//convert to int
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			h[i][j] = m[i][j] - 48;

	//matrix with 25 tiles
	for(int m = 0; m < 5; m++ )
		for (int n = 0; n < 5; n++) {
			for (int i = 0; i < MAX; i++)
				for (int j = 0; j < MAX; j++)
					g[m * MAX + i][n*MAX + j] = (h[i][j] + m  + n - 1 ) % 9 + 1 ;
		}

	
	//for each position calculate total risk of a path to that position
	//several iterations may be necessary if the lowest totol risk path is not always topdown and left to right. 
	d[0][0] = 0;
	bool changed = true;
	while (changed) {	
		changed = false;
		for (int i = 0; i < 5 * MAX; i++)
			for (int j = 0; j < 5 * MAX; j++) {
				if (d.isInRange(i + 1, j) && d[i][j] > d[i + 1][j] + g[i][j]) {
					d[i][j] = d[i + 1][j] + g[i][j];
					changed = true;
				}
				if (d.isInRange(i, j + 1) && d[i][j] > d[i][j + 1] + g[i][j]) {
					d[i][j] = d[i][j + 1] + g[i][j];
					changed = true;
				}
				if (d.isInRange(i - 1, j) && d[i][j] > d[i - 1][j] + g[i][j]) {
					d[i][j] = d[i - 1][j] + g[i][j];
					changed = true;
				}
				if (d.isInRange(i, j - 1) && d[i][j] > d[i][j - 1] + g[i][j]) {
					d[i][j] = d[i][j - 1] + g[i][j];
					changed = true;
				}
			}	
	}
	cout << d[5 * MAX - 1][5 * MAX - 1] << endl;

	return 0;
}

