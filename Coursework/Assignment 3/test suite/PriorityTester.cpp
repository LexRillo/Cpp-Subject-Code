/*
 * PriorityTester.cpp
 *
 *  Created on: 28 Dec 2017
 *      Author: np183
 */

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include "PriorityTester.h"

using std::string;
using std::vector;
using std::map;
using std::set;
using std::pair;
using std::make_pair;
using std::stringstream;

PriorityTester::PriorityTester() {}

PriorityTester::~PriorityTester() {}

void PriorityTester::testCtor() {
	func_("testCtor");
	{
		Priority<string> ps;
		if (ps.pop_front(Priority<string>::ONE) ||
			ps.pop_front(Priority<string>::TWO)) {
			errorOut_("default constructor<string> not empty");
		}
	}
	testDone_();

	{
		Priority<double> pd;
		if (pd.pop_front(Priority<double>::ONE) ||
				pd.pop_front(Priority<double>::TWO)) {
			errorOut_("default constructor<double> not empty",1);
		}
	}
	passOut_("default constructor built empty container");
}

void PriorityTester::testPopSep() {
	func_("testPopSep");

	{
		Priority<string> ps;
		vector<string*> strings;
		makePriority_(LARGE_ARRAY,ps,strings,KEYONE);

		for (unsigned int i=0 ; i<LARGE_ARRAY ; ++i) {
			string* temp = ps.pop_front(Priority<string>::ONE);
			if (!temp || temp != strings[i]) {
				errorOut_("wrong item extracted (Priority<string>)");
			}
		}
		if (ps.pop_front(Priority<string>::ONE) ||
			ps.pop_front(Priority<string>::TWO)) {
			errorOut_("priority should be empty (Priority<string>)",1);
		}

		for (auto p : strings) {
			delete p;
		}
	}
	{
		Priority<string> ps;
		vector<string*> strings;
		makePriority_(LARGE_ARRAY,ps,strings,KEYTWO);

		for (unsigned int i=0 ; i<LARGE_ARRAY ; ++i) {
			string* temp = ps.pop_front(Priority<string>::TWO);
			if (!temp || temp != strings[i]) {
				errorOut_("wrong item extracted (Priority<string>)");
			}
		}
		if (ps.pop_front(Priority<string>::TWO) ||
			ps.pop_front(Priority<string>::ONE)) {
			errorOut_("priority should be empty (Priority<string>)",1);
		}

		for (auto p : strings) {
			delete p;
		}
	}
	testDone_(1);
	{
		Priority<double> pd;
		vector<double*> doubles;
		makePriority_(LARGE_ARRAY,pd,doubles,KEYONE);

		for (unsigned int i=0 ; i<LARGE_ARRAY ; ++i) {
			double* temp = pd.pop_front(Priority<double>::ONE);
			if (!temp || temp != doubles[i]) {
				errorOut_("wrong item extracted (Priority<double>)",2);
			}
		}
		if (pd.pop_front(Priority<double>::ONE) ||
			pd.pop_front(Priority<double>::TWO)) {
			errorOut_("priority should be empty (Priority<double>)",3);
		}

		for (auto p : doubles) {
			delete p;
		}
	}
	{
		Priority<double> pd;
		vector<double*> doubles;
		makePriority_(LARGE_ARRAY,pd,doubles,KEYTWO);

		for (unsigned int i=0 ; i<LARGE_ARRAY ; ++i) {
			double* temp = pd.pop_front(Priority<double>::TWO);
			if (!temp || temp != doubles[i]) {
				errorOut_("wrong item extracted (Priority<double>)",2);
			}
		}
		if (pd.pop_front(Priority<double>::TWO) ||
			pd.pop_front(Priority<double>::ONE)) {
			errorOut_("priority should be empty (Priority<double>)",3);
		}

		for (auto p : doubles) {
			delete p;
		}
	}

	passOut_("added elements and removed them with pop");
}

