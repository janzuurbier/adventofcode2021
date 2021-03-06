// dag13.cpp : Defines the entry point for the console application.
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

class point {
public:
	int x, y;

	point(int x, int y) : x(x), y(y) {}

	point spiegel_hor(int hor) {
		return point(2*hor - x, y);
	}

	point spiegel_ver(int ver) {
		return point(x, 2*ver - y);
	}

	bool operator<(const point& p) const {
		return 2000 * y + x < 2000 * p.y + p.x;
	}

};


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string line;
	set<point> points;
	while (getline(input, line)) {
		if (line.length() == 0) break;
		size_t pos = line.find(',');
		int x = stoi(line.substr(0, pos));
		int y = stoi(line.substr(pos + 1));
		points.insert(point(x, y));
	}

	while (getline(input, line)) {
		size_t pos = line.find("=");
		char dir = line[pos - 1];
		int val = stoi(line.substr(pos + 1));
		set <point> new_points;
		if (dir == 'y') {
			for (point p : points) if (p.y > val) new_points.insert(p.spiegel_ver(val)); else if (p.y != val) new_points.insert(p);
		}
		else if (dir == 'x') {
			for (point p : points) if (p.x > val) new_points.insert(p.spiegel_hor(val)); else if (p.x != val) new_points.insert(p);
		}
		points = new_points;	
	}
	
	matrix<char, 6, 40> tekening('.');
	for (point p : points) {
		tekening[p.y][p.x] = '#';
	}

	cout << tekening << endl;

    return 0;
}

