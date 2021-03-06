// dag14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <map>

using namespace std;

struct rule_t {
	char a, b, c;
};

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	set<char> symbols;

	string first_line;
	getline(input, first_line);
	for (char ch : first_line) symbols.insert(ch);

	string empty_line;
	getline(input, empty_line);

	vector<rule_t> rules;
	string rule_line;
	while (getline(input, rule_line)) {
		rule_t r;
		r.a = rule_line[0];
		r.b = rule_line[1];
		r.c = rule_line[6];
		symbols.insert(r.a);
		symbols.insert(r.b);
		symbols.insert(r.c);
		rules.push_back(r);
	}

	//map1[a][b] contains the number of times the char-sequence ab appears
	map<char, map<char, uint64_t>> map1, map2;
	for (char ch1 : symbols)
		for (char ch2 : symbols) {
			map1[ch1][ch2] = 0;
			map2[ch1][ch2] = 0;
		}

	for (size_t i = 0; i < first_line.length() - 1; i++)
		map1[first_line[i]][first_line[i + 1]]++;

	for (int i = 0; i < 40; i++) {
		map2 = map1;
		for (rule_t r : rules) {
			map2[r.a][r.c] += map1[r.a][r.b];
			map2[r.c][r.b] += map1[r.a][r.b];
			map2[r.a][r.b] -= map1[r.a][r.b];
		}
		map1 = map2;
	}

	//count the symols in final line
	map<char, uint64_t> count;
	for (char ch : symbols)
		count[ch] = 0;

	for (char ch1 : symbols)
		for (char ch2 : symbols) {
			count[ch1] += map1[ch1][ch2];
			count[ch2] += map1[ch1][ch2];
		}

	//every char is counted twice except for the first and the last.
	//first and last char are the same in first line and final line
	char first = first_line[0], last = first_line[first_line.size() - 1];
	count[first]++;
	count[last]++;

	//divide by 2
	for (char ch : symbols) {
		count[ch] /= 2;
	}

	uint64_t min = count[*symbols.begin()];
	uint64_t max = count[*symbols.begin()];
	for (char ch : symbols) {
		cout << ch << ": " << count[ch] << endl;
		if (count[ch] < min) min = count[ch];
		if (count[ch] > max) max = count[ch];
	}

	cout << "min: " << min << endl;
	cout << "max: " << max << endl;
	cout << "difference: " << max - min << endl;

	return 0;
}