// AUTOMATICALLY GENERATED DO NOT EDIT

#include "AutomatonTester.h"

int main(int argc, char* argv[]) {

	if (false) {
		for (unsigned int i=0 ; i<1 ; ++i) {
			AutomatonTester t;
		}
		return 0;
	}

	while(argc > 1) {

		switch (argv[--argc][0]) {
		case 'a':
		{
			AutomatonTester t;
			t.testAssOpMove();
		}
		break;
		case 'b':
		{
			AutomatonTester t;
			t.testStateChangeName();
		}
		break;
		case 'c':
		{
			AutomatonTester t;
			t.testMemory();
		}
		break;
		case 'd':
		{
			AutomatonTester t;
			t.testAssOpCopy();
		}
		break;
		case 'e':
		{
			AutomatonTester t;
			t.testMoveCtor();
		}
		break;
		case 'f':
		{
			AutomatonTester t;
			t.testIterateState();
		}
		break;
		case 'g':
		{
			AutomatonTester t;
			t.testCopyCtor();
		}
		break;
		case 'h':
		{
			AutomatonTester t;
			t.testBasic();
		}
		break;
		case 'i':
		default:
		{
			AutomatonTester t;
			t.testStability();
		}
		break;
		}
	}
	 return 0;
}
