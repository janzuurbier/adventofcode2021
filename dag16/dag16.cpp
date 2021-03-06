// dag16.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
//#include <set>
//#include <stack>
//#include "../matrix/matrix.h"
//#include <algorithm>

using namespace std;

string hex_to_bin(char ch) {
	switch (ch) {
	case '0': return "0000"; break;
	case '1': return "0001"; break;
	case '2': return "0010"; break;
	case '3': return "0011"; break;
	case '4': return "0100"; break;
	case '5': return "0101"; break;
	case '6': return "0110"; break;
	case '7': return "0111"; break;
	case '8': return "1000"; break;
	case '9': return "1001"; break;
	case 'A': return "1010"; break;
	case 'B': return "1011"; break;
	case 'C': return "1100"; break;
	case 'D': return "1101"; break;
	case 'E': return "1110"; break;
	case 'F': return "1111"; break;
	default: return "";
	}
}

class packet {
public:
	int version = 0;
	int type = 0;
	char id = ' ';
	int total_length = 0;
	int nr_subpackets = 0;
	int len_subpackets = 0;
	vector<packet> subpackets;
	uint64_t value = 0;

	int count_sum_version_nrs() {
		int retval = version;
		for (packet p : subpackets)
			retval += p.count_sum_version_nrs();
		return retval;
	}

	uint64_t calc_value() {
		switch (type) {
		case 0: {
			uint64_t sum = 0;
			for (packet p : subpackets) sum += p.calc_value();
			return sum;
		}
		case 1: {
			uint64_t prod = 1;
			for (packet p : subpackets) prod *= p.calc_value();
			return prod;
		}
		case 2: {
			uint64_t min = subpackets[0].calc_value();
			for (packet p : subpackets) if (p.calc_value() < min) min = p.calc_value();
			return min;
		}
		case 3: {
			uint64_t max = subpackets[0].calc_value();
			for (packet p : subpackets) if (p.calc_value() > max) max = p.calc_value();
			return max;
		}
		case 4: {
			return value;
		}
		case 5: {
			return subpackets[0].calc_value() > subpackets[1].calc_value() ? 1 : 0;
		}
		case 6: {
			return subpackets[0].calc_value() < subpackets[1].calc_value() ? 1 : 0;
		}
		case 7: {
			return subpackets[0].calc_value() == subpackets[1].calc_value() ? 1 : 0;
		}
		default: {
			return 0;
		}
		}
	}

	friend istream& operator >>(istream& is, packet& p) {
		p.version = 0;
		for (int i = 0; i < 3; i++) {
			char ch = is.get();
			p.version *= 2;
			p.version += ch - 48;
		}
		p.total_length += 3;
		p.type = 0;
		for (int i = 0; i < 3; i++) {
			char ch = is.get();
			p.type *= 2;
			p.type += ch - 48;
		}
		p.total_length += 3;
		if (p.type == 4) {
			p.value = 0;		
			while (true){
				bool doorgaan = (is.get() == '1');
				for (int i = 0; i < 4; i++) {
					char ch = is.get();
					p.value *= 2;
					p.value += ch - 48;
				}
				p.total_length += 5;
				if (!doorgaan) break;
			}
		}
		else {
			p.id = is.get();
			p.total_length++;
			if (p.id == '1') {
				p.nr_subpackets = 0;
				for (int i = 0; i < 11; i++) {
					char ch = is.get();
					p.nr_subpackets *= 2;
					p.nr_subpackets += ch - 48;
				}
				p.total_length += 11;
				for (int i = 0; i < p.nr_subpackets; i++) {
					packet q;
					is >> q;
					p.subpackets.push_back(q);
					p.total_length += q.total_length;
				}
			}
			else if (p.id == '0') {
				p.len_subpackets = 0;
				for (int i = 0; i < 15; i++) {
					char ch = is.get();
					p.len_subpackets *= 2;
					p.len_subpackets += ch - 48;
				}
				p.total_length += 15;
				int length_read = 0;
				while (length_read < p.len_subpackets) {
					packet q;
					is >> q;
					p.subpackets.push_back(q);
					length_read += q.total_length;
					p.total_length += q.total_length;
				}
			}
		}
		return is;
	}
};


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	stringstream buffer;

	while(!input.eof()) {
		char ch = input.get();
		buffer << hex_to_bin(ch);
	}

	packet p;
	buffer >> p;

	cout << "part 1: " << p.count_sum_version_nrs() << endl;
	cout << "part 2: " << p.calc_value() << endl;

	return 0;
}

