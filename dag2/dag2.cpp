// dag2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
//#include <vector>
//#include <sstream>
#include <fstream>
//#include <set>
//#include <stack>

using namespace std;



int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	int depth = 0;
	int forw = 0;
	int aim = 0;

	string command;
	int parameter;
	
	while (!input.eof()) {
		input >> command;
		input >> parameter;
		if (command == "forward") { forw += parameter; depth += aim * parameter; }
		else if (command == "up") aim -= parameter;
		else if (command == "down") aim += parameter;	
	}

	cout << forw << "\t" << depth << "\t" << forw*depth << endl;


	return 0;
}