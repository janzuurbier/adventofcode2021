// dag8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <set>
#include <map>
//#include <stack>
//#include "../matrix/matrix.h"

using namespace std;

//returnt true als de strings verschillende letters hebben
//wel dezelfde letters maar in andere volgorde dan false
bool is_different(string a, string b) {
	if (a.length() != b.length()) return true;
	for (char ch : a)
		if (b.find(ch) == string::npos)
			return true;
	return false;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	int sum = 0;//te berekenen antwoord op part 2;

	string line;
	while (getline(input, line)) {

		istringstream in(line);

		vector<string> words;
		while (!in.eof()) {
			string s;
			in >> s;
			if (s != "|")
				words.push_back(s);
		}

		//map met als key een letterstring en als value het cijfer dat hij vertegenwoordigt
		map<string, int> themap;

		//string die bij een bepaald cijfer horen.
		string string1, string6, string9, string5, string3;
		//letter die op de plaats van c resp e komt
		char letterc, lettere;

		for (string s : words) {
			if (s.length() == 2) { themap[s] = 1; string1 = s; }
			else if (s.length() == 3) themap[s] = 7;
			else if (s.length() == 4) themap[s] = 4;
			else if (s.length() == 7) themap[s] = 8;
		}
		//lengte is 6 en niet beide letters van string1 dan is het een 6
		for (string s : words) {
			if (s.length() == 6 && (s.find(string1[0]) == string::npos || s.find(string1[1]) == string::npos)) {
				themap[s] = 6;
				string6 = s;
				//cout << string6 << " is " << 6 << endl;
				for (char ch = 'a'; ch <= 'g'; ch++)
					if (s.find(ch) == string::npos)
						letterc = ch;
			}
		}
		//lengte is 5 en de c ontbreekt dan is het een 5
		for (string s : words) {
			if (s.length() == 5 && s.find(letterc) == string::npos) {
				themap[s] = 5;
				string5 = s;
				//cout << string5 << " is " << 5 << endl;
				for (char ch = 'a'; ch <= 'g'; ch++)
					if (s.find(ch) == string::npos)
						if(ch != letterc) lettere = ch;
			}
		}	
		//lengte is 6 en de e ontbreekt dan is het een 9
		for (string s : words) {
			if (s.length() == 6 && s.find(lettere) == string::npos) {
				themap[s] = 9;
				string9 = s;
				//cout << string9 << " is " << 9 << endl;
			}
		}
		//overgebleven lengte 6 is de 0
		for (string s : words) {
			if (s.length() == 6 && is_different(s, string6) && is_different(s, string9)) {
				themap[s] = 0;
				//cout << s << " is " << 0 << endl;
			}
		}	
		//overgebleven lengte 5 waarvan de e ontbreekt is een 3
		for (string s : words) {
			if (s.length() == 5 && s.find(lettere) == string::npos && is_different(s, string5))  {
				themap[s] = 3;
				string3 = s;
				//cout << string3 << " is " << 3 << endl;
			}
		}
		//blijft over de 2
		for (string s : words) {
			if (s.length() == 5 && is_different(s, string3) && is_different(s, string5)) {
				themap[s] = 2;
				//cout << s << " is " << 2 << endl;
			}
		}
		

		// einde van de regel achter de | 
		int pos = line.find('|');
		line = line.substr(pos + 1);
		istringstream iss = istringstream(line);
		
		//bepaal de getalwaarde van het einde van de regel
		int val = 0;
		while (!iss.eof()) {
			string s;
			iss >> s;
			val = val *10 + themap[s];
		}
		//cout << line << " " << val << endl;
		sum += val;
			
	}

	cout << sum << endl;
		
		
	return 0;
}