void PriorityTester::testPopMix() {
	func_("testPopMix");

	{
		Priority<string> ps;
		vector<string*> strings;
		makePriority_(LARGE_ARRAY,ps,strings,KEYBOTH);

		for (unsigned int i=0 ; i<LARGE_ARRAY ; ++i) {
			string* temp = nullptr;
			if (i%2) {
				temp = ps.pop_front(Priority<string>::ONE);
			} else {
				temp = ps.pop_front(Priority<string>::TWO);
			}
			string* otemp = strings[i];
			if (!temp || temp != otemp) {
				errorOut_("wrong item extracted (Priority<string>)");
			}
		}
		if (ps.pop_front(Priority<string>::ONE) ||
			ps.pop_front(Priority<string>::TWO)) {
			errorOut_("priority should be empty (Priority<string>)",1);
		}

		for (auto p : strings) {
			delete p;
		}
	}
	testDone_(1);
	{
		Priority<double> pd;
		vector<double*> doubles;
		makePriority_(LARGE_ARRAY,pd,doubles,KEYBOTH);

		for (unsigned int i=0 ; i<LARGE_ARRAY ; ++i) {
			double* temp = nullptr;
			if (i%2) {
				temp = pd.pop_front(Priority<double>::ONE);
			} else {
				temp = pd.pop_front(Priority<double>::TWO);
			}
			if (!temp || temp != doubles[i]) {
				errorOut_("wrong item extracted (Priority<doubles>)",2);
			}
		}
		if (pd.pop_front(Priority<double>::ONE) ||
			pd.pop_front(Priority<double>::TWO)) {
			errorOut_("priority should be empty (Priority<doubles>)",3);
		}

		for (auto p : doubles) {
			delete p;
		}
	}

	passOut_("added elements and removed them with pop in mixed order");
}

