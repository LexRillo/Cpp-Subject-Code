/*
 * LinkedListTester.cpp
 *
 *  Created on: 15 Oct 2014
 *      Author: np183
 */

#include <stdlib.h>
#include <iostream>
#include <utility>

#include "LinkedListTester.h"
#include "LinkedList.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

constexpr int LINKEDLISTSIZE=100000;

LinkedListTester::LinkedListTester() : error_(false), funcname_() {
	unsigned int val(time(0)*rand());
	cout << val << endl;
	srand(val);
}

LinkedListTester::~LinkedListTester() {
}

void LinkedListTester::testCtor() {
	funcname_ = "testCtor";
	LinkedList ll;
	if (ll.size()!=0) {
		errorOut_("initial size is not 0",1);
	}
	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		ll.push_back(i);
		if (ll.size() != i+1) {
			errorOut_("wrong size",2);
			break;
		}
	}
	passOut_("did some tests to the constructors");
}

void LinkedListTester::testCopyCtor() {
	funcname_ = "testCopyCtor";
	// Create an initial vector
	LinkedList source;
	for (int i=0 ; i < LINKEDLISTSIZE ; ++i) {
		source.push_back(rand());
//		cout << source.last() << " ";
	}
//	cout << endl;

	LinkedList copy(source);

	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
//		cout << source.first() << " " << copy.first() << " ";
		if (source.first() != copy.first()) {
			errorOut_("different values in copy",1);
			break;
		}
		source.pop_front();
		copy.pop_front();
	}
	for (int i=0 ; i < LINKEDLISTSIZE ; ++i) {
		source.push_back(rand());
	}

	LinkedList copy1(source);
	LinkedList move(std::move(source));
	if (source.size() != 0) {
		errorOut_("Move constructor does not erase",2);
	}
	if (move.size() != copy1.size()) {
		errorOut_("Sizes don't match between copy and move",3);
	}
	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		if (copy1.first() != move.first()) {
			errorOut_("Copy and move don't match",4);
			break;
		}
		copy1.pop_front();
		move.pop_front();
	}
	passOut_("tested the copy and move constructors");
}

void LinkedListTester::testFunctionality() {
	funcname_ = "testFunctionality";
	LinkedList ll;
	int backup[LINKEDLISTSIZE];
	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		int temp = rand();
		ll.push_back(temp);
		backup[i]=temp;
	}
	int head=0;
	int tail=LINKEDLISTSIZE-1;
	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		if (true || rand()%2) {
			if (backup[head]!=ll.first()) {
				errorOut_("insert and retrieve different values",1);
				break;
			}
			ll.pop_front();
			++head;
		}
		else {
			if (backup[tail]!= ll.last()) {
				errorOut_("insert and retrieve different values",2);
				break;
			}
			ll.pop_back();
			--tail;
		}
	}

	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		ll.push_back(backup[i]);
	}
	LinkedList lRev;
	while (!ll.empty()) {
		lRev.push_back(ll.last());
		ll.pop_back();
	}
	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		if (lRev.first() != backup[LINKEDLISTSIZE-1-i]) {
			errorOut_("insert and retrieve different values",3);
			break;
		}
		lRev.pop_front();
	}
	passOut_("added and removed elements and checked that they are correct");
}

void LinkedListTester::testOperatorEq() {
	funcname_ = "testOperatorEq";
	// Create an initial vector
	LinkedList source;
	for (int i=0 ; i < LINKEDLISTSIZE ; ++i) {
		source.push_back(rand());
	}
	LinkedList copy;
	copy = source;

	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		if (source.first() != copy.first()) {
			errorOut_("different values in copy",1);
			break;
		}
		source.pop_front();
		copy.pop_front();
	}

	for (int i=0 ; i < LINKEDLISTSIZE ; ++i) {
		source.push_back(rand());
	}

	LinkedList copy1;
	copy1 = source;
	LinkedList move;
	move = std::move(source);
	if (source.size() != 0) {
		errorOut_("Move constructor does not erase",2);
	}
	if (move.size() != copy1.size()) {
		errorOut_("Sizes don't match between copy and move",3);
	}
	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		if (copy1.first() != move.first()) {
			errorOut_("Copy and move don't match",4);
			break;
		}
		copy1.pop_front();
		move.pop_front();
	}
	passOut_("tested copy and move operator=");
}

void LinkedListTester::testSize() {
	funcname_ = "testSize";
	LinkedList ll;
	for (int i=0 ; i<=100 ; ++i) {
		if (ll.size() != i) {
			errorOut_("returned wrong size",1);
			break;
		}
		ll.push_back(i);
	}
	passOut_("the size matches what I expected");
}

void LinkedListTester::testEmpty() {
	funcname_ = "testEmpty";
	LinkedList ll;
	if (!ll.empty()) {
		errorOut_("initially not empty",1);
	}
	for (int i=0 ; i<=100 ; ++i) {
		ll.push_back(i);
	}
	if (ll.empty()) {
		errorOut_("empty after adding things",2);
	}
	ll.clear();
	if (!ll.empty()) {
		errorOut_("after clear not empty",1);
	}
	passOut_("empty when expected it to be");
}

void LinkedListTester::testClear() {
	funcname_ = "testClear";

	LinkedList ll;
	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		ll.push_back(i);
	}
	if (ll.size() != LINKEDLISTSIZE) {
		errorOut_("could not build up a full vector",0);
		return;
	}
	ll.clear();
	if (ll.size() != 0) {
		errorOut_("did not clear",1);
	}
	passOut_("cleared the vector");
}


void LinkedListTester::testMemory() {
	funcname_ = "testMemory";
	for (int j=0 ; j<=LINKEDLISTSIZE/100; ++j) {
		LinkedList ll;
		for (int i=0 ; i<=LINKEDLISTSIZE/10 ; ++i) {
			if (rand()%2) {
				ll.push_back(i);
			}
			else {
				ll.push_front(i);
			}
		}
	}
	passOut_("stressed the memory usage");
}

void LinkedListTester::errorOut_(const string& errMsg, unsigned int errBit) {
        cerr << funcname_ << " " << "(fail";
        if (errBit)
                cerr << errBit;
        cerr << "): " << errMsg << endl;
        error_|=(1<<errBit);
}

bool LinkedListTester::errorSet_(unsigned int mask) {
        return error_& mask;
}

void LinkedListTester::passOut_(const string& passMsg) {
        if (!error_) {
                cerr << funcname_ << " " << "(pass): " << passMsg << endl;
        }
}
