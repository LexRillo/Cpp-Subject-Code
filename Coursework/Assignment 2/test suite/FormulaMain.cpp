// AUTOMATICALLY GENERATED DO NOT EDIT

#include "FormulaTester.h"

int main(int argc, char* argv[]) {

	if (false) {
		for (unsigned int i=0 ; i<1 ; ++i) {
			FormulaTester t;
		}
		return 0;
	}

	while(argc > 1) {

		switch (argv[--argc][0]) {
		case 'a':
		{
			FormulaTester t;
			t.testNegate();
		}
		break;
		case 'b':
		{
			FormulaTester t;
			t.testValid();
		}
		break;
		case 'c':
		{
			FormulaTester t;
			t.testName();
		}
		break;
		case 'd':
		{
			FormulaTester t;
			t.testEvaluate();
		}
		break;
		case 'e':
		{
			FormulaTester t;
			t.testPrint();
		}
		break;
		case 'f':
		{
			FormulaTester t;
			t.testCopy();
		}
		break;
		case 'g':
		default:
		{
			FormulaTester t;
			t.testMemory();
		}
		break;
		}
	}
	 return 0;
}
