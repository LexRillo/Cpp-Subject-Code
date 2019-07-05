/*
 * VectorTester.cpp
 *
 *  Created on: 15 Oct 2014
 *      Author: np183
 */

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <utility>

#include "VectorTester.h"
#include "Vector.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::stringstream;

constexpr int VECSIZE=100000;

VectorTester::VectorTester() : error_(false), funcname_() {
	unsigned int val(time(0)*rand());
	cout << val << endl;
	srand(val);
}

VectorTester::~VectorTester() {
}

void VectorTester::testCtor() {
	funcname_ = "testCtor";
	Vector vec;
	if (vec.size()!=0) {
		errorOut_("initial size is not 0",1);
	}
	for (int i=0 ; i<VECSIZE ; ++i) {
		vec.push_back(i);
		if (vec.size() != i+1) {
			errorOut_("wrong size",2);
			break;
		}
	}

	int size=rand()%VECSIZE;
	int val=rand();
	Vector vec1(size,val);
	if (vec1.size()!=size) {
		errorOut_("set to the wrong size",3);
	}
	else {
		for (int i=0 ; i < size ; ++i) {
			if (vec1[i]!=val) {
				errorOut_("values initialized incorrectly",4);
				break;
			}
		}
	}
	passOut_("did some tests to the constructors");
}

void VectorTester::testCopyCtor() {
	funcname_ = "testCopyCtor";
	// Create an initial vector
	Vector source;
	for (int i=0 ; i < VECSIZE ; ++i) {
		source.push_back(rand());
	}
	Vector copy(source);

	for (int i=0 ; i<VECSIZE ; ++i) {
		if (source[i] != copy[i]) {
			errorOut_("different values in copy",1);
			break;
		}
	}

	Vector move(std::move(source));
	if (source.size() != 0) {
		errorOut_("Move constructor does not erase",1);
	}
	if (move.size() != copy.size()) {
		errorOut_("Sizes don't match between copy and move",2);
	}
	for (int i=0 ; i<VECSIZE ; ++i) {
		if (copy[i] != move[i]) {
			errorOut_("Copy and move don't match",3);
			break;
		}
	}
	passOut_("tested the copy and move constructors");
}

void VectorTester::testPushBack() {
	funcname_ = "testPushBack";
	Vector vec;
	int backup[VECSIZE];
	for (int i=0 ; i<VECSIZE ; ++i) {
		int temp = rand();
		vec.push_back(temp);
		backup[i]=temp;
	}
	for (int i=0 ; i<VECSIZE ; ++i) {
		if (vec[i] != backup[i]) {
			errorOut_("insert and retrieve the same values",1);
			break;
		}
	}

	passOut_("added 100 elements and checked that they are retrieved");
}

void VectorTester::testOperatorSqBr() {
	funcname_ = "testOperatorSqBr";

	Vector vec(VECSIZE,0);
	int rec[VECSIZE];
	for (int i=0 ; i<VECSIZE ; ++i) {
		rec[i]=0;
	}

	for (int i=0 ; i<VECSIZE ; ++i) {
		int loc = rand() % 200;
		int val = rand();
		vec[loc] = val;
		rec[loc] = val;
	}

	for (int i=0 ; i<VECSIZE ; ++i) {
		if (vec[i] != rec[i]) {
			errorOut_("wrong value retrieved",1);
			break;
		}
	}
	passOut_("set elements and retrieved them");
}


void VectorTester::testOperatorEq() {
	funcname_ = "testOperatorEq";
	// Create an initial vector
	Vector source;
	for (int i=0 ; i < VECSIZE ; ++i) {
		source.push_back(rand());
	}
	Vector copy(50,15);
	copy = source;

	for (int i=0 ; i<VECSIZE ; ++i) {
		if (source[i] != copy[i]) {
			errorOut_("different values in copy",1);
			break;
		}
	}

	Vector move(50,15);
	move = std::move(source);
	if (source.size() != 50 && source.size() != 0) {
		errorOut_("Move constructor does not swap or erase",1);
	}
	if (move.size() != copy.size()) {
		errorOut_("Sizes don't match between copy and move",2);
	}
	for (int i=0 ; i<VECSIZE ; ++i) {
		if (copy[i] != move[i]) {
			errorOut_("Copy and move don't match",3);
			break;
		}
	}
	passOut_("tested the copy and move constructors");

}

void VectorTester::testSize() {
	funcname_ = "testSize";
	Vector vec;
	for (int i=0 ; i<=100 ; ++i) {

		if (vec.size() != i) {
			errorOut_("returned wrong size",1);
			break;
		}
		vec.push_back(i);
	}
	passOut_("the size matches what I expected");
}