void PriorityTester::testSame() {
	func_("testSame");

	{
		Priority<string> ps;

		set<string*> first;
		set<string*> second;
		for (unsigned int i=0 ; i<LARGE_ARRAY ; ++i) {
			string* temp=new string(std::move(randString_(VERY_SMALL_ARRAY)));
			if (rand()%5<1) {
				first.insert(temp);
				ps.push_back(temp,0,1);
			} else {
				second.insert(temp);
				ps.push_back(temp,1,1);
			}
		}


		while (!first.empty()) {
			string* temp = ps.pop_front(Priority<string>::ONE);
			if (temp == nullptr) {
				errorOut_("priority is empty prematurely (Priority<string>)");
				break;
			}
			auto it = first.find(temp);
			if (it == first.end()) {
				errorOut_("wrong item extracted (Priority<string>)",1);
			} else {
				delete *it;
				first.erase(it);
			}
		}

		while (!second.empty()) {
			string* temp = ps.pop_front(Priority<string>::TWO);
			if (temp == nullptr) {
				errorOut_("priority is empty prematurely (Priority<string>)");
				break;
			}
			auto it = second.find(temp);
			if (it == second.end()) {
				errorOut_("wrong item extracted (Priority<string>)",1);
			} else {
				delete *it;
				second.erase(it);
			}
		}

		if (ps.pop_front(Priority<string>::ONE) ||
			ps.pop_front(Priority<string>::TWO)) {
			errorOut_("priority should be empty (Priority<string>)",2);
		}

		for (auto p : first) {
			delete p;
		}
		for (auto p : second) {
			delete p;
		}
	}
	{
		Priority<string> ps;

		set<string*> first;
		set<string*> second;
		for (unsigned int i=0 ; i<LARGE_ARRAY ; ++i) {
			string* temp=new string(std::move(randString_(VERY_SMALL_ARRAY)));
			if (rand()%5<1) {
				first.insert(temp);
				ps.push_back(temp,1,0);
			} else {
				second.insert(temp);
				ps.push_back(temp,1,1);
			}
		}


		while (!first.empty()) {
			string* temp = ps.pop_front(Priority<string>::TWO);
			if (temp == nullptr) {
				errorOut_("priority is empty prematurely (Priority<string>)");
				break;
			}
			auto it = first.find(temp);
			if (it == first.end()) {
				errorOut_("wrong item extracted (Priority<string>)",1);
			} else {
				delete *it;
				first.erase(it);
			}
		}

		while (!second.empty()) {
			string* temp = ps.pop_front(Priority<string>::ONE);
			if (temp == nullptr) {
				errorOut_("priority is empty prematurely (Priority<string>)");
				break;
			}
			auto it = second.find(temp);
			if (it == second.end()) {
				errorOut_("wrong item extracted (Priority<string>)",1);
			} else {
				delete *it;
				second.erase(it);
			}
		}

		if (ps.pop_front(Priority<string>::ONE) ||
			ps.pop_front(Priority<string>::TWO)) {
			errorOut_("priority should be empty (Priority<string>)",2);
		}

		for (auto p : first) {
			delete p;
		}
		for (auto p : second) {
			delete p;
		}
	}
	testDone_(2);

	{
		Priority<double> pd;

		set<double*> first;
		set<double*> second;
		for (unsigned int i=0 ; i<LARGE_ARRAY ; ++i) {
			double* temp=new double(randFloat_(LARGE_ARRAY,LARGE_ARRAY));
			if (rand()%5<1) {
				first.insert(temp);
				pd.push_back(temp,0,1);
			} else {
				second.insert(temp);
				pd.push_back(temp,1,1);
			}
		}


		while (!first.empty()) {
			double* temp = pd.pop_front(Priority<double>::ONE);
			if (temp == nullptr) {
				errorOut_("priority is empty prematurely (Priority<double>)",3);
				break;
			}
			auto it = first.find(temp);
			if (it == first.end()) {
				errorOut_("wrong item extracted (Priority<double>)",4);
			} else {
				delete *it;
				first.erase(it);
			}
		}

		while (!second.empty()) {
			double* temp = pd.pop_front(Priority<double>::TWO);
			if (temp == nullptr) {
				errorOut_("priority is empty prematurely (Priority<double>)",3);
				break;
			}
			auto it = second.find(temp);
			if (it == second.end()) {
				errorOut_("wrong item extracted (Priority<double>)",4);
			} else {
				delete *it;
				second.erase(it);
			}
		}

		if (pd.pop_front(Priority<double>::ONE) ||
			pd.pop_front(Priority<double>::TWO)) {
			errorOut_("priority should be empty (Priority<double>)",5);
		}

		for (auto p : first) {
			delete p;
		}
		for (auto p : second) {
			delete p;
		}
	}
	{
		Priority<double> pd;

		set<double*> first;
		set<double*> second;
		for (unsigned int i=0 ; i<LARGE_ARRAY ; ++i) {
			double* temp=new double(randFloat_(LARGE_ARRAY,LARGE_ARRAY));
			if (rand()%5<1) {
				first.insert(temp);
				pd.push_back(temp,1,0);
			} else {
				second.insert(temp);
				pd.push_back(temp,1,1);
			}
		}


		while (!first.empty()) {
			double* temp = pd.pop_front(Priority<double>::TWO);
			if (temp == nullptr) {
				errorOut_("priority is empty prematurely (Priority<double>)",3);
				break;
			}
			auto it = first.find(temp);
			if (it == first.end()) {
				errorOut_("wrong item extracted (Priority<double>)",4);
			} else {
				delete *it;
				first.erase(it);
			}
		}

		while (!second.empty()) {
			double* temp = pd.pop_front(Priority<double>::ONE);
			if (temp == nullptr) {
				errorOut_("priority is empty prematurely (Priority<double>)",3);
				break;
			}
			auto it = second.find(temp);
			if (it == second.end()) {
				errorOut_("wrong item extracted (Priority<double>)",4);
			} else {
				delete *it;
				second.erase(it);
			}
		}

		if (pd.pop_front(Priority<double>::ONE) ||
			pd.pop_front(Priority<double>::TWO)) {
			errorOut_("priority should be empty (Priority<double>)",5);
		}

		for (auto p : first) {
			delete p;
		}
		for (auto p : second) {
			delete p;
		}
	}

	passOut_("added elements and removed them with pop in mixed order");
}

