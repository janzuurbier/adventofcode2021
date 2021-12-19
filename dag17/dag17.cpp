// dag17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "stdafx.h"
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
const int minx = 277, maxx = 318, miny = -92, maxy = -53;

int main()
{
	//which startspeed is feasible  in x direction?
	vector<int> feasible_x_speed;
	for (int startspeed = 1; startspeed <= maxx; startspeed++) {	
		int x = 0;
		int v = startspeed;
		while (true) {
			x += v;
			if (v > 0) v--;
			if (x >= minx && x <= maxx) {
				feasible_x_speed.push_back(startspeed);
				break;
			}
			if (v == 0 || x > maxx) 
				break;
		}
	}
	//which startspeed is feasible for speed in y direction?
	//if startspeed is larger than 0 y will become 0 again with speed = -startspeed.
	//if the y coordinate of the probe wil be lower than miny in one step it kan never enter the target araa
	//because it wil go past it in one step. 
	vector<int> feasible_y_speed;
	for (int startspeed = miny; startspeed < -miny; startspeed++) {
		int y = 0;
		int v = startspeed;
		while (true) {
			y += v;
			v--;
			if (y >= miny && y <= maxy) {
				feasible_y_speed.push_back(startspeed);
				break;
			}
			if (y < miny) break;
		}
	}

	//is there an vx for a feasible vy so that the probe comes in the area.
	//what is the max for vy?
	set<pair<int, int>> initial_velocities;
	int max_height = 0;
	sort(feasible_y_speed.begin(), feasible_y_speed.end(), [](const int& a, const int& b) -> bool { return a > b; } );
	for (int vy : feasible_y_speed) {
		for (int vx : feasible_x_speed) {
			int x = 0, y = 0;
			int vxc = vx, vyc = vy;
			while (x < maxx && y > miny) {
				x += vxc;
				y += vyc;
				if (vxc > 0) vxc--;
				vyc--;
				if (x >= minx && x <= maxx && y >= miny && y <= maxy) {
					int height = (vy * (vy + 1)) / 2;
					if (height > max_height) max_height = height;
					initial_velocities.insert(pair<int, int>(vx, vy));
				}
			}
		}
	}
	cout << "max_height: " << max_height << endl;
	cout << "disticht nr of initial velocities: " <<  initial_velocities.size() << endl;	
}

