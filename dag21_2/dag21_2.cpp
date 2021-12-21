//dag 21.cpp

#include <iostream>
#include <sstream>
#include <fstream>
//#include <set>
//#include <stack>
#include <deque>
#include <map>
//#include "../matrix/matrix.h"
//#include <algorithm>
using namespace std;

struct node_t {
	int player1;
	int player2;
	int score1;
	int score2;
	int ronde;
	uint64_t nr_universes;

	node_t(int a, int b, int c, int d, int e, uint64_t f) : player1(a), player2(b), score1(c), score2(d), ronde(e), nr_universes(f) {}
	node_t() : player1(0), player2(0), score1(0), score2(0), ronde(0), nr_universes(0) {}
};

deque<node_t> cache;

int main()
{
	cache.push_back(node_t(1, 3, 0, 0, 1, 1));

	map<int, int>count;
	for (int sum_of_dices = 3; sum_of_dices <= 9; sum_of_dices++) count[sum_of_dices] = 0;
	for (int x = 1; x <= 3; x++)
		for (int y = 1; y <= 3; y++)
			for (int z = 1; z <= 3; z++)
				count[x + y + z]++;

	uint64_t uni_count_1 = 0;
	uint64_t uni_count_2 = 0;
	int old_ronde = 1;
	while (!cache.empty()) {
		node_t n = cache.front();
		if (n.ronde > old_ronde) {
			old_ronde = n.ronde;
			cout << n.ronde << " " << cache.size() << endl;
		}
		cache.pop_front();
		if (n.ronde % 2 == 1)
			for (int sum_of_dices = 3; sum_of_dices <= 9; sum_of_dices++) {
				int new_player = n.player1 + sum_of_dices;
				if (new_player > 10) new_player = new_player - 10;
				int new_score = n.score1 + new_player;
				if (new_score >= 21)
					uni_count_1 += n.nr_universes*count[sum_of_dices];
				else
					cache.push_back(node_t(new_player, n.player2, new_score, n.score2, n.ronde + 1, n.nr_universes*count[sum_of_dices]));
			}
		else
			for (int sum_of_dices = 3; sum_of_dices <= 9; sum_of_dices++) {
				int new_player = n.player2 + sum_of_dices;
				if (new_player > 10) new_player = new_player - 10;
				int new_score = n.score2 + new_player;
				if (new_score >= 21)
					uni_count_2 += n.nr_universes*count[sum_of_dices];
				else
					cache.push_back(node_t(n.player1, new_player, n.score1, new_score, n.ronde + 1, n.nr_universes*count[sum_of_dices]));
			}
	}

	cout << "nr universes for player1 to win: " << uni_count_1 << endl;
	cout << "nr universes for player2 to win: " << uni_count_2 << endl;

	return 0;
}
