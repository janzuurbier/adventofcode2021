// dag5.cpp : Defines the entry point for the console application.
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

const int MAX = 1000;

class point_t {
public:
	int x;
	int y;

	friend istream& operator>>(istream& is, point_t& p) {
		is >> p.x;
		is.get();
		is >> p.y;
		return is;
	}
};

class line_t {
public:
	point_t begin;
	point_t end;


	friend istream& operator>>(istream& is, line_t& l) {
		string s;
		is >> l.begin >> s >> l.end;
		return is;
	}
};



int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}


	vector<line_t> lines;
	while (!input.eof()) {
		line_t l;
		input >> l;
		lines.push_back(l);
	}

	cout << lines.size() << " lines read." << endl;

	//het diagram (getransponeerd maar dat geeft niet)
	matrix<int, MAX, MAX> diagram(0);

	//dit moet handiger kunnen
	for (line_t l : lines) {
		if (l.begin.y == l.end.y && l.begin.x > l.end.x) {
			for (int i = l.begin.x; i >= l.end.x; i--) diagram[i][l.begin.y]++;
		}
		else if (l.begin.x == l.end.x && l.begin.y < l.end.y) {
			for (int i = l.begin.y; i <= l.end.y; i++) diagram[l.begin.x][i]++;
		}
		else if (l.begin.x == l.end.x && l.begin.y > l.end.y) {
			for (int i = l.begin.y; i >= l.end.y; i--) diagram[l.begin.x][i]++;
		}
		else if (l.begin.x == l.end.x && l.begin.y == l.end.y) {
			diagram[l.begin.x][l.begin.y]++;
		}
		else if (l.begin.y == l.end.y && l.begin.x < l.end.x) {
			for (int i = l.begin.x; i <= l.end.x; i++) diagram[i][l.begin.y]++;
		}
		

		else if (l.begin.x - l.end.x == l.begin.y - l.end.y && l.begin.x < l.end.x)
			for (int i = l.begin.x, j = l.begin.y; i <= l.end.x && j <= l.end.y; i++, j++) diagram[i][j]++;
		else if (l.begin.x - l.end.x == l.begin.y - l.end.y && l.begin.x > l.end.x)
			for (int i = l.begin.x, j = l.begin.y; i >= l.end.x && j >= l.end.y; i--, j--) diagram[i][j]++;

		else if (l.begin.x - l.end.x == l.end.y - l.begin.y && l.begin.x < l.end.x)
			for (int i = l.begin.x, j = l.begin.y; i <= l.end.x && j >= l.end.y; i++, j--) diagram[i][j]++;
		else if (l.begin.x - l.end.x == l.end.y - l.begin.y && l.begin.x > l.end.x)
			for (int i = l.begin.x, j = l.begin.y; i >= l.end.x && j <= l.end.y; i--, j++) diagram[i][j]++;

	}

	//cout << diagram << endl;

	int count = 0;
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			if (diagram[i][j] >= 2) count++;

	cout << count << endl;

    return 0;
}

