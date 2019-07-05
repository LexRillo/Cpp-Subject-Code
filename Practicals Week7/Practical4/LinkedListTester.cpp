/*
 * LinkedListTester.cpp
 *
 *  Created on: 15 Oct 2014
 *      Author: np183
 */

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <utility>

#include "LinkedListTester.h"
#include "LinkedList.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::stringstream;

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

void LinkedListTester::testToString() {
	funcname_ = "testToString";
	int backup[LINKEDLISTSIZE/100];
	LinkedList ll;
	for (int j = 0 ; j<=LINKEDLISTSIZE/100 ; ++j) {
		backup[j] = rand();
		ll.push_back(backup[j]);
	}

	string result = ll.toString();
	CompareWithStringSimple_(result,backup,LINKEDLISTSIZE/100);

	int length = rand() % 100;
	result  = ll.toString(length,'_');

	passOut_("string was ok");
}

void LinkedListTester::testOSRedir() {
	funcname_ = "testOSRedir";

	int backup[LINKEDLISTSIZE/100];
	LinkedList ll;
	for (int j=0 ; j<= LINKEDLISTSIZE/100 ; ++j) {
	  backup[j] = rand();
	  ll.push_back(backup[j]);
	}

	stringstream s;
	s << ll;
	CompareWithStringSimple_(s.str(),backup,LINKEDLISTSIZE/100);

	int length = rand() % 100;
	stringstream s1;
	s1.fill('*');
	s1.width(length);
	s1 << ll;
	CompareWithString_(s1.str(),backup,LINKEDLISTSIZE/100,length,'*');

	passOut_("output was OK");
}

void LinkedListTester::testISRedir() {
  funcname_ = "testISRedir";
  stringstream s1,s2;
  int backup[LINKEDLISTSIZE/100];
  bool notfirst = false;
  for (int j=0 ; j<LINKEDLISTSIZE/100 ; ++j) {
    backup[j] = rand();
    if (notfirst) {
      s1 << " ";
      s2 << " ";
    }
    s1 << backup[j];
    s2 << backup[j];
    notfirst = true;
  }
  s2 << "blah";
  s1.seekg(0);
  s2.seekg(0);

  LinkedList l1,l2;
  s1 >> l1;
  s2 >> l2;

  if (l2.size() > 0) {
    errorOut_("read from a corrupt stream",0);
  }
  if (s2) {
    errorOut_("stream with error should be unusable",1);
  }

  if (l1.size() != LINKEDLISTSIZE/100) {
    errorOut_("failed to read well structured stream",2);
  }
  else {
    for (int j=0 ; j<LINKEDLISTSIZE/100 ; ++j) {
      if (backup[j] != l1.first()) {
	errorOut_("wrong values in read vector",3);
	break;
      }
      l1.pop_front();
    }

    if (!s1 || s1.peek()!=std::char_traits<char>::eof() || !s1.eof()) {
      errorOut_("stream without error should be usable and at eof",4);
    }
  }
	passOut_("managed to input well");
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

void LinkedListTester::CompareWithStringSimple_(const string& result,
						int* arr,
						int size) 
{
	string::size_type begin=0;
	for (int j=0 ; j<=size ; ++j) {
		string::size_type end = result.find(' ',begin);
		if (end == string::npos) {
			end = result.length();
		}
		string currentelem = result.substr(begin,end-begin);
		begin = end+1;

		if (currentelem != std::to_string(arr[j])) {
			errorOut_("print to one line did not work well",1);
			return;
		}
	}
}

void LinkedListTester::CompareWithString_(const string& result, int* arr,
					  int size, int length, char fill) 
{
	int j=0;
	string::size_type begin = 0;
	while (begin < result.length()) {
		string::size_type end=result.find('\n',begin);
		if (end == string::npos) {
			end = result.length();
		}
		string currentline = result.substr(begin,end-begin);
		begin=end+1;
		if (currentline.length() > length && currentline.find(fill)==string::npos && currentline.find(' ')==string::npos) {
			errorOut_("too long lines",2);
			return;
		}
		string::size_type endl=0;
		for (string::size_type beginl=0;
			 beginl < currentline.length();
			 beginl = endl+1) {
			endl=currentline.find(fill,beginl);
			if (endl==string::npos) {
				endl = currentline.length();
			}
			string currentelem = currentline.substr(beginl,endl-beginl);

			if (currentelem != std::to_string(arr[j])) {
				errorOut_("something went wrong",3);
				return;
			}
			++j;
		}
	}
}
