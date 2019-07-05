/*
 * PathTester.cpp
 *
 *  Created on: 29 Dec 2017
 *      Author: np183
 */

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <exception>

#include "PathTester.h"

using std::set;
using std::multimap;
using std::vector;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::remove_if;
using std::all_of;
using std::stringstream;

PathTester::PathTester() {}

PathTester::~PathTester() {}

void PathTester::testConstruction() {
	func_("testConstruction");
	try {
		Path p;

		auto curr = make_pair(0,0);
		if (p.current() != curr) {
			errorOut_("an empty path should start from (0;0)");
		}
		vector<Path::Direction> v;
		extendRandomPath_(v,LARGE_ARRAY);

		for (auto dir : v) {
			curr = applyDir_(curr,dir);
			p.move(dir);
			if (p.current() != curr) {
				errorOut_("wrong move",1);
			}
		}
	} catch (...) {
		errorOut_("thrown exception with no reason",2);
	}
	testDone_(1);

	try {
		for (unsigned int j=0 ; j < VERY_SMALL_ARRAY ; ++j) {
			vector<Path::Direction> v;
			extendRandomPath_(v,LARGE_ARRAY);

			auto curr = make_pair(0,0);
			for (auto dir : v) {
				curr = applyDir_(curr,dir);
			}

			Path p(v);
			if (p.current() != curr) {
				errorOut_("wrong construction from vector",3);
			}
		}
	} catch (...) {
		errorOut_("thrown exception with no reason",4);
	}
	testDone_(4);

	try {
		vector<Path::Direction> v;
		extendRandomPath_(v,LARGE_ARRAY,false);

		Path p(v);
		errorOut_("did not throw exception for wrong direction",5);
	} catch (std::exception& e) {
		// expected behaviour
	} catch (...) {
		errorOut_("thrown wrong exception",6);
	}

	passOut_("tested the default constructor with move and the constructor from vector");
}

void PathTester::testDim() {
	func_("testDim");
	try {
		for (unsigned int j=0 ; j < VERY_SMALL_ARRAY ; ++j) {
			vector<Path::Direction> v;
			extendRandomPath_(v,LARGE_ARRAY);

			auto curr = make_pair(0,0);

			auto min = make_pair(0,0);
			auto max = make_pair(0,0);

			Path p;
			for (auto dir : v) {
				curr = applyDir_(curr,dir);
				p.move(dir);
				max.first = std::max(max.first,curr.first);
				max.second = std::max(max.second,curr.second);
				min.first = std::min(min.first,curr.first);
				min.second = std::min(min.second,curr.second);
			}

			if (p.maxX() != max.first) {
				errorOut_("maxX returns wrong value");
			}
			if (p.minX() != min.first) {
				errorOut_("minX returns wrong value",1);
			}
			if (p.maxY() != max.second) {
				errorOut_("maxY returns wrong value",2);
			}
			if (p.minY() != min.second) {
				errorOut_("minY returns wrong value",3);
			}
		}
	} catch (...) {
		errorOut_("thrown exception with no reason",4);
	}
	passOut_("created random paths and tested the min/max functions");
}

void PathTester::testVisited() {
	func_("testVisited");
	try {
		Path p;
		for (unsigned int i=0 ; i<LARGE_ARRAY ; ++i) {
			p.move(Path::N);
		}
		for (unsigned int i=0 ; i<=LARGE_ARRAY ; ++i) {
			if (p.visited(0,static_cast<int>(i)) != i) {
				errorOut_("wrong value for simple visited");
			}
		}
	} catch (...) {
		errorOut_("thrown exception with no reason",1);
	}
	testDone_(1);

	try {
		for (unsigned int j=0 ; j < VERY_SMALL_ARRAY ; ++j) {
			vector<Path::Direction> v;
			extendRandomPath_(v,LARGE_ARRAY);

			Path p;
			for (auto dir : v) {
				p.move(dir);
			}

			multimap<pair<int,int>,unsigned int> visited;
			{
				auto curr = make_pair(0,0);
				unsigned int i=0;
				visited.insert(make_pair(curr,i));
				for (auto dir : v) {
					curr = applyDir_(curr,dir);
					visited.insert(make_pair(curr,++i));
				}
			}
			auto curr = make_pair(0,0);
			for (auto dir : v) {
				curr = applyDir_(curr,dir);
				unsigned int location = p.visited(curr.first,curr.second);
				if (all_of(visited.find(curr),visited.upper_bound(curr), [&](pair<pair<int,int>,unsigned int> p) {
					return location != p.second;
				})) {
					errorOut_("wrong value for complex visited",2);
				}
			}
		}
	} catch (...) {
		errorOut_("thrown exception with no reason",3);
	}
	testDone_(3);

	try {
		vector<Path::Direction> v;
		extendRandomPath_(v,LARGE_ARRAY);

		Path p;
		for (auto dir : v) {
			p.move(dir);
		}

		for (int i=-16 ; i<16 ; ++i) {
			for (int j=-16 ; j<16 ; ++j) {
				p.visited(i,j);
			}
		}
		errorOut_("did not throw exception for unvisited place",4);
	} catch (std::exception& e) {
		// Expected behavior
		;
	}
	catch (...) {
		errorOut_("thrown exception with no reason",5);
	}

	passOut_("created random paths and tested the visited function");
}

