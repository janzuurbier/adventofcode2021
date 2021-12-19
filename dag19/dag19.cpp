// dag19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <set>
//#include <stack>
#include <vector>
#include <map>
#include "../matrix/matrix.h"
#include <algorithm>

using namespace std;
typedef  matrix<int, 3, 3>  mat_t;

const int AANTAL_SCANNERS = 36;

//rotatiematrices zonder spiegeling
vector<mat_t> vind_matrices() {
	vector<mat_t> ret;
	for (int x : {0, 1, 2})
		for (int y : {0, 1, 2})
			for (int z : {0, 1, 2})
				if (x != y && y != z && x != z)
					for (int a : { -1, 1})
						for (int b : { -1, 1})
							for (int c : { -1, 1}) {
								mat_t m(0);
								m[x][0] = a;
								m[y][1] = b;
								m[z][2] = c;
								int det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
								det -= m[1][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1]);
								det += m[2][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1]);
								if (det == 1) ret.push_back(m);
							}
	return ret;
}

class vec_t {
public:
	int x, y, z;

	vec_t(int x, int y, int z) : x(x), y(y), z(z) {}

	vec_t() : x(0), y(0), z(0) {}

	vec_t(string line) {
		istringstream iss(line);
		char komma;
		iss >> x >> komma >> y >> komma >> z;
	}

	friend ostream& operator<<(ostream& os, const vec_t v) {
		os << v.x << ", " << v.y << ", " << v.z;
		return os;
	}

	vec_t operator*(const mat_t& m) const {
		vec_t ret;
		ret.x = m[0][0] * x + m[0][1] * y + m[0][2] * z;
		ret.y = m[1][0] * x + m[1][1] * y + m[1][2] * z;
		ret.z = m[2][0] * x + m[2][1] * y + m[2][2] * z;
		return ret;
	}

	void operator*=(const mat_t& m) {
		int a = m[0][0] * x + m[0][1] * y + m[0][2] * z;
		int b = m[1][0] * x + m[1][1] * y + m[1][2] * z;
		z = m[2][0] * x + m[2][1] * y + m[2][2] * z;
		x = a;
		y = b;
	}

	vec_t operator-(const vec_t& v) const {
		vec_t temp;
		temp.x = x - v.x;
		temp.y = y - v.y;
		temp.z = z - v.z;
		return temp;
	}

	void operator-=(const vec_t& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	bool operator< (const vec_t& v) const {
		return (x < v.x || x == v.x && y < v.y || x == v.x && y == v.y && z < v.z);
	}

	vec_t operator-() const {
		return vec_t(-x, -y, -z);
	}
};

int abs(int x) {
	return x < 0 ? -x : x;
}



int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	vector< mat_t> matrices = vind_matrices();

	//lees alle punten van beacons die de scanners kunnen zien. 
	vector<vector<vec_t>> scanners;
	string line;	
	while (!input.eof()) {
		vector<vec_t> punten;
		getline(input, line);
		while (getline(input, line)) {	
			if (line.size() == 0) break;
			vec_t v(line);
			punten.push_back(v);
		}
		scanners.push_back(punten);
	}

	//matrix<mat_t, AANTAL_SCANNERS, AANTAL_SCANNERS> relatieve_orientaties(mat_t(0));
	vector<mat_t> buffer;
	matrix<int, AANTAL_SCANNERS, AANTAL_SCANNERS> relatieve_orientaties(0);
	matrix<vec_t, AANTAL_SCANNERS, AANTAL_SCANNERS> relatieve_posities(vec_t(0,0,0));

	//voor elk paar scanners vindt de verschuiving en rotatiematrix
	for(int sc1 = 0; sc1 < scanners.size(); sc1++)
		for (int sc2 = sc1 + 1; sc2 < scanners.size(); sc2++) { 
		vec_t verschuiving(0, 0, 0);
		int aantal_overeenkomsten = 0;
		mat_t orientatie(0);

		for (mat_t mat : matrices) {
			vector<vec_t> temp;
			for (int i = 0; i < scanners[sc2].size(); i++) {
				temp.push_back(scanners[sc2][i] * mat);
			}

			//tel hoe vaak een verschuiving voorkomt
			map<vec_t, int> m;
			for (vec_t v : scanners[sc1])
				for (vec_t w : temp) {
					vec_t verschil = w - v;
					if (m.count(verschil) == 0) m[verschil] = 1; else m[verschil]++;
				}

			int max = 0;
			vec_t diff;
			for (auto it = m.begin(); it != m.end(); it++) {
				if (it->second >= max) {
					max = it->second;
					diff = it->first;
				}
			}
			if (max > aantal_overeenkomsten) {
				verschuiving = diff;
				aantal_overeenkomsten = max;
				orientatie = mat;
			}
			
		}

		if (aantal_overeenkomsten > 11) {
			cout << "aantal overeenkomende punten tussen " << sc1 << " en " << sc2 << ": " << aantal_overeenkomsten << endl;
			cout << "verschuiving: " << verschuiving << endl;
			cout << "orientatie: " << endl << orientatie << endl << endl;
			buffer.push_back(orientatie);
			relatieve_orientaties[sc2][sc1] = buffer.size()-1;
			relatieve_posities[sc2][sc1] = verschuiving;
			mat_t inverse(0);
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					inverse[i][j] = orientatie[j][i];
			buffer.push_back(inverse);
			relatieve_orientaties[sc1][sc2] = buffer.size()-1;
			relatieve_posities[sc1][sc2] =  -verschuiving;
		}		
	}

