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
map<char, int> roomnr;
map<char, int> stepcost;


struct mv {
	pos from, to;

	mv(pos p, pos q) : from(p), to(q) {}

	int get_steps() {
		return from.row - 1 + abs(from.col - to.col) + to.row - 1;
	}
};

vector<mv> find_moves(const burrow& b){
	vector<mv> v;	
	for (const pos& p : posities) {
		char ch = b[p.row][p.col];
		if ('A' <= ch && ch <= 'D') {
			if (p.row == 1) {
				bool canmove_to_hall = true;
				if (p.col < roomnr[ch]) {
					for (int i = p.col + 1; i <= roomnr[ch] && canmove_to_hall; i++)
						if (b[1][i] != '.')
							canmove_to_hall = false;
				}
				else if (p.col > roomnr[ch]) {
					for (int i = p.col - 1; i >= roomnr[ch] && canmove_to_hall; i--)
						if (b[1][i] != '.')
							canmove_to_hall = false;
				}
				if (canmove_to_hall) {
					int i = ROWS - 2;
					while (b[i][roomnr[ch]] == ch)
						i--;
					if (i != 1 && b[i][roomnr[ch]] == '.') v.push_back(mv(p, pos(i, roomnr[ch])));
				}
			}
			if (p.row > 1 && b[p.row - 1][p.col] == '.') {
				bool canmove_to_hall = true;
				bool canmove_to_room = true;
				
				if (p.col == roomnr[ch]) {
					canmove_to_room = false;
					int i = p.row;
					while (b[i][p.col] == ch) i++;
					if (i == ROWS - 1)
						canmove_to_hall = false;
				}
				if ( p.col != roomnr[ch]) {					
					if (p.col < roomnr[ch]) {
						for (int i = p.col + 1; i <= roomnr[ch] && canmove_to_room; i++)
							if (b[1][i] != '.')
								canmove_to_room = false;
					}
					else if (p.col > roomnr[ch]) {
						for (int i = p.col - 1; i >= roomnr[ch] && canmove_to_room; i--)
							if (b[1][i] != '.')
								canmove_to_room = false;
					}
					if (canmove_to_room) {
						int i = ROWS - 2;
						while (b[i][roomnr[ch]] == ch)
							i--;
						if (i != 1 && b[i][roomnr[ch]] == '.') 
							v.push_back(mv(p, pos(i, roomnr[ch])));
						else 
							canmove_to_room = false;
					}
				}
				if (canmove_to_hall && !canmove_to_room) {
					int i = p.col - 1;
					while (b[1][i] == '.' ) {
						if (i != 3 && i != 5 && i != 7 && i != 9) v.push_back(mv(p, pos(1, i)));
						i--;
					}
					i = p.col + 1;
					while (b[1][i] == '.') {
						if (i != 3 && i != 5 && i != 7 && i != 9)v.push_back(mv(p, pos(1, i)));
						i++;
					}
				}
			}
		}
	}
	return v;
}

uint32_t least_energy(burrow& b,  burrow& end) {
	if (b == end) return 0;
	vector<mv> moves = find_moves(b);
	if (moves.size() == 0) return 1000000;
	uint32_t min = 1000000;
	for (mv& m : moves) {
		char ch = b[m.from.row][m.from.col];
		uint32_t energy = stepcost[ch] * m.get_steps();		
		b[m.from.row][m.from.col] = '.';
		b[m.to.row][m.to.col] = ch;
		energy += least_energy(b, end);
		b[m.from.row][m.from.col] = ch;
		b[m.to.row][m.to.col] = '.';
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
	burrow endburrow('#');
	input >> endburrow;

	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++) 
			if (b[i][j] != '#') {
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


	cout << least_energy(b, endburrow ) << endl;

}