void PathTester::testComparison() {
	func_("testComparison");
	try {
		for (unsigned int j=0 ; j < VERY_SMALL_ARRAY ; ++j) {
			vector<Path::Direction> v;
			extendRandomPath_(v,SMALL_ARRAY);

			Path p1,p2;
			for (auto dir : v) {
				p1.move(dir);
				p2.move(dir);
			}

			if (!(p1 == p2) || p1 != p2) {
				errorOut_("equivalent paths are not equal");
			}

			extendRandomPath_(v,SMALL_ARRAY);
			Path p3;
			for (auto dir : v) {
				p3.move(dir);
			}

			if (p1 == p3 || !(p1 != p3)) {
				errorOut_("different paths are equal",1);
			}
		}
	} catch (...) {
		errorOut_("thrown exception with no reason",2);
	}
	testDone_(2);

	try {
		for (unsigned int j=0 ; j < VERY_SMALL_ARRAY ; ++j) {
			vector<Path::Direction> v;
			extendRandomPath_(v,SMALL_ARRAY);

			Path p1,p2;
			for (auto dir : v) {
				p1.move(dir);
				p2.move(dir);
			}

			if (!(p1<=p2) || !(p1>= p2)) {
				errorOut_("equivalent paths not leq or geq",3);
			}

			extendRandomPath_(v,SMALL_ARRAY);
			Path p3;
			for (auto dir : v) {
				p3.move(dir);
			}

			if (!(p1 <= p3) || !(p3>=p1)) {
				errorOut_("extending paths is not leq or geq",4);
			}

			Path::Direction dir = randomDir_();
			while (dir == v[SMALL_ARRAY]) {
				dir = randomDir_();
			}

			p2.move(dir);

			if (p2<=p3 || p3>= p2) {
				errorOut_("diverging paths are comparable",5);
			}
		}
	} catch (...) {
		errorOut_("thrown exception with no reason",6);
	}
	testDone_(6);

	try {
		for (unsigned int j=0 ; j < VERY_SMALL_ARRAY ; ++j) {
			vector<Path::Direction> v;
			extendRandomPath_(v,SMALL_ARRAY);

			Path p1,p2;
			for (auto dir : v) {
				p1.move(dir);
				p2.move(dir);
			}

			if ((p1<p2) || (p1>p2)) {
				errorOut_("equivalent paths lt or gt",7);
			}

			extendRandomPath_(v,SMALL_ARRAY);
			Path p3;
			for (auto dir : v) {
				p3.move(dir);
			}

			if (!(p1 < p3) || !(p3>p1)) {
				errorOut_("extending paths is not gt or lt",8);
			}

			Path::Direction dir = randomDir_();
			while (dir == v[SMALL_ARRAY]) {
				dir = randomDir_();
			}

			p2.move(dir);

			if (p2<p3 || p3> p2 || p2>p3 || p3<p2) {
				errorOut_("diverging paths are comparable",9);
			}
		}
	} catch (...) {
		errorOut_("thrown exception with no reason",10);
	}

	passOut_("created random paths and compared them");
}


void PathTester::testLength() {
	func_("testLength");
	try {
		vector<Path::Direction> v;
		extendRandomPath_(v,LARGE_ARRAY + rand()%LARGE_ARRAY);

		Path p;
		unsigned int i=1;
		if (p.length() != i) {
			errorOut_("wrong length");
		}
		for (auto dir : v) {
			p.move(dir);
			if (p.length() != ++i) {
				errorOut_("wrong length");
			}
		}
	} catch (...) {
		errorOut_("thrown exception with no reason",1);
	}

	passOut_("created random paths and tested the length");
}

