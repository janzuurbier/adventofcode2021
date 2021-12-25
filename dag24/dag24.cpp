// dag24.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
//#include <set>
//#include <stack>
#include "../matrix/matrix.h"
//#include <algorithm>

using namespace std;

const int ROWS = 7;
const int COLS = 13;
const int N = 19;
typedef  matrix<char, ROWS, COLS> burrow;

struct pos {
	int row;
	int col;

	pos(int r, int c) : row(r), col(c) {}

	bool operator<(const pos& p) const {
		if (row < p.row) return true;
		if (row == p.row && col < p.col) return true;
		return false;
	}
};

vector<pos> posities;
map<pos, int> posnr;
map<char, int> roomnr;
map<char, int> stepcost;


struct mv {
	int from, to;

	mv(int f = 0, int t = 0) : from(f), to(t) {}

	int get_steps() {
		pos p = posities[from];
		pos q = posities[to];
		return p.row - 1 + abs(p.col - q.col) + q.row - 1;
	}
};

vector<mv> find_moves(const burrow& b){
	vector<mv> v;	
	for (const pos& p : posities) {
		char ch = b[p.row][p.col];
		if ('A' <= ch && ch <= 'D') {
			if (p.row == 1) {
				bool canmove = true;
				if (p.col < roomnr[ch]) {
					for (int i = p.col + 1; i <= roomnr[ch] && canmove; i++)
						if (b[1][i] != '.')
							canmove = false;
				}
				else if (p.col > roomnr[ch]) {
					for (int i = p.col - 1; i >= roomnr[ch] && canmove; i--)
						if (b[1][i] != '.')
							canmove = false;
				}
				if (canmove) {
					int i = ROWS - 2;
					while (b[i][roomnr[ch]] == ch)
						i--;
					if (i != 1 && b[i][roomnr[ch]] == '.') v.push_back(mv(posnr[p], posnr[pos(i, roomnr[ch])]));
				}
			}
			if (p.row > 1 && b[p.row - 1][p.col] == '.') {
				bool canmove = true;
				bool canmovedirect = true;
				
				if (p.col == roomnr[ch]) {
					canmovedirect = false;
					int i = p.row;
					while (b[i][p.col] == ch) i++;
					if (i == ROWS - 1)
						canmove = false;
				}
				if ( p.col != roomnr[ch]) {					
					if (p.col < roomnr[ch]) {
						for (int i = p.col + 1; i <= roomnr[ch] && canmovedirect; i++)
							if (b[1][i] != '.')
								canmovedirect = false;
					}
					else if (p.col > roomnr[ch]) {
						for (int i = p.col - 1; i >= roomnr[ch] && canmovedirect; i--)
							if (b[1][i] != '.')
								canmovedirect = false;
					}
					if (canmovedirect) {
						int i = ROWS - 2;
						while (b[i][roomnr[ch]] == ch)
							i--;
						if (i != 1 && b[i][roomnr[ch]] == '.') 
							v.push_back(mv(posnr[p], posnr[pos(i, roomnr[ch])]));
						else 
							canmovedirect = false;
					}
				}
				if (canmove && !canmovedirect) {
					int i = p.col - 1;
					while (b[1][i] == '.' ) {
						if (i != 3 && i != 5 && i != 7 && i != 9) v.push_back(mv(posnr[p], posnr[pos(1, i)]));
						i--;
					}
					i = p.col + 1;
					while (b[1][i] == '.') {
						if (i != 3 && i != 5 && i != 7 && i != 9)v.push_back(mv(posnr[p], posnr[pos(1, i)]));
						i++;
					}
				}
			}
		}
	}
	return v;
}

uint32_t least_energy(burrow& b) {
	bool ready = true;
	for (char ch = 'A'; ready && ch <= 'D'; ch++) {
		for (int i = 2; ready && i < ROWS - 1; i++)
			if (b[i][roomnr[ch]] != ch) ready = false;
	}
	if (ready) return 0;
	vector<mv> moves = find_moves(b);
	if (moves.size() == 0) return INT32_MAX;
	uint32_t min = UINT32_MAX;
	for (mv& m : moves) {
		pos p = posities[m.from];
		pos q = posities[m.to];
		char ch = b[p.row][p.col];
		uint32_t energy = stepcost[ch] * m.get_steps();		
		b[p.row][p.col] = '.';
		b[q.row][q.col] = ch;
		energy += least_energy(b);
		b[p.row][p.col] = ch;
		b[q.row][q.col] = '.';
		if (energy < min) {
			min = energy;
		}
	}
	return min;
}


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	burrow b('#');
	input >> b;

	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++) 
			if (b[i][j] != '#') {
				posnr[pos(i, j)] = posities.size();
				posities.push_back(pos(i, j));	
			}

	roomnr['A'] = 3;
	roomnr['B'] = 5;
	roomnr['C'] = 7;
	roomnr['D'] = 9;

	stepcost['A'] = 1;
	stepcost['B'] = 10;
	stepcost['C'] = 100;
	stepcost['D'] = 1000;


	cout << least_energy(b ) << endl;

}
