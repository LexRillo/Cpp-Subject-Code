/*
 * main.cpp
 *
 *  Created on: Oct 30, 2017
 *      Author: np183
 *      Module: CO7105
 *      Department of Informatics
 *      University of Leicester
 */


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <exception>
#include "ModelPath.h"
#include "Priority.h"
#include "ModelPriority.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

vector<Path::Direction> convert(const vector<char> v);

class intCont {
public:
	int val_;
	intCont() { val_=0; }
	intCont(int v) { val_=v; }
	friend std::ostream& operator<<(std::ostream& o, intCont& i);
};


int main(int argc, char* argv[]) {
	if (false) {
		Path p;
		p.move(Path::N);
		p.move(Path::N);
		p.move(Path::NE);
		p.move(Path::E);
		p.move(Path::E);
		p.move(Path::SE);
		p.move(Path::S);
		p.move(Path::S);
		p.move(Path::SW);
		p.move(Path::W);
		p.move(Path::NW);
		p.move(Path::N);
		p.move(Path::SW);
		cout << p;
	}
	if (false) {
		{
			Path p1;
			Path p2;
			p1.move(Path::E);
			p2.move(Path::NE);
			Path p3 = p1+p2;
			cout << p3;
		}
		{
			vector<char> v1{'N','N','E','S','W'};
			Path p1(convert(v1));
			vector<char> v2{'E','S','W'};
			Path p2(convert(v2));
			Path p3 = p1-p2;
			cout << p3;

			vector<char> v4{'E','N','N'};
			Path p4(convert(v4));
			Path p5 = p3-p4;
			cout << p5;
			Path p6;
			p6.move(Path::W);
			if (p6 != p5) {
				cout << "Something went wrong" << endl;
			}
		}
	}

	if (true) {

		Priority<intCont> p;
		intCont* arr[2];
		p.push_back(arr[0] = new intCont(5),1,2);
		p.push_back(arr[1] = new intCont(6),2,1);

		cout << "The following should be 5 6" << endl;
		for (auto it=p.begin(Priority<intCont>::ONE) ;
			 it != p.end(Priority<intCont>::ONE) ; ++it) {
			cout << " " << it->val_;
		}
		cout << endl;

		cout << "The following should be 6 5" << endl;
		for (auto it=p.begin(Priority<intCont>::TWO) ;
			 it != p.end(Priority<intCont>::TWO) ; ++it) {
			cout << " " << *it;
		}
		cout << endl;

		intCont* p1=p.pop_front(Priority<intCont>::ONE);
		intCont* p2=p.pop_front(Priority<intCont>::TWO);


		if (!p1 || !p2) {
			cout << "One of the pointers is null" << endl;

		} else {
			if (p1->val_==p2->val_) {
				cout << "Both pops returned the same value" << endl;
			}
			if (p1->val_!=5) {
				cout << "First pop returned something other than 5: " << p1->val_ << endl;
			}
			if (p2->val_!=6) {
				cout << "Second pop returned something other than 6: " << p2->val_ << endl;
			}
		}
		delete arr[0];
		delete arr[1];
	}

	if (true) {
		ModelPriority p;

		intCont* arr[2];
		p.push_back(arr[0] = new intCont(5),1,2);
		p.push_back(arr[1] = new intCont(6),2,1);

		cout << "The following should be 5 6" << endl;
		for (auto it=p.begin(ModelPriority::ONE) ;
				it != p.end(ModelPriority::ONE) ; ++it) {
			cout << " " << it->val_;
		}
		cout << endl;

		cout << "The following should be 6 5" << endl;
		for (auto it=p.begin(ModelPriority::TWO) ;
				it != p.end(ModelPriority::TWO) ; ++it) {
			cout << " " << *it;
		}
		cout << endl;

		intCont* p1=p.pop_front(ModelPriority::ONE);
		intCont* p2=p.pop_front(ModelPriority::TWO);


		if (!p1 || !p2) {
			cout << "One of the pointers is null" << endl;

		} else {
			if (p1->val_==p2->val_) {
				cout << "Both pops returned the same value" << endl;
			}
			if (p1->val_!=5) {
				cout << "First pop returned something other than 5: " << p1->val_ << endl;
			}
			if (p2->val_!=6) {
				cout << "Second pop returned something other than 6: " << p2->val_ << endl;
			}
		}
		delete arr[0];
		delete arr[1];

	}
	return 0;
}

vector<Path::Direction> convert(const vector<char> v) {
	vector<Path::Direction> res;
	for (auto i=v.begin() ; i != v.end() ; ++i) {
		switch(*i) {
		case 'N':
			res.push_back(Path::N);
			break;
		case 'S':
			res.push_back(Path::S);
			break;
		case 'E':
			res.push_back(Path::E);
			break;
		case 'W':
			res.push_back(Path::W);
			break;
		case 'M':
			res.push_back(Path::NW);
			break;
		case 'O':
			res.push_back(Path::NE);
			break;
		case 'R':
			res.push_back(Path::SW);
			break;
		case 'T':
			res.push_back(Path::SE);
			break;
		default:
			throw std::exception();
		}
	}
	return res;
}


std::ostream& operator<<(std::ostream& o, intCont& i) {
	{
		o << i.val_;
		return o;
	}
}

