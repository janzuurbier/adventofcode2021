// dag20.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <sstream>
#include <fstream>
#include <set>
//#include <stack>
#include <vector>
#include <map>
#include "../matrix/matrix.h"
//#include <algorithm>

using namespace std;

const int N = 100;
const int A = 50;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string line = "";
	string l;
	while (true) {
		getline(input, l);
		if (l.size() == 0) break;
		line += l;
	}
	cout << line.size() << endl;

	matrix<char, N, N> temp('.');
	input >> temp;

	matrix<char, N + 2*A, N + 2*A>  m('.');
	for(int i = 0; i < N ; i++)
		for (int j = 0; j < N ; j++) {
			m[i + A][j + A] = temp[i][j];
		}

	for (int k = 1; k <= A; k++) {
		matrix<char, N + 2 * A, N + 2 * A> n = m;
		for (int i = 0; i < N + 2*A; i++)
			for (int j = 0; j < N + 2*A; j++) {
				int a = 0;
				for (int p = i - 1; p <= i + 1; p++)
					for (int q = j - 1; q <= j + 1; q++) {
						a *= 2;
						if (m.isInRange(p, q) && m[p][q] == '#' || !m.isInRange(p,q) && k%2 == 0) a += 1;
					}
				n[i][j] = line[a];
			}
		m = n;
	}
	
	int b = 0;
	for (int i = 0; i < N + 2*A; i++)
		for (int j = 0; j < N + 2*A; j++) {
			if (m[i][j] == '#')
				b++;
		}
	cout << b << endl;

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
