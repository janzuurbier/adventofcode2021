// dag12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
//#include <vector>
//#include <sstream>
#include <fstream>
#include <set>
#include <map>
//#include <stack>

using namespace std;


/**calculates the number of paths to "end".
* param cave is the cave from where you calculate the number of paths.
* param connections is the connection_map use for calculating the number
* for the connections we use a map with key a cave and value the other caves the cave is connected to.
* param small_caves_visited is a set of caves you have visited at least once
* param twice becomes true if you have visited one of the caves twice
**/

int find_nr_paths(string cave, map<string, set<string>>& connections, set<string>& small_caves_visited, bool twice = false) {
	//if you reach end, you found one path.
	if (cave == "end") {
		return 1;
	}

	int retval = 0;

	if (cave[0] >= 'A' && cave[0] <= 'Z') {
		for (string next_cave : connections[cave]) {
			retval += find_nr_paths(next_cave, connections, small_caves_visited, twice);
		}
	}
	if (cave[0] >= 'a' && cave[0] <= 'z') {
		if (small_caves_visited.count(cave) == 0 && !twice) {
			//you can come back but remember you have visited this cave.
			//insert it in the set with visited caves.
			//but because we use reference parameter we have to make a copy this time
			set<string> new_small_caves_visited = small_caves_visited;
			new_small_caves_visited.insert(cave);
			for (string next_cave : connections[cave]) {
				retval += find_nr_paths(next_cave, connections, new_small_caves_visited, false);
			}
		}
		else if (small_caves_visited.count(cave) == 0 && twice) {
			//now you can't come back for you have visited another cave twice
			//remove all connections with this cave as an endpoint. You can't use them in the rest of the path.
			//because of the reference parameter we have to make a copy this time.
			//twice remains true
			map<string, set<string>> new_connections = connections;
			for (string next_cave : connections[cave]) {
				new_connections[next_cave].erase(cave);
			}
			for (string next_cave : new_connections[cave]) {
				retval += find_nr_paths(next_cave, new_connections, small_caves_visited, true);
			}
		}
		else if (small_caves_visited.count(cave) == 1 && !twice && cave != "start") {
			//now you also can't come back.
			//twice becomes true for you have visited this cave twice
			map<string, set<string>> new_connections = connections;
			for (string next_cave : connections[cave]) {
				new_connections[next_cave].erase(cave);
			}
			for (string next_cave : new_connections[cave]) {
				retval += find_nr_paths(next_cave, new_connections, small_caves_visited, true);
			}
		}
	}
	return retval;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	map<string, set<string>> connections;
	string line;
	while (getline(input, line)) {
		size_t pos = line.find('-');
		string a = line.substr(0, pos);
		string b = line.substr(pos + 1);
		set<string> empty;
		connections[a].insert(b);
		connections[b].insert(a);
	}

	set<string> caves_visited;
	cout << find_nr_paths("start", connections, caves_visited) << endl;
	return 0;
}