void VectorTester::testEmpty() {
	funcname_ = "testEmpty";
	Vector vec;
	if (!vec.empty()) {
		errorOut_("initially not empty",1);
	}
	for (int i=0 ; i<=100 ; ++i) {
		vec.push_back(i);
	}
	if (vec.empty()) {
		errorOut_("empty after adding things",2);
	}
	vec.clear();
	if (!vec.empty()) {
		errorOut_("after clear not empty",1);
	}
	passOut_("empty when expected it to be");
}

void VectorTester::testClear() {
	funcname_ = "testClear";

	Vector vec;
	for (int i=0 ; i<VECSIZE ; ++i) {
		vec.push_back(i);
	}
	if (vec.size() != VECSIZE) {
		errorOut_("could not build up a full vector",0);
		return;
	}
	vec.clear();
	if (vec.size() != 0) {
		errorOut_("did not clear",1);
	}
	passOut_("cleared the vector");
}


void VectorTester::testMemory() {
	funcname_ = "testMemory";
	for (int j=0 ; j<=VECSIZE/100; ++j) {
		Vector vec;
		for (int i=0 ; i<=VECSIZE/10 ; ++i) {
			vec.push_back(i);
		}
		vec[VECSIZE/10-1]=0;
	}

	passOut_("stressed the memory usage");
}

void VectorTester::testToString() {
	funcname_ = "testToString";
	int backup[VECSIZE/100];
	Vector vec;
	for (int j = 0 ; j<=VECSIZE/100 ; ++j) {
		backup[j] = rand();
		vec.push_back(backup[j]);
	}

	string result = vec.toString();

	CompareWithStringSimple_(result,backup,VECSIZE/100);
	int length = rand() % 100;
	result  = vec.toString(length,'_');
	CompareWithString_(result,backup,VECSIZE/100,length,'_');

	passOut_("string was ok");
}

void VectorTester::testOSRedir() {
	funcname_ = "testOSRedir";
	int backup[VECSIZE/100];
	Vector vec;
	for (int j = 0 ; j<VECSIZE/100 ; ++j) {
		backup[j] = rand();
		vec.push_back(backup[j]);
	}

	stringstream s;
	s << vec;
	CompareWithStringSimple_(s.str(),backup,VECSIZE/100);

	int length = rand() % 100;
	stringstream s1;
	s1.fill('(');
	s1.width(length);
	s1 << vec;
	CompareWithString_(s1.str(),backup,VECSIZE/100,length,'(');

	passOut_("output was OK");
}

void VectorTester::testISRedir() {
  funcname_ = "testISRedir";

  stringstream s1,s2;
  int backup[VECSIZE/100];
  bool notfirst = false;
  for (int j=0 ; j<VECSIZE/100 ; ++j) {
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

  Vector v1,v2;
  s1 >> v1;
  s2 >> v2;

  if (v2.size() > 0) {
    errorOut_("read from a corrupt stream",0);
  }
  if (s2) {
    errorOut_("stream with error should be unusable",1);
  }

  if (v1.size() != VECSIZE/100) {
    errorOut_("failed to read well structured stream",2);
  }
  else {
    for (int j=0 ; j<VECSIZE/100 ; ++j) {
      if (backup[j] != v1[j]) {
	errorOut_("wrong values in read vector",3);
	break;
      }
    }

    if (!s1 || s1.peek()!=std::char_traits<char>::eof() || !s1.eof()) {
      errorOut_("stream without error should be usable and at eof",4);
    }
  }
  passOut_("managed to input well");
}



void VectorTester::errorOut_(const string& errMsg, unsigned int errBit) {
        cerr << funcname_ << " " << "(fail";
        if (errBit)
                cerr << errBit;
        cerr << "): " << errMsg << endl;
        error_|=(1<<errBit);
}

bool VectorTester::errorSet_(unsigned int mask) {
        return error_& mask;
}

void VectorTester::passOut_(const string& passMsg) {
        if (!error_) {
                cerr << funcname_ << " " << "(pass): " << passMsg << endl;
        }
}

void VectorTester::CompareWithStringSimple_(const string& result,int* arr, int size) {
	string::size_type begin=0;
	int j=0;
	for ( ; begin < result.length() && j<size ; ++j) {
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
	if (j != size) {
	  errorOut_("was expecting more elements",2);
	}
}


void VectorTester::CompareWithString_(const string& result, int* backup, int size, int length, char fill) 
{
  string::size_type begin = 0;
	int j=0;
	while (begin < result.length()) {
		string::size_type end=result.find('\n',begin);
		if (end == string::npos) {
			end = result.length();
		}
		string currentline = result.substr(begin,end-begin);
		begin=end+1;
		if (currentline.length() > length && currentline.find(fill)!=string::npos && currentline.find(' ')!=string::npos) {
			errorOut_("too long lines",3);
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

			if (currentelem != std::to_string(backup[j])) {
				errorOut_("something went wrong",4);
				return;
			}
			++j;
		}
	}
}
