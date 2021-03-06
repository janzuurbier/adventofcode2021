// dag4.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
//#include <sstream>
#include <fstream>
//#include <set>
//#include <stack>
#include "../matrix/matrix.h"

using namespace std;



int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	//de bingo-getallen
	vector<int> getallen;

	char ch = ',';
	int getal;
	while (ch == ',') {
		input >> getal;
		getallen.push_back(getal);
		ch = input.get();
	}
	cout << getallen.size() << " getallen gelezen." << endl;
	
	//de bingo-borden
	vector<matrix<int, 5, 5>> borden;

	matrix<int, 5, 5 > b(0);
	while (!input.eof()) {
		input >> b;
		borden.push_back(b);
	}

	cout << borden.size() << " borden gelezen" << endl;

	for (int getal : getallen) {
		for (matrix<int, 5, 5>& bord: borden) {

			
			//streep getal weg op huidige bord
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (bord[i][j] == getal)
						bord[i][j] = -1;
				}
			}

			//ga na of het bord heeft gewonnen
			bool wins = false;
			//check rows
			for (int i = 0; i < 5 && !wins; i++) {
				bool b = true;
				for (int j = 0; j < 5; j++) {
					if (bord[i][j] != -1) b = false;
				}
				wins = b;
			}
			//check columns
			for (int j = 0; j < 5 && !wins; j++) {
				bool b = true;
				for (int i = 0; i < 5; i++) {
					if (bord[i][j] != -1) b = false;
				}
				wins = b;
			}

			//als bord wint
			if (wins) {
				cout << endl << "getal: " << getal << endl;
				cout << bord << endl;
				int sum = 0;
				for (int i = 0; i < 5; i++)
					for (int j = 0; j < 5; j++)
						if (bord[i][j] >= 0) sum += bord[i][j];
				cout << "som niet gemarkeerde getallen: " << sum << endl;
				cout << "final score: " << sum * getal << endl;
				//vul ongeldige getallen in op het bord in plaats van verwijderen.
				for (int i = 0; i < 5; i++)
					for (int j = 0; j < 5; j++)
						bord[i][j] = 1000;
			}
			//bingo gaat door met overige borden
		}
	}
	




	return 0;
}