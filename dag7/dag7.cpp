// dag7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
//#include <sstream>
#include <fstream>
//#include <set>
//#include <stack>
//#include "../matrix/matrix.h"
#include <algorithm>

using namespace std;


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	vector<int> positions;

	char ch = ',';
	int getal;
	int aantal = 0;
	while (ch == ',') {
		aantal++;
		input >> getal;
		positions.push_back(getal);
		ch = input.get();
	}
	cout << aantal << " getallen gelezen." << endl;
	for (int i : positions) cout << i << " ";
	cout << endl;

	//sort the array
	sort(positions.begin(), positions.end());
	for (int i : positions) cout << i << " ";
	cout << endl;

	/*
	//part 1
	//fuel for the crabs left of current position to reach the current position
	int left = 0;
	//fuel for the crabs right of current position to reach the current position
	int right = 0;
	for (int p : positions) right += p;

	//nr of crabs left of current pos
	int count1 = 0;
	//nr of crabs right of current pos
	int count2 = positions.size();

	int oldpos = positions[0];
	int minfuel = Left + right;
	int minpos = 0;
	for (int pos : positions) {
		left += count1 * (pos - oldpos);
		right -= count2 * (pos - oldpos);
		count1++;
		count2--;
		int fuel = left + right;
		cout << pos << " fuel: " << left + right << endl;
		oldpos = pos;
		if (fuel < minfuel) {
			minfuel = fuel;
			minpos = pos;
		} 
	}	
	*/

	//part 2
	int nrCrabs = positions.size();
	int sum = 0;
	for (int p : positions)
		sum += p;

	int fuel = 0;
	for (int p : positions)
		fuel += p * p + p;
	fuel /= 2;
	cout << fuel << endl;
	int lastpos = 0;
	int minfuel = fuel;
	int minpos = 0;
	int count = 0;
	for (int i = positions[0]; i < positions[nrCrabs -1]; i++) {
		
		while(positions[lastpos] == i){
			lastpos++;
			count++;
		}
		int delta = (2 * count - nrCrabs);
		delta += (2 * i + 1)*nrCrabs  - 2*sum;
		delta /= 2;
		fuel += delta;
		//sorry for all the math
		if (fuel < minfuel) {
			minfuel = fuel;
			minpos = i+1;
		}
		//cout << "postition: " << i+1 << " fuel: " << fuel << endl;

	}
	
	//both parts
	cout << "position: " << minpos << " fuel: " << minfuel << endl;

	return 0;
}
