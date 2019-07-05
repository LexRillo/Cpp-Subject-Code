/*
 * VectorTester.cpp
 *
 *  Created on: 15 Oct 2014
 *      Author: np183
 */

#include <stdlib.h>
#include <iostream>
#include <utility>

#include "VectorTester.h"
#include "Vector.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

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
	for (int i=0 ; i<100 ; ++i) {
		if (!vec.addElem(i)) {
			errorOut_("could not add 100 elements to initialized vector",2);
			break;
		}
		if (vec.size() != i+1) {
			errorOut_("wrong size",3);
			break;
		}
	}

	int size=rand()%100;
	int val=rand();
	Vector vec1(size,val);
	if (vec1.size()!=size) {
		errorOut_("set to the wrong size",4);
	}
	else {
		for (int i=0 ; i < size ; ++i) {
			if (vec1.getElem(i)!=val) {
				errorOut_("values initialized incorrectly",5);
				break;
			}
		}
	}
	for (int i=size ; i<Vector::SIZE ; ++i) {
		if (vec1.setElem(i,0)) {
			errorOut_("size set incorrectly",6);
			break;
		}
	}
	passOut_("did some tests to the constructors");
}

void VectorTester::testAddGetElem() {
	funcname_ = "testAddElem";
	Vector vec;
	int backup[Vector::SIZE];
	for (int i=0 ; i<Vector::SIZE ; ++i) {
		int temp = rand();
		vec.addElem(temp);
		backup[i]=temp;
	}
	for (int i=0 ; i<Vector::SIZE ; ++i) {
		if (vec.getElem(i) != backup[i]) {
			errorOut_("insert and retrieve the same values",1);
			break;
		}
	}
	bool error=false;
	for (int i=0 ; i < Vector::SIZE ; ++i) {
		if (vec.addElem(0) && !error) {
			errorOut_("inserted more than 100 values",2);
			error = true;
		}
	}

	passOut_("added 100 elements and checked that they are retrieved");
}

void VectorTester::testSetElem() {
	funcname_ = "testSetElem";

	Vector vec;
	for (int i=0 ; i < 10000 ; ++i) {
		int loc = rand() % 100;
		if (vec.setElem(loc,0)) {
			errorOut_("set an element before increasing vector size",1);
			break;
		}
	}
	for (int i=0 ; i<Vector::SIZE ; ++i) {
		vec.addElem(i);
	}
	for (int i=0 ; i<10000 ; ++i) {
		int loc = rand() % 200;
		int val = rand();
		if (!errorSet_(1<<2) && loc<100 && (!vec.setElem(loc,val) || vec.getElem(loc)!=val)) {
			errorOut_("failed to set or to retrieve",2);
		}
		if (!errorSet_(1<<3) && loc>=100 && vec.setElem(loc,val)) {
			errorOut_("set out of bound",3);
		}
	}
	passOut_("set elements and retrieved them");
}


void VectorTester::testSize() {
	funcname_ = "testSize";
	Vector vec;
	bool error=false;
	for (int i=0 ; i<=100 ; ++i) {

		if (vec.size() != i && !error) {
			errorOut_("returned wrong size",1);
			error = true;
		}
		vec.addElem(i);
	}
	for (int i=0 ; i<Vector::SIZE ; ++i) {
		vec.addElem(0);
		if (vec.size()!= Vector::SIZE) {
			errorOut_("returned wrong size",2);
			break;
		}
	}
	passOut_("the size matches what I expected");
}

void VectorTester::testClear() {
	funcname_ = "testClear";

	Vector vec;
	for (int i=0 ; i<=100 ; ++i) {
		vec.addElem(i);
	}
	if (vec.size() != Vector::SIZE) {
		errorOut_("could not build up a full vector",0);
		return;
	}
	vec.clear();
	if (vec.size() != 0) {
		errorOut_("did not clear",1);
	}
	passOut_("cleared the vector");
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
