/*
 * main.cpp
 *
 *  Created on: 15 Oct 2014
 *      Author: np183
 */

#include <iostream>
#include <string>

#include "VectorTester.h"
#include "LinkedListTester.h"


using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[]) {

	if (false) {
		for (unsigned int i=0 ; i<1 ; ++i) {
			VectorTester t;
			t.testCtor();
		}
		return 0;

	}

	while (argc > 1) {

		switch (argv[--argc][0]) {
		case 'a':
		{
			VectorTester t;
			t.testCtor();
		}
		break;
		case 'b':
		{
			VectorTester t;
			t.testCopyCtor();
		}
		break;
		case 'c':
		{
			VectorTester t;
			t.testPushBack();
		}
		break;
		case 'd':
		{
			VectorTester t;
			t.testOperatorSqBr();
		}
		break;
		case 'e':
		{
			VectorTester t;
			t.testOperatorEq();
		}
		break;
		case 'f':
		{
			VectorTester t;
			t.testSize();
		}
		break;
		case 'g':
		{
			VectorTester t;
			t.testEmpty();
		}
		break;
		case 'h':
		{
			VectorTester t;
			t.testClear();
		}
		break;
		case 'i':
		{
			VectorTester t;
			t.testMemory();
		}
		break;
		case 'j':
		{
			LinkedListTester t;
			t.testCtor();
		}
		break;
		case 'k':
		{
			LinkedListTester t;
			t.testCopyCtor();
		}
		break;
		case 'l':
		{
			LinkedListTester t;
			t.testFunctionality();
		}
		break;
		case 'm':
		{
			LinkedListTester t;
			t.testOperatorEq();
		}
		break;
		case 'n':
		{
			LinkedListTester t;
			t.testSize();
		}
		break;
		case 'o':
		{
			LinkedListTester t;
			t.testEmpty();
		}
		break;
		case 'p':
		{
			LinkedListTester t;
			t.testClear();
		}
		break;
		case 'q':
		default:
		{
			LinkedListTester t;
			t.testMemory();
		}
		break;
        }
	}
	return 0;
}

