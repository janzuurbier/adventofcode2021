// dag24.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
//#include "../matrix/matrix.h"
//#include <algorithm>

using namespace std;

int64_t w = 0, x = 0, y = 0, z = 0;

vector<string> instructions;

void process_instruction(string s) {

	string instruction;
	char var;
	int val;

	istringstream iss(s);
	iss >> instruction >> var;
	if (instruction != "inp") {
		string temp;
		iss >> temp;
		if ('0' <= temp[0] && temp[0] <= '9' || temp[0] == '-') val = stoi(temp);
		else if (temp[0] == 'w') val = w;
		else if (temp[0] == 'x') val = x;
		else if (temp[0] == 'y') val = y;
		else if (temp[0] == 'z') val = z;
		else cout << "error at " << s << endl;
	}

	if (instruction == "inp") {
		char ch;
		cin >> ch;
		switch (var) {
		case 'w': w = ch - 48; break;
		case 'x': x = ch - 48; break;
		case 'y': y = ch - 48; break;
		case 'z': z = ch - 48; break;
		default: cout << "error at " << s << endl;
		}
	}
	else if (instruction == "mul") {
		switch (var) {
		case 'w': w *= val; break;
		case 'x': x *= val; break;
		case 'y': y *= val; break;
		case 'z': z *= val; break;
		default: cout << "error at " << s << endl;
		}
	}
	else if (instruction == "add") {
		switch (var) {
		case 'w': w += val; break;
		case 'x': x += val; break;
		case 'y': y += val; break;
		case 'z': z += val; break;
		default: cout << "error at " << s << endl;
		}
	}
	else if (instruction == "div") {
		if (val == 0)
			cout << "division by zero" << endl;
		else
			switch (var) {
			case 'w': w /= val; break;
			case 'x': x /= val; break;
			case 'y': y /= val; break;
			case 'z': z /= val; break;
			default: cout << "error at " << s << endl;
			}
	}
	else if (instruction == "mod") {
		if (val == 0)
			cout << "division by zero" << endl;
		else
			switch (var) {
			case 'w': w %= val; if (w < 0) w = -w;  break;
			case 'x': x %= val; if (x < 0) x = -x; break;
			case 'y': y %= val; if (y < 0) y = -y; break;
			case 'z': z %= val; if (z < 0) z = -z; break;
			default: cout << "error at " << s << endl;
			}
	}
	else if (instruction == "eql") {
		switch (var) {
		case 'w': w = (w == val) ? 1 : 0; break;
		case 'x': x = (x == val) ? 1 : 0; break;
		case 'y': y = (y == val) ? 1 : 0; break;
		case 'z': z = (z == val) ? 1 : 0; break;
		default: cout << "error at " << s << endl;
		}
	}
}

void run() {
	for (string s : instructions)
		process_instruction(s);
	cout << "w = " << w << endl;
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	cout << "z = " << z << endl;
	cout << endl;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string line;	
	while (getline(input, line)) {
		if (line.substr(0, 3) == "inp") {
			instructions.push_back(line);
		}
	}

	run();
}


