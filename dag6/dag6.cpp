// dag6.cpp : Defines the entry point for the console application.
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

using namespace std;

/**
* brief fishcount for part 1 use recursion to calculate number of fish
* param timerstart timer of a fish at time 0
* param days number of days
* return the ammount of fish this fish has grown into after the number of days
*/
int fishcount(int timerstart, int days) {
	int count = 1;
	for (int i = 1; i <= days; i++) {	
		if (timerstart == 0) {
			timerstart = 6;
			count = count + fishcount(8, days - i );
		}
		else
			timerstart--;
	}
	return count;
}




int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	int fisharray[7];
	for (int i = 0; i < 7; i++) fisharray[i] = 0;

	char ch = ',';
	int getal;
	int aantal = 0;
	while (ch == ',') {
		aantal++;
		input >> getal;
		fisharray[getal]++;
		ch = input.get();
	}
	cout << aantal << " getallen gelezen." << endl;

	//part 1
	int sum = 0;
	for (int i = 0; i < 7; i++)
		sum += fisharray[i]*fishcount(i, 80);
	cout << sum << endl;

	//part 2
	//now avoid recursion
	//calculate fishcount(8, x) in an array
	
	uint64_t fishcountarray[265];
	fishcountarray[0] = 1;
	for (int x = 1; x < 265; x++) {
		uint64_t count = 1;
		int timerstart = 8;
		for (int i = 1; i <= x; i++) {
			if (timerstart == 0) {
				timerstart = 6;
				count = count + fishcountarray[x - i];
			}
			else
				timerstart--;
		}
		fishcountarray[x] = count;
	}

	uint64_t sum2 = 0;
	for (int i = 0; i < 7; i++)
		sum2 += fisharray[i]*fishcountarray[256 + 8 - i]; //fishcount(x, 256) = fishcount(8, 256 + 8 - x)

	cout << sum2 << endl;


	return 0;
}

