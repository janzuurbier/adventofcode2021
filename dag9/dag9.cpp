// dag9.cpp : Only part 2..
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
//#include <sstream>
#include <fstream>
#include <set>
//#include <map>
//#include <stack>
#include "../matrix/matrix.h"
#include <algorithm>

using namespace std;

const int ROWS = 100, COLS = 100;
//const int ROWS = 5, COLS = 10;

// find the size of de basin where point (i, j) is in.
// (i, j) is not nessecerally a lowpoint
// returns 0 if height = 9
// also this point and all other points in the basin are being marked, so that they are counted only once
int find_basin_size (int i, int j, const matrix<char, ROWS, COLS>& map, matrix<bool, ROWS, COLS>& marked) {
	int size = 0;
	if (map.isInRange(i, j) && !marked[i][j] && map[i][j] != '9') {
		size++;
		marked[i][j] = true;
		size += find_basin_size(i + 1, j, map, marked);
		size += find_basin_size(i - 1, j, map, marked);
		size += find_basin_size(i, j - 1, map, marked);
		size += find_basin_size(i, j + 1, map, marked);
	}
	return size;
}


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	//ifstream input("C:\\Users\\Jan\\Desktop\\test.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	matrix<char, ROWS, COLS> heightmap('0');
	matrix<bool, ROWS, COLS> marked(false);

	input >> heightmap;

	vector<int> basin_sizes;
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++) {
			int size = find_basin_size(i, j, heightmap, marked);
			if (size > 0) {
				basin_sizes.push_back(size);
			}
		}
	sort(basin_sizes.begin(), basin_sizes.end());
	for (int i : basin_sizes) cout << i << "\t";
	cout << endl;


    return 0;
}

