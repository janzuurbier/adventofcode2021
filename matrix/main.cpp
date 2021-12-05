#include "stdafx.h"
#include "matrix.h"
#include <iostream>
#include <vector>

using namespace std;


int main()
{
	vector<matrix<int>> cube ;
	cube.push_back(matrix<int>(2,2,0));
	cube.push_back(matrix<int>(2, 2, 0));
	cube[0][1][0] = 3;



	cout << cube[0] << endl << endl << cube[1];


}