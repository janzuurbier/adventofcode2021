// dag21_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

class die_t {
	int die = 0;

public:
	int nr_throws = 0;

	int throwdie() {
		nr_throws++;
		die++;
		die = (die - 1) % 100 + 1;
		return die;
	}
};

int main() {
	int player1 = 4;
	int player2 = 8;
	int score1 = 0;
	int score2 = 0;
	die_t die;

	while (true) {
		for (int i = 0; i < 3; i++) player1 += die.throwdie();
		player1 = (player1 - 1) % 10 + 1;
		score1 += player1;
		if (score1 >= 1000) break;
		for (int i = 0; i < 3; i++) player2 += die.throwdie();
		player2 = (player2 - 1) % 10 + 1;
		score2 += player2;
		if (score2 >= 1000) break;
	}

	int losingscore = score1 < 1000 ? score1 : score2;
	cout << die.nr_throws << " " << losingscore << " " << die.nr_throws * losingscore << endl;

	return 0;
}
