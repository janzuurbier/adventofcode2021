// dag24.cpp : 
//
//z1 = w1 + 7
//z2 = z1*26 + w2 + 4
//z3 = z2*26 + w3 + 8
//z4 = z3 div 26 = z2 if w4 = z3 mod 26 - 4 = w3 + 4  ==> w4 = w3 + 4 (1)
//z5 = z4*26 + w5 + 5
//z6 = z5*26 + w6 + 14
//z7 = z6*26 + w7 + 12
//z8 = z7 div 26 = z6 if w8 = z7 mod 26 - 9 = w7 + 12 - 9 ==> w8 = w7 + 3 (2)
//z9 = z8 div 26 = z6 div 26 = z5 if w9 = z8 mod 26 - 9 = z6 mod 26 - 9 = w6 + 14 - 0 ==> w9 = w6 + 5 (3)
//z10 = z9*26 + w10 + 7
//z11 = z10 div 26 = z9 if w11 = z10 mod26 -15 = w10 + 7 - 15 ==> w11 = w10 - 8 (4)
//z12 = z11 div 26 = z9 div 26 = z5 div 26 = ze = z2 if w12 = z11 mod 26 - 7 = z9 mod 26 - 7 = z5 mod 26 - 7 = w5 + 5 - 7 ==> w12 = w5 - 2 (5)
//z13 = z12 div 26 = z8 div 26 = z2 div 26 = z1 if w13 = z12 mod 26 = z2 mod 26 - 10 = w2 + 4 - 10 ==> w13 = w2 - 6 (6)
//z14 = z12 div 26 = z1 div 26 = 0 (!) if w14 = z13 mod 26 = z1 mod 26 = w1 + 7 ==> w14 = w1 + 7 (7)
//
//All 7 conditions must be true for z14 to become zero.
//Since w1 ... w14 are >= 1 and <= 9
//w1 <= 2 because of (7)
//w2 >= 7 because of (6)
//w3 <= 5 because of (1)
//w5 >= 3 because of (5)
//w6 <= 4 because of (3)
//w7 <= 6 because of (2)
//w10 = 9 because of (4)
//now we can choose w1 .. w14 als large (for part 1) or as small (for part 2) as possible and check it with the program below.


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

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


