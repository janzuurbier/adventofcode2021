// dag10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
//#include <set>
#include <stack>
//#include <map>
//#include "../matrix/matrix.h"
#include <algorithm>

using namespace std;

bool matches(char open, char close) {
	return  (open == '<' && close == '>' || open == '(' && close == ')' || open == '{' && close == '}' || open == '[' && close == ']');

}

int score(char ch1) {
	int retval;
	switch (ch1) {
	case '}': retval = 1197; break;
	case ')': retval = 3; break;
	case ']': retval = 57; break;
	case '>': retval = 25137; break;
	case '{': retval = 3; break;
	case '(': retval = 1; break;
	case '[': retval = 2; break;
	case '<': retval = 4; break;
	default: retval = 0;
	}
	return retval;
}

//for corrupt line  return score of the first illegal bracket
//for incomplete line return the total score of missing brackets 
//in case of incomplete line it returns a negative value to mark difference between incomplete and corrupt lines
int64_t check_line(string line) {
	stack<char> mystack;
	istringstream iss(line);
	int retval = 0;
	char ch1 = ' ', ch2 = ' ';
	while (true) {
		iss >> ch1;
		if (iss.eof()) break;
		if (ch1 == '(' || ch1 == '{' || ch1 == '[' || ch1 == '<') {
			mystack.push(ch1);
		}
		else {

			//just to be sure
			if (mystack.empty()) {
				cout << "empty" << endl;  return 0;
			}

			ch2 = mystack.top();
			if (!matches(ch2, ch1)) {
				 return score(ch1);
			}
			mystack.pop();
		}
	}
	int64_t val = 0;
	while (!mystack.empty()) {
		char ch = mystack.top();
		mystack.pop();
		val *= 5;
		val += score(ch);
	}
	return -val;
}


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}


	
	int64_t sum = 0;
	vector<int64_t> scores;
	string line;
	while (getline(input, line)) {
		int64_t i = check_line(line);
		if (i >= 0)
			sum += i;
		else
			scores.push_back(-i);

	}
	cout << "part 1: " << sum << endl;


	sort(scores.begin(), scores.end());
	cout << "part 2: " << scores[scores.size() / 2] << endl;
	

	return 0;
}

