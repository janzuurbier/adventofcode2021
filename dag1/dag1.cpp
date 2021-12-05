// dag1.cpp : Defines the entry point for the console application.
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

	int incr = 0;

	string line;
	getline(input, line);
	int x = stoi(line);
	getline(input, line);
	int y = stoi(line);
	getline(input, line);
	int z = stoi(line);
	int prev = x + y + z;
	//cout << prev << endl;
	while (getline(input, line)) {
		x = y;
		y = z;
		z = stoi(line);
		int sum = x + y + z;
		if (sum > prev) incr++;
		prev = sum;
		//cout << prev << endl;
	}


	cout << endl << incr <<  endl;

	return 0;
}