	//vind paden om om te rekenen naar orientatie scanner0
	vector<int> paden[AANTAL_SCANNERS];
	paden[0].push_back(0);
	set<int> volgende;
	set<int> afgehandeld;
	set<int> nognietafgehandeld;
	for (int i = 1; i < AANTAL_SCANNERS; i++)
		nognietafgehandeld.insert(i);
	set<int> nieuw;
	volgende.insert(0);
	afgehandeld.insert(0);

	bool changed = true;
	while (afgehandeld.size() < AANTAL_SCANNERS && changed) {
		changed = false;
		for (int i : volgende)
			for (int j : nognietafgehandeld) {
				if ((relatieve_orientaties[j][i] != 0 || relatieve_orientaties[i][j] != 0) && afgehandeld.count(j) == 0) {
					for (int p : paden[i])
						paden[j].push_back(p);
					paden[j].push_back(j);

					nieuw.insert(j);
					afgehandeld.insert(j);
					changed = true;
				}
			}

		volgende.clear();
		for (int x : nieuw) {
			volgende.insert(x);
			nognietafgehandeld.erase(x);
			afgehandeld.insert(x);
		}
		nieuw.clear();
	}

	//print alle paden en maak een kopie voor later
	vector<int> paden_kopie[AANTAL_SCANNERS];
	for (int i = 0; i < AANTAL_SCANNERS; i++) {
		for (int x : paden[i]) {
			cout << x << " ";
			paden_kopie[i].push_back(x);
		}
		cout << endl;
	}

	//alles beacons omrekenen naar orientatie van scanner0
	for (int i = 0; i < AANTAL_SCANNERS; i++) {
		int m = paden[i].back();
		paden[i].pop_back();
		while (!paden[i].empty()) {
			int n = paden[i].back();
			paden[i].pop_back();
			if (m > n) {
				for (int k = 0; k < scanners[i].size(); k++) {
					scanners[i][k] *= buffer[relatieve_orientaties[m][n]];
					scanners[i][k] -= relatieve_posities[m][n];
				}
			}
			else {
				for (int k = 0; k < scanners[i].size(); k++) {
					scanners[i][k] -= relatieve_posities[m][n];
					scanners[i][k] *= buffer[relatieve_orientaties[m][n]];
				}

			}
			m = n;
		}
	}

	//vind aantal beacons
	set<vec_t> alle_beacons;
	for (int i = 0; i < AANTAL_SCANNERS; i++)
		for (vec_t v : scanners[i]) {
			alle_beacons.insert(v);
		}
	cout << alle_beacons.size() << endl;

	//voor deel 2 moeten we dezelfde berekening doen
	//niet voor de punten van de beacons
	//maar voor de plaats van de scanner.
	vector<vec_t> alle_scanners;
	for (int i = 0; i < AANTAL_SCANNERS; i++)
		alle_scanners.push_back(vec_t(0, 0, 0));
	for (int i = 0; i < AANTAL_SCANNERS; i++) {
		int m = paden_kopie[i].back();
		paden_kopie[i].pop_back();
		while (!paden_kopie[i].empty()) {
			int n = paden_kopie[i].back();
			paden_kopie[i].pop_back();
			if (m > n) {			
				alle_scanners[i] *= buffer[relatieve_orientaties[m][n]];
				alle_scanners[i] -= relatieve_posities[m][n];			
			}
			else {
				alle_scanners[i] -= relatieve_posities[m][n];
				alle_scanners[i] *= buffer[relatieve_orientaties[m][n]];
			}
			m = n;
		}
	}

	int maxdist = 0;
	for(vec_t v : alle_scanners)
		for (vec_t w : alle_scanners) {
			int manhattandistance = abs(v.x - w.x) + abs(v.y - w.y) + abs(v.z - w.z);
			if (manhattandistance > maxdist)
				maxdist = manhattandistance;
		}
	cout << "largest distance: " << maxdist << endl;
		


	return 0;
}

