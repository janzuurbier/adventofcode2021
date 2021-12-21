// dag18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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



class number_t {
public:
	int leftval = -1;
	int rightval = -1;
	number_t* leftnumber = nullptr;
	number_t* rightnumber = nullptr;

	number_t() : leftval(-1), rightval(-1),  leftnumber(nullptr), rightnumber(nullptr) {}

	number_t(const number_t& other_number) : leftval(other_number.leftval), rightval(other_number.rightval) {
		if (other_number.leftnumber != nullptr) {
			leftnumber = new number_t(*other_number.leftnumber);
		}
		else
			leftnumber = nullptr;
		if (other_number.rightnumber != nullptr)	
			rightnumber = new number_t(*other_number.rightnumber);
		else 
			rightnumber = nullptr;

	}

	number_t(string s) :leftval(-1), rightval(-1), leftnumber(nullptr), rightnumber(nullptr) {
		stringstream buffer(s);
		buffer >> *this;
	}

	~number_t() {
		if (leftnumber != nullptr) {
			if (leftnumber->leftnumber != nullptr) delete leftnumber->leftnumber;
			if (leftnumber->rightnumber != nullptr) delete leftnumber->rightnumber;
			//delete leftnumber;
		}
		if (rightnumber != nullptr) {
			if (rightnumber->leftnumber != nullptr) delete rightnumber->leftnumber;
			if (rightnumber->rightnumber != nullptr) delete rightnumber->rightnumber;
			//delete rightnumber;
		}
	}

	friend istream& operator>>(istream& is, number_t& number) {
		int ch = is.get(); //openbracket
		ch = is.peek();
		if (ch == '[') {
			number.leftnumber = new number_t;
			is >> *number.leftnumber;
			number.leftval = -1;
		}
		else {
			ch = is.get();
			number.leftval = ch - 48;
			number.leftnumber = nullptr;
		}
		ch = is.get(); //komma
		ch = is.peek();
		if (ch == '[') {
			number.rightnumber = new number_t;
			is >> *number.rightnumber;
			number.rightval = -1;
		}
		else {
			ch = is.get();
			number.rightval = ch - 48;
			number.rightnumber = nullptr;
		}
		ch = is.get(); //close bracket
		return is;		
	}

	friend ostream& operator<<(ostream& os, const number_t& number) {
		os << '[';
		if (number.leftnumber == nullptr)
			os << number.leftval;
		else
			os << *number.leftnumber;
		os << ',';
		if (number.rightnumber == nullptr)
			os << number.rightval;
		else
			os << *number.rightnumber;
		os << ']';
		return os;
	}

	void operator+= (const number_t& rhs) {
		if (leftnumber == nullptr) {
			leftnumber = new number_t;
			leftnumber->leftval = leftval;
			leftnumber->rightval = rightval;
		}
		else {
			number_t* p = leftnumber;
			leftnumber = new number_t;
			leftnumber->leftnumber = p;
			leftnumber->rightnumber = rightnumber;
		}
		rightnumber = new number_t(rhs);	
		leftval = -1;
		rightval = -1;
		reduce();
	}

	number_t operator+(const number_t rhs) const {
		number_t retnumber(*this);
		retnumber += rhs;
		return retnumber;
	}

	bool operator==(const number_t rhs) const {
		if (leftnumber == nullptr && rhs.leftnumber != nullptr || leftnumber != nullptr && rhs.leftnumber == nullptr) return false;
		if (rightnumber == nullptr && rhs.rightnumber != nullptr || rightnumber != nullptr && rhs.rightnumber == nullptr) return false;
		bool retval = true;
		if (leftnumber == nullptr) retval = retval && (leftval == rhs.leftval); else retval = retval && (*leftnumber == *rhs.leftnumber);
		if (rightnumber == nullptr)retval = retval && (rightval == rhs.rightval); else retval = retval && (*rightnumber == *rhs.rightnumber);
		return retval;
	}

	bool operator !=(const number_t rhs) const {
		return !(*this == rhs);
	}

	bool split() {
		bool haschanged = false;
		if (leftnumber == nullptr && leftval >= 10) {
			leftnumber = new number_t;
			leftnumber->leftval = leftval / 2;
			leftnumber->rightval = leftval - leftnumber->leftval;
			haschanged = true;
		}
		else
			if(leftnumber != nullptr ) haschanged = leftnumber->split();
		if (!haschanged) {
			if (rightnumber == nullptr && rightval >= 10) {
				rightnumber = new number_t;
				rightnumber->leftval = rightval / 2;
				rightnumber->rightval = rightval - rightnumber->leftval;
				haschanged = true;
			}
			else
				if (rightnumber != nullptr) haschanged = haschanged || rightnumber->split();
		}
		return haschanged;
	}


	void add_val_left(int val) {
		if (leftnumber == nullptr)
			leftval += val;
		else 
			leftnumber->add_val_left(val);
	}

	void add_val_right(int val) {
		if (rightnumber == nullptr)
			rightval += val;
		else
			rightnumber->add_val_right(val);
	}

	struct uitkomst {
		int first;
		int second;
		bool haschanged;

	};

	uitkomst explode(int level = 0) {
		uitkomst u;
		u.haschanged = false;
		if (leftnumber == nullptr && rightnumber == nullptr && level >= 4) {
			u.first = leftval; 
			u.second = rightval;
		}
		if (leftnumber != nullptr && !u.haschanged) {
			uitkomst p = leftnumber->explode(level + 1);
			u.haschanged = u.haschanged || p.haschanged;
			u.first = p.first;
			u.second = -1;
			if (p.second > 0) {
				if (rightnumber == nullptr) rightval += p.second; else rightnumber->add_val_left(p.second);
			}		
			if (p.first >= 0 && p.second >= 0) {
				leftval = 0;
				leftnumber = nullptr;
				u.haschanged = true;
			}
		}
		if (rightnumber != nullptr && !u.haschanged){
			uitkomst p = rightnumber->explode(level + 1);
			u.haschanged = u.haschanged || p.haschanged;
			if (p.first > 0) {
				if (leftnumber == nullptr) leftval += p.first; else leftnumber->add_val_right(p.first);
			}
			u.first = -1;
			u.second = p.second;
			if (p.first >= 0 && p.second >= 0) {
				rightval = 0;
				rightnumber = nullptr;
				u.haschanged = true;
			}
		}
		return u;
	}

	void reduce() {
		bool haschanged = true;
		while (haschanged) {
			while (haschanged) {
				//cout << *this << endl;
				uitkomst u = explode();
				haschanged = u.haschanged;
			}
			//cout << *this << endl;
			haschanged = split();			
		}
	}

	int magnitude() {
		int a = leftnumber == nullptr ? leftval : leftnumber->magnitude();
		int b = rightnumber == nullptr ? rightval : rightnumber->magnitude();
		return 3 * a + 2 * b;
	}
};


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	vector<number_t> numbers;
	string line;
	while (getline(input, line)) {
		number_t number(line);
		numbers.push_back(number);	
	}

	int max = 0;
	int index1 = 0, index2 = 0;
	for (int i = 0; i < numbers.size(); i++)
		for (int j = i + 1; j < numbers.size(); j++) {
			int sum = (numbers[i] + numbers[j]).magnitude();
			if ( sum > max) {
				max = sum;
				index1 = i;
				index2 = j;
			}
			sum = (numbers[j] + numbers[i]).magnitude();
			if (sum > max) {
				max = sum;
				index1 = j;
				index2 = i;
			}
		}
	cout << numbers[index1] << endl;
	cout << numbers[index2] << endl;
	cout << max;

	return 0;	
}

//