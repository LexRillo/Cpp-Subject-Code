// AUTOMATICALLY GENERATED DO NOT EDIT

#include "PriorityTester.h"

int main(int argc, char* argv[]) {

	if (false) {
		for (unsigned int i=0 ; i<1 ; ++i) {
			PriorityTester t;
		}
		return 0;
	}

	while(argc > 1) {

		switch (argv[--argc][0]) {
		case 'a':
		{
			PriorityTester t;
			t.testItInc();
		}
		break;
		case 'b':
		{
			PriorityTester t;
			t.testItAccess();
		}
		break;
		case 'c':
		{
			PriorityTester t;
			t.testPopMix();
		}
		break;
		case 'd':
		{
			PriorityTester t;
			t.testCtor();
		}
		break;
		case 'e':
		{
			PriorityTester t;
			t.testIterator();
		}
		break;
		case 'f':
		{
			PriorityTester t;
			t.testPopSep();
		}
		break;
		case 'g':
		{
			PriorityTester t;
			t.testSame();
		}
		break;
		case 'h':
		default:
		{
			PriorityTester t;
			t.testStability();
		}
		break;
		}
	}
	 return 0;
}
