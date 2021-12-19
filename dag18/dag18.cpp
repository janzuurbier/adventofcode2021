// dag18.cpp : This file contains the 'main' function. Program execution begins and ends there.
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



class number_t {
public:
	int leftval = -1;
	int rightval = -1;
	number_t* leftnumber = nullptr;
	number_t* rightnumber = nullptr;
	number_t* parent;
	bool hasexploded = false;



	number_t() : leftval(-1), rightval(-1),  leftnumber(nullptr), rightnumber(nullptr), parent(nullptr), hasexploded(false) {}

	number_t(number_t* parent) : leftval(-1), rightval(-1), leftnumber(nullptr), rightnumber(nullptr), parent(parent), hasexploded(false) {}

	number_t(const number_t& other_number) : leftval(other_number.leftval), rightval(other_number.rightval), parent(other_number.parent), hasexploded(false) {
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

	number_t(string s) :leftval(-1), rightval(-1), leftnumber(nullptr), rightnumber(nullptr), parent(nullptr), hasexploded(false) {
		stringstream buffer(s);
		buffer >> *this;
	}

	~number_t() {
		if (leftnumber != nullptr) {
			if (leftnumber->leftnumber != nullptr) delete leftnumber->leftnumber;
			if (leftnumber->rightnumber != nullptr) delete leftnumber->rightnumber;
		}
		//delete leftnumber;
		if (rightnumber != nullptr) {
			if (rightnumber->leftnumber != nullptr) delete rightnumber->leftnumber;
			if (rightnumber->rightnumber != nullptr) delete rightnumber->rightnumber;
		}
		//delete rightnumber;
	}

	friend istream& operator>>(istream& is, number_t& number) {
		int ch = is.get(); //openbracket
		ch = is.peek();
		if (ch == '[') {
			number.leftnumber = new number_t(&number);
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
			number.rightnumber = new number_t(&number);
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

	number_t* copy(number_t* number) {
		number_t* retval = new number_t(number->parent);
		if (number->leftnumber != nullptr) {
			retval->leftnumber = copy(number->leftnumber);
		}
		else
			retval->leftnumber = nullptr;
		
		if (number->rightnumber != nullptr) {
			retval->rightnumber = copy(number->rightnumber);
		}
		else
			retval->rightnumber = nullptr;
		retval->leftval = number->leftval;
		retval->rightval = number->rightval;
		
		return retval;
	}

	number_t* add (number_t* rhs) {
		number_t* ret = new number_t();
		ret->leftnumber = this;
		ret->leftnumber->parent = ret;
		ret->rightnumber = rhs;	
		ret->rightnumber->parent = ret;
		ret->leftval = -1;
		ret->rightval = -1;
		return ret;
	}

	void split() {
		if (leftnumber == nullptr && leftval > 10) {
			leftnumber = new number_t(this);
			leftnumber->leftval = leftval / 2;
			leftnumber->rightval = leftval - leftnumber->leftval;
		}
		else
			if(leftnumber != nullptr) leftnumber->split();
		if (rightnumber == nullptr && rightval > 10) {
			rightnumber = new number_t(this);
			rightnumber->leftval = rightval / 2;
			rightnumber->rightval = rightval - rightnumber->leftval;
		}
		else
			if (rightnumber != nullptr) rightnumber->split();
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

	bool explode(int level) {
		if (hasexploded ) return false;
		bool changed = false;
		if (rightnumber == nullptr && leftnumber == nullptr && parent != nullptr && level >= 4) {	
			int a = leftval;
			int b = rightval;
			hasexploded = true;
			if (this == parent->leftnumber){
				if (parent->rightnumber == nullptr)
					parent->rightval += b;
				else
					parent->rightnumber->add_val_left(b);
								
				
				number_t* temp = this;
				while ( temp->parent != nullptr && temp->parent->leftnumber == temp)
					temp = temp->parent;
				if (temp->parent != nullptr && temp->parent->leftnumber != temp) {
					temp = temp->parent;
					if (temp != nullptr && temp->leftnumber == nullptr)
						temp->leftval += a;
					else
						temp->leftnumber->add_val_right(a);
				}
					
				
				parent->leftval = 0;
				parent->leftnumber = nullptr;	
			}
			if (this == parent->rightnumber) {
				if (parent->leftnumber == nullptr)
					parent->leftval += a;
				else
					parent->leftnumber->add_val_right(a);				
		
				number_t* temp = this;
				while (temp->parent != nullptr && temp->parent->rightnumber == temp)
					temp = temp->parent;
				if (temp->parent != nullptr && temp->parent->rightnumber != temp) {
					temp = temp->parent;
					if (temp != nullptr && temp->rightnumber == nullptr)
						temp->rightval += b;
					else
						temp->rightnumber->add_val_left(b);
				}
				
				parent->rightnumber = nullptr;
				parent->rightval = 0;
			}	
			parent = parent->parent;
			changed = true;
		}
		if (leftnumber != nullptr) 
			changed = ( leftnumber->explode(level + 1) || changed);
		if (rightnumber != nullptr)
			changed = ( rightnumber->explode(level + 1) || changed);
		return changed;
	}

	void clear() {
		hasexploded = false;
		if (leftnumber != nullptr) leftnumber->clear();
		if (rightnumber != nullptr) rightnumber->clear();
	}

	void reduce() {
		while (explode(0)) {
			split();
			clear();
		}
	}






};


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string line;
	getline(input, line);
	number_t number(line);
	number_t* n = &number;
	while (getline(input, line)) {
		number_t other_number(line);
		n = n->add(&other_number);
		cout << *n << endl;
		n->reduce();
		cout << *n << endl;
	}
	
	
	
	
	

	return 0;
	
}

//