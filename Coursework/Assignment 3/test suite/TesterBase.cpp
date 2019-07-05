/*
 * TesterBase.cpp
 *
 *  Created on: 31 Oct 2015
 *      Author: np183
 *      Department of Informatics
 *      University of Leicester
 */

#include <stdlib.h>
#include <iostream>

#include "TesterBase.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

typedef unsigned int uint;

TesterBase::TesterBase(int i) : error_(0), tested_(0), funcname_("") {
	unsigned int val(i ? i : time(0)*rand());
	cout << val << endl;
	srand(val);
}

TesterBase::~TesterBase() {
}

void TesterBase::errorOut_(const string& errMsg, unsigned int errBit) {
	if (!errorSet_(1<<errBit)) {
		cerr << funcname_ << " " << "(fail";
		if (errBit)
			cerr << errBit;
		cerr << "): " << errMsg << endl;
		error_|=(1<<errBit);
	}
}

void TesterBase::testDone_(unsigned int errBit) {
	if (!testSet_(1<<errBit)) {
		cerr << funcname_ << " (completed test";
		if (errBit)
			cerr << errBit;
		cerr << ")" << endl;
		tested_ |= (1<<errBit);
	}
}

bool TesterBase::errorSet_(unsigned int mask) {
	return error_& mask;
}

bool TesterBase::testSet_(unsigned int mask) {
	return tested_ & mask;
}

void TesterBase::passOut_(const string& passMsg) {
	if (!error_) {
		cerr << funcname_ << " " << "(pass): " << passMsg << endl;
	}
}

void TesterBase::func_(const string& funcname,const string& success,const string& fail)
{
	funcname_=funcname;
}

float TesterBase::randFloat_(uint lowerbound, uint upperbound) {
	uint denom = rand() % 100 + 1;
	uint num = rand() % 100;
	float number = static_cast<float>(num)/static_cast<float>(denom);
	if (number>1) {
		number = 1 / number;
	}
	if (upperbound - lowerbound > 1) {
		number += rand() % (upperbound- lowerbound);
	}

	return number;
}

string TesterBase::randString_(uint length) {
	string val;
	for (unsigned int i = 0 ; i<length ; ++i) {
		val.push_back(randChar_());
	}
	return val;
}

string TesterBase::randStringSpace_(uint length) {
	string val;
	for (unsigned int i = 0 ; i<length ; ++i) {
		val.push_back(randCharSpace_());
	}
	return val;
}

char TesterBase::randChar_() {
	return 'a' + static_cast<char>(rand() % ('z'-'a'));
}


char TesterBase::randCharSpace_() {
	if (rand() % 10) { // non space
		return randChar_();
	}
	else if (rand() % 10) { // space or tab
		if (rand() % 10) {
			return ' ';
		}
		else {
			return '\t';
		}
	}
	else {
		return '\n';
	}
}

string TesterBase::removeSpaces_(string input) {
	std::string::size_type i;
	while ((i=input.find(' ')) != std::string::npos) {
		input = input.substr(0,i) + input.substr(i+1,std::string::npos);
	}
	return input;
}

string TesterBase::lc_(string input) {
	for (unsigned int i=0 ; i != input.size() ; ++i) {
		if (input[i] >= 'A' && input[i]<= 'Z') {
			input[i] = input[i] + 'a' - 'A';
		}
	}
	return input;
}



/*
 * TesterBase.cpp
 *
 *  Created on: 31 Oct 2015
 *      Author: np183
 *      Department of Informatics
 *      University of Leicester
 */
