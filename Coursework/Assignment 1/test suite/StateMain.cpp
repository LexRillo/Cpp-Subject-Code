// AUTOMATICALLY GENERATED DO NOT EDIT

#include "StateTester.h"

int main(int argc, char* argv[]) {

	if (false) {
		for (unsigned int i=0 ; i<1 ; ++i) {
			StateTester t;
			t.testStability();
		}
		return 0;
	}

	while(argc > 1) {

		switch (argv[--argc][0]) {
		case 'a':
		{
			StateTester t;
			t.testAssignmentOpMove();
		}
		break;
		case 'b':
		{
			StateTester t;
			t.testOpEq();
		}
		break;
		case 'c':
		{
			StateTester t;
			t.testTransition();
		}
		break;
		case 'd':
		{
			StateTester t;
			t.testName();
		}
		break;
		case 'e':
		{
			StateTester t;
			t.testCtor();
		}
		break;
		case 'f':
		{
			StateTester t;
			t.testLabel();
		}
		break;
		case 'g':
		{
			StateTester t;
			t.testAssignmentOpCopy();
		}
		break;
		case 'h':
		{
			StateTester t;
			t.testMoveCtor();
		}
		break;
		case 'i':
		{
			StateTester t;
			t.testCopyCtor();
		}
		break;
		case 'j':
		{
			StateTester t;
			t.testMoveMemory();
		}
		break;
		case 'k':
		default:
		{
			StateTester t;
			t.testStability();
		}
		break;
		}
	}
	 return 0;
}