void PriorityTester::testIterator() {
	func_("testIterator");
	{
		Priority<string> ps;
		vector<string*> strings;
		for (int i=0 ; i<LARGE_ARRAY ; ++i) {
			string* temp=nullptr;
			strings.push_back(temp=new string(std::move(randString_(VERY_SMALL_ARRAY))));
			ps.push_back(temp,i,LARGE_ARRAY-i);
		}
		{
			auto sit = strings.begin();
			auto pit = ps.begin(Priority<string>::ONE);
			for ( ; sit != strings.end() && pit != ps.end(Priority<string>::ONE) ;
					++sit, ++pit) {
				if (*sit != pit.operator ->()) {
					errorOut_("wrong iteration order (Priority<string>)");
				}
			}

			if (sit != strings.end() || pit != ps.end(Priority<string>::ONE)) {
				errorOut_("iteration too long or too short (Priority<string>)",1);
			}
		}
		{
			auto sit = strings.rbegin();
			auto pit = ps.begin(Priority<string>::TWO);
			for ( ; sit != strings.rend() && pit != ps.end(Priority<string>::TWO) ;
					++sit, ++pit) {
				if (*sit != pit.operator ->()) {
					errorOut_("wrong iteration order (Priority<string>)");
				}
			}

			if (sit != strings.rend() || pit != ps.end(Priority<string>::TWO)) {
				errorOut_("iteration too long or too short (Priority<string>)",1);
			}
		}
		for (auto p : strings) {
			delete p;
		}
	}
	testDone_(1);

	{
		Priority<double> pd;
		vector<double*> doubles;
		for (int i=0 ; i<LARGE_ARRAY ; ++i) {
			double* temp=nullptr;
			doubles.push_back(temp=new double(this->randFloat_(VERY_LARGE_ARRAY,VERY_LARGE_ARRAY)));
			pd.push_back(temp,i,LARGE_ARRAY-i);
		}
		{
			auto dit = doubles.begin();
			auto pit = pd.begin(Priority<double>::ONE);
			for ( ; dit != doubles.end() && pit != pd.end(Priority<double>::ONE) ;
					++dit, ++pit) {
				if (*dit != pit.operator ->()) {
					errorOut_("wrong iteration order (Priority<double>)",2);
				}
			}

			if (dit != doubles.end() || pit != pd.end(Priority<double>::ONE)) {
				errorOut_("iteration too long or too short (Priority<double>)",3);
			}
		}
		{
			auto dit = doubles.rbegin();
			auto pit = pd.begin(Priority<double>::TWO);
			for ( ; dit != doubles.rend() && pit != pd.end(Priority<double>::TWO) ;
					++dit, ++pit) {
				if (*dit != pit.operator ->()) {
					errorOut_("wrong iteration order (Priority<double>)",2);
				}
			}

			if (dit != doubles.rend() || pit != pd.end(Priority<double>::TWO)) {
				errorOut_("iteration too long or too short (Priority<double>)",3);
			}
		}
		for (auto p : doubles) {
			delete p;
		}
	}


	passOut_("added elements and checked that they are iterated through correctly");
}

void PriorityTester::testItAccess() {
	func_("testItAccess");

	{
		Priority<string> ps;
		string *temp = new string(std::move(randString_(VERY_SMALL_ARRAY)));
		ps.push_back(temp,0,0);
		auto it = ps.begin(Priority<string>::ONE);
		if (it.operator->() != temp) {
			errorOut_("access through operator-> return wrong value (Priority<string>)");
		}
		if (*it != *temp) {
			errorOut_("access through operator* return wrong value (Priority<string>)",1);
		}
		delete temp;
	}
	testDone_(1);
	{
		Priority<double> pd;
		double *temp = new double(randFloat_(VERY_LARGE_ARRAY,VERY_LARGE_ARRAY));
		pd.push_back(temp,0,0);
		auto it = pd.begin(Priority<double>::ONE);
		if (it.operator->() != temp) {
			errorOut_("access through operator-> return wrong value (Priority<double>)",2);
		}
		if (*it != *temp) {
			errorOut_("access through operator* return wrong value (Priority<double>)",3);
		}
		delete temp;
	}
	passOut_("tested access through the iterator");
}

