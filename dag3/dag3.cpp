// dag3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
//#include <sstream>
#include <fstream>
//#include <set>
//#include <stack>

using namespace std;

const int LEN = 12;

// het programma moet twee maal draaien met een kleine aanpassing.
// vermenigvuldig de uitkomsten handmatig
int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	
	vector<string> lines;


	string line;
	while (getline(input, line)) {

		lines.push_back(line);

	}
	cout << lines.size() << " lines read" << endl;




	for (int i = 0; i < LEN; i++) {
		//als er één lijn over is, klaar
		if (lines.size() == 1) {
			cout << lines.at(0) << endl;
			break;
		}

		//tel aantal enen op plaats i
		unsigned int count = 0;
		for (string line : lines) {
			if (line[i] == '1') count++;
		}

		//ga na of er meer enen of meer nullen zijn
		char ch;
		if (2 * count >= lines.size()) {
			ch = '1';
		}
		else {
			ch = '0';
		}

	
		//verwijder ongeldige lijnen
		for (vector<string>::iterator iter = lines.begin(); iter != lines.end(); ) {
			if (iter->at(i) != ch)
				iter = lines.erase(iter);
			else
				++iter;
		}
		//cout << lines.size() << endl;

	}
	
	
	line = lines[0];
	//int-waarde omrekenen
	int ox_rating = 0;
	for (int i = 0; i < LEN; i++) {
		ox_rating *= 2;
		if (line.at(i) == '1')
			ox_rating += 1;
	}
	cout << ox_rating << endl;

		
	return 0;
}