void PathTester::testSpace() {
	func_("testSpace");
	try {
		vector<Path::Direction> v;
		extendRandomPath_(v,LARGE_ARRAY);

		Path p;
		set<pair<int,int>> s;
		auto curr = make_pair(0,0);
		s.insert(curr);
		if (p.space() != s.size()) {
			errorOut_("wrong space");
		}
		for (auto dir : v) {
			p.move(dir);
			curr = applyDir_(curr,dir);
			s.insert(curr);
			if (p.space() != s.size()) {
				errorOut_("wrong space");
			}
		}
	} catch (...) {
		errorOut_("thrown exception with no reason",1);
	}

	passOut_("created random paths and tested the space");
}

void PathTester::testOperatorPlus() {
	func_("testOperatorPlus");
	try {
		for (unsigned int i=0 ; i<LARGE_ARRAY ; ++i) {
			vector<Path::Direction> v1,v2;
			extendRandomPath_(v1,VERY_SMALL_ARRAY);
			extendRandomPath_(v2,VERY_SMALL_ARRAY);

			Path p1,p2;
			auto curr = make_pair(0,0);
			for (auto dir : v1) {
				p1.move(dir);
				curr = applyDir_(curr,dir);
			}
			for (auto dir : v2) {
				p2.move(dir);
				curr = applyDir_(curr,dir);
			}

			Path p3 = p1+p2;
			if (p3.current() != curr) {
				errorOut_("wrong result to operator+");
			}
		}
	} catch (...) {
		errorOut_("thrown exception with no reason",1);
	}

	passOut_("added random paths");
}

void PathTester::testOperatorMinus() {
	func_("testOperatorMinus");
	try {
		for (unsigned int i=0 ; i<LARGE_ARRAY ; ++i) {
			vector<Path::Direction> v1,v2;
			extendRandomPath_(v1,VERY_SMALL_ARRAY);
			extendRandomPath_(v2,VERY_SMALL_ARRAY);

			Path p1,p2;
			auto curr = make_pair(0,0);
			for (auto dir : v1) {
				p1.move(dir);
				curr = applyDir_(curr,dir);
			}
			for (auto dir : v2) {
				p1.move(dir);
				p2.move(dir);
			}

			Path p3 = p1-p2;
			if (p3.current() != curr) {
				errorOut_("wrong result to operator-");
			}
		}
	} catch (...) {
		errorOut_("thrown exception with no reason",1);
	}
	testDone_(1);

	try {
		for (unsigned int i=0 ; i<LARGE_ARRAY ; ++i) {
			vector<Path::Direction> v1,v2;
			extendRandomPath_(v1,VERY_SMALL_ARRAY);
			extendRandomPath_(v2,VERY_SMALL_ARRAY);

			Path p1,p2;
			for (auto dir : v1) {
				p1.move(dir);
			}
			for (auto dir : v2) {
				p1.move(dir);
				p2.move(dir);
			}

			auto curr = make_pair(0,0);
			for (auto it=v1.rbegin() ; it != v1.rend() ; ++it) {
				auto next  = applyDir_(curr,*it);
				auto app = make_pair(next.first - curr.first,next.second - curr.second);
				curr.first -= app.first;
				curr.second-= app.second;
			}

			Path p3 = p2-p1;
			if (p3.current() != curr) {
				errorOut_("wrong result to operator- that goes beyond the origin",2);
			}
		}
	} catch (...) {
		errorOut_("thrown exception with no reason",3);
	}
	testDone_(3);

	try {
		vector<Path::Direction> v1,v2;
		extendRandomPath_(v1,VERY_SMALL_ARRAY);
		extendRandomPath_(v2,VERY_SMALL_ARRAY);

		Path p1,p2;
		for (auto dir : v1) {
			p1.move(dir);
		}
		Path::Direction dir = randomDir_();
		p1.move(dir);
		Path::Direction odir = randomDir_();
		while (dir == odir) {
			odir = randomDir_();
		}
		p2.move(odir);
		for (auto dir : v2) {
			p1.move(dir);
			p2.move(dir);
		}

		Path p3=p1-p2;
		errorOut_("operator- not thrown exception",4);
	} catch (std::exception& e) {
		// expected behavior
		;
	} catch (...) {
		errorOut_("thrown exception with no reason",5);
	}

	passOut_("subtracted random paths");
}