void PriorityTester::testItInc() {
	func_("testItInc");

	{
		Priority<string> ps;
		string *temp = new string(std::move(randString_(VERY_SMALL_ARRAY)));
		ps.push_back(temp,0,0);
		{
			auto it = ps.begin(Priority<string>::ONE);
			if (ps.begin(Priority<string>::ONE) != it++) {
				errorOut_("post increment wrong (Priority<string>)");
			}
			if (it != ps.end(Priority<string>::ONE)) {
				errorOut_("post increment wrong value (Priority<string>)",1);
			}
		}
		{
			auto it = ps.begin(Priority<string>::TWO);
			if (++it != it) {
				errorOut_("pre increment wrong (Priority<string>)",2);
			}
			if (it != ps.end(Priority<string>::TWO)) {
				errorOut_("pre increment wrong value (Priority<string>)",3);
			}
		}
		delete temp;
	}
	testDone_(3);
	{
		Priority<double> pd;
		double *temp = new double(randFloat_(VERY_LARGE_ARRAY,VERY_LARGE_ARRAY));
		pd.push_back(temp,0,0);
		{
			auto it = pd.begin(Priority<double>::ONE);
			if (pd.begin(Priority<double>::ONE) != it++) {
				errorOut_("post increment wrong (Priority<double>)",4);
			}
			if (it != pd.end(Priority<double>::ONE)) {
				errorOut_("post increment wrong value (Priority<double>)",5);
			}
		}
		{
			auto it = pd.begin(Priority<double>::TWO);
			if (++it != it) {
				errorOut_("pre increment wrong (Priority<double>)",6);
			}
			if (it != pd.end(Priority<double>::TWO)) {
				errorOut_("pre increment wrong value (Priority<double>)",7);
			}
		}
		delete temp;
	}
	passOut_("tested access through the iterator");
}

void PriorityTester::testStability() {
	func_("testStability");

	for (auto i=0 ; i<VERY_LARGE_ARRAY/SMALL_ARRAY ; ++i) {
		auto p = new Priority<string>();
		vector<string*> s;

		switch (rand() % 3) {
		case 0: // clear p and add info to it
		{
			delete p;
			p = new Priority<string>();
			s.clear();
			makePriority_(LARGE_ARRAY + rand() % LARGE_ARRAY,
					*p,s,KEYBOTH);
		}
		break;
		case 1: // replace all the information in the p
		{
			int size = s.size();
			for (auto i=0 ; i<size ; ++i) {
				if (rand()% 2) {
					p->pop_front(Priority<string>::ONE);
				}
				else {
					p->pop_front(Priority<string>::TWO);
				}
			}
			s.clear();
			makePriority_(LARGE_ARRAY + rand() % LARGE_ARRAY,
					*p,s,KEYBOTH);
		}
		case 2: // add more info to p
		default:
		{
			makePriority_(rand() % LARGE_ARRAY,
					*p,s,KEYBOTH);
		}
		break;
		}
	}
	passOut_("test the stability of Priority");
}

template <typename T>
void PriorityTester::makePriority_(unsigned int size,
								  Priority<T>& p,
								  vector<T*>& v,
								  int which) {
	int ind(rand()%2 ? -1*rand() : rand());
	for (unsigned int i=0 ; i<size ; ++i, ind+=rand()%SMALL_ARRAY+1) {
		T* temp=random_(T());
		v.push_back(temp);
		int ind1 (which >= 0 ? ind : 0);
		int ind2 (which <= 0 ? ind : 0);
		p.push_back(temp,ind1,ind2);
	}
}

template <typename T>
T* PriorityTester::random_(T a) {
	return new T;
}

template<>
string* PriorityTester::random_(string s) {
	return new string(std::move(randString_(VERY_SMALL_ARRAY)));
}

template<>
double* PriorityTester::random_(double d) {
	return new double(randFloat_(LARGE_ARRAY,LARGE_ARRAY));
}
