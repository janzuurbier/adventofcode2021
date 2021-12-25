// dag22.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <set>
//#include <stack>
//#include "../matrix/matrix.h"
#include <algorithm>

using namespace std;

class reboot_step {
public:
	int xmin, xmax, ymin, ymax, zmin, zmax;
	bool on;

	reboot_step(int a = 0, int b = 0, int c = 0, int d = 0, int e = 0, int f = 0, bool on = false) 
		: xmin(a), xmax(b), ymin(c), ymax(d), zmin(e), zmax(f), on(on) {}

	reboot_step(const reboot_step& c) 
		: xmin(c.xmin), xmax(c.xmax), ymin(c.ymin), ymax(c.ymax), zmin(c.zmin), zmax(c.zmax), on(c.on) {}

	friend istream& operator>>(istream& is, reboot_step& step) {
		string s;
		is >> s;
		if (s == "on") step.on = true; else if (s == "off") step.on = false; else cout << "read error" << endl;
		char ch;
		is.get(ch); is.get(ch); is.get(ch);
		is >> step.xmin;
		is.get(); is.get();
		is >> step.xmax;
		is.get();
		is.get(); is.get();
		is >> step.ymin;
		is.get(); is.get();
		is >> step.ymax;
		is.get();
		is.get(); is.get();
		is >> step.zmin;
		is.get(); is.get();
		is >> step.zmax;
		return is;
	}

	friend ostream& operator<<(ostream& os, const reboot_step& step) {
		cout << (step.on ? "on" : "off") << " x=" << step.xmin << ".." << step.xmax;
		cout << ",y=" << step.ymin << ".." << step.ymax;
		cout << ",z=" << step.ymin << ".." << step.ymax;
		return os;
	}

	uint64_t size() const {
			if (xmax >= xmin && ymax >= ymin && zmax >= zmin) {
				uint64_t retval = (xmax - xmin + 1);
				retval *= (ymax - ymin + 1);
				retval *= (zmax - zmin + 1);
				return retval;
			}
		else
			return 0;
	}

	bool isInside(const reboot_step& c) const {
		return xmin >= c.xmin && xmax <= c.xmax && ymin >= c.ymin && ymax <= c.ymax && zmin >= c.zmin && zmax <= c.zmax;
	}

	bool operator<(const reboot_step& c) const {
		if (xmin < c.xmin) return true;
		else if (xmin == c.xmin && ymin < c.ymin) return true;
		else if (xmin == c.xmin && ymin == c.ymin && zmin < c.zmin) return true;
		else if (xmin == c.xmin && ymin == c.ymin && zmin == c.zmin && xmax < c.xmax) return true;
		else if (xmin == c.xmin && ymin == c.ymin && zmin == c.zmin && xmax == c.xmax && ymax < c.ymax) return true;
		else if (xmin == c.xmin && ymin == c.ymin && zmin == c.zmin && xmax == c.xmax && ymax == c.ymax && zmax < c.zmax) return true;
		return false;
	}
};

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	vector<reboot_step> steps;
	while (!input.eof()) {
		reboot_step step;
		input >> step;
		steps.push_back(step);
	}
	vector<reboot_step> steps_rev; 
	for (int i = steps.size() - 1; i >= 0; i--)
		steps_rev.push_back(steps[i]);

	uint64_t count = 0; //will be the answer to part 2

	//use set to order elements and take every number only once
	set<int> sx;
	set<int> sy;
	set<int> sz;
	for (reboot_step c : steps) {
		sx.insert(c.xmin);
		sx.insert(c.xmax + 1);
		sy.insert(c.ymin);
		sy.insert(c.ymax + 1);
		sz.insert(c.zmin);
		sz.insert(c.zmax + 1);
	}
	//put elements in vectors
	vector<int> vx;
	for (int i : sx) vx.push_back(i);
	vector<int> vy;
	for (int i : sy) vy.push_back(i);
	vector<int> vz;
	for (int i : sz) vz.push_back(i);
	//iterate all cubicles
	//the last cube where the cubicle is part of determines if it is on or off
	//if on sum its size to count
	for (int i = 0; i < vx.size() - 1; i++) {
		cout << i << endl;
		for (int j = 0; j < vy.size() - 1; j++)
			for (int k = 0; k < vz.size() - 1; k++) {
				reboot_step cubicle = reboot_step(vx[i], vx[i + 1] - 1, vy[j], vy[j + 1] - 1, vz[k], vz[k + 1] - 1);
				for (reboot_step& c : steps_rev) {
					if (cubicle.isInside(c)) {
						if (c.on) count += cubicle.size();
						break;
					}
				}
			}
	}

	cout << count << endl;

	return 0;
}