void PathTester::testOperatorRedir() {
	func_("testOperatorRedir");
	try {
		vector<Path::Direction> v;
		extendRandomPath_(v,VERY_SMALL_ARRAY);

		Path p;
		for (auto dir : v) {
			p.move(dir);
		}

		// Compute min and max
		auto min = make_pair(0,0);
		auto max = make_pair(0,0);
		{
			auto curr = make_pair(0,0);
			for (auto dir : v) {
				curr = applyDir_(curr,dir);
				min.first = std::min(curr.first,min.first);
				min.second = std::min(curr.second,min.second);
				max.first = std::max(curr.first,max.first);
				max.second = std::max(curr.second,max.second);
			}
		}

		// create an array of the right size full with spaces
		char arr[3*(max.first-min.first+1)][3*(max.second-min.second+1)];
		for (unsigned int i=0 ; i<3*(max.first-min.first+1) ; ++i) {
			for (unsigned int j=0 ; j< 3*(max.second-min.second+1) ; ++j) {
				arr[i][j] = ' ';
			}
		}

		// The location in the char array corresponding to curr
		auto curr = make_pair(0,0);
		auto locX = [min,&curr]() {
			return 3*(curr.first-min.first)+1;
		};
		auto locY = [min,&curr]() {
			return 3*(curr.second-min.second)+1;
		};

		// Fill the array with the path
		arr[locX()][locY()] = 's';
		for (auto dir : v) {
			auto next = applyDir_(curr,dir);
			auto app = make_pair(next.first-curr.first,next.second-curr.second);

			char symb;
			if (app.first * app.second < 0) {
				symb = '\\';
			} else if (app.first * app.second > 0) {
				symb = '/';
			} else if (0 == app.first) {
				symb = '|';
			} else { // 0 == app.second
				symb = '-';
			}

			arr[locX()+app.first][locY()+app.second] = symb;
			arr[locX()+2*app.first][locY()+2*app.second] = symb;

			curr = next;
			arr[locX()][locY()] = 'o';
		}
		arr[locX()][locY()] = 'e';

		// send the array to stream
		stringstream res;
		for (unsigned int j= 3*(max.second-min.second+1)-1 ; true ; --j) {
			for (unsigned int i=0 ; i< 3*(max.first-min.first+1) ; ++i) {
				res << arr[i][j];
			}
			res << endl;
			if (0==j) {
				break;
			}
		}

		// compare with implementation
		stringstream out;
		out << p;
		string ress = res.str();
		string outs = out.str();
		if (ress != outs) {
			if (remove_if(ress.begin(),ress.end(),isspace) !=
				remove_if(outs.begin(),outs.end(),isspace)) {
				errorOut_("error in path redirection but only in spaces",1);
			} else {
				errorOut_("error in path redirection");
			}
		}
	} catch (...) {
		errorOut_("thrown exception with no reason",2);
	}

	passOut_("streamed a random path");
}

Path::Direction PathTester::randomDir_(bool legal) {
	if (legal) {
		return static_cast<Path::Direction>(rand()%8);
	} else {
		return static_cast<Path::Direction>(rand()%9);
	}
}

pair<int,int> PathTester::applyDir_(pair<int,int> loc,Path::Direction dir) {
	switch (dir) {
	case Path::N:
	{
		loc.second += 1;
	}
	break;
	case Path::S:
	{
		loc.second -= 1;
	}
	break;
	case Path::E:
	{
		loc.first += 1;
	}
	break;
	case Path::W:
	{
		loc.first -= 1;
	}
	break;
	case Path::NE:
	{
		loc.first += 1;
		loc.second += 1;
	}
	break;
	case Path::NW:
	{
		loc.first -= 1;
		loc.second += 1;
	}
	break;
	case Path::SE:
	{
		loc.first += 1;
		loc.second -= 1;
	}
	break;
	case Path::SW:
	{
		loc.first -= 1;
		loc.second -= 1;
	}
	break;
	}
	return loc;
}

Path::Direction PathTester::difference_(pair<int,int> first, pair<int,int> second) {
	switch (second.first - first.first) {
	case -1:
	{
		switch (second.second - first.second) {
		case -1:
			return Path::SW;
		case 1:
			return Path::NW;
		case 0:
			return Path::W;
		default:
			// throw the exception at the end
			;
		}
	}
	break;
	case 0:
	{
		switch (second.second - first.second) {
		case -1:
			return Path::S;
		case 1:
			return Path::N;
		default:
			// throw the exception at the end
			;
		}
	}
	break;
	case 1:
	{
		switch (second.second - first.second) {
		case -1:
			return Path::SE;
		case 1:
			return Path::NE;
		case 0:
			return Path::E;
		default:
			// throw the exception at the end
			;
		}
	}
	break;
	default:
		// throw the exception at the end
		;
	}
	throw std::exception();
}

void PathTester::extendRandomPath_(vector<Path::Direction>& v, unsigned int size, bool legal) {
	bool fault=legal;
	for (unsigned int i=0 ; i<size || !fault; ++i) {
		Path::Direction dir = randomDir_(legal);
		v.push_back(dir);
		if (!fault && static_cast<int>(dir)==8) {
			fault = true;
			if (i>=900) {
				i=900;
			}
		}
	}
}
