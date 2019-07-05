/*
 * main.cpp
 */

#include <iostream>
#include <string>

#include "ShapeTester.h"


using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[]) {

	if (false) {
		for (unsigned int i=0 ; i<1 ; ++i) {
			ShapeTester t;
		}
		return 0;

	}

	while (argc > 1) {

		switch (argv[--argc][0]) {
		case 'a':
		{
			ShapeTester t;
			t.testCtor();
		}
		break;
		case 'b':
		{
			ShapeTester t;
			t.testSimpleFunctions();
		}
		break;
		case 'c':
		{
			ShapeTester t;
			t.testArea();
		}
		break;
		case 'd':
		{
			ShapeTester t;
			t.testPerimeter();
		}
		break;
		case 'e':
		{
			ShapeTester t;
			t.testToString();
		}
		break;
		case 'f':
		default:
		{
			ShapeTester t;
			t.testOstreamRedir();
		}
		break;
		}
	}
	return 0;
}

