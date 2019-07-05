// AUTOMATICALLY GENERATED DO NOT EDIT

#include "PathTester.h"

int main(int argc, char* argv[]) {

	if (false) {
		for (unsigned int i=0 ; i<1 ; ++i) {
			PathTester t;
		}
		return 0;
	}

	while(argc > 1) {

		switch (argv[--argc][0]) {
		case 'a':
		{
			PathTester t;
			t.testDim();
		}
		break;
		case 'b':
		{
			PathTester t;
			t.testLength();
		}
		break;
		case 'c':
		{
			PathTester t;
			t.testConstruction();
		}
		break;
		case 'd':
		{
			PathTester t;
			t.testComparison();
		}
		break;
		case 'e':
		{
			PathTester t;
			t.testOperatorPlus();
		}
		break;
		case 'f':
		{
			PathTester t;
			t.testOperatorRedir();
		}
		break;
		case 'g':
		{
			PathTester t;
			t.testVisited();
		}
		break;
		case 'h':
		{
			PathTester t;
			t.testOperatorMinus();
		}
		break;
		case 'i':
		default:
		{
			PathTester t;
			t.testSpace();
		}
		break;
		}
	}
	 return 0;
}
