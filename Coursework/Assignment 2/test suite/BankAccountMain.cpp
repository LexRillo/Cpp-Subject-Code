// AUTOMATICALLY GENERATED DO NOT EDIT

#include "BankAccountTester.h"

int main(int argc, char* argv[]) {

	if (false) {
		for (unsigned int i=0 ; i<1 ; ++i) {
			BankAccountTester t;
		}
		return 0;
	}

	while(argc > 1) {

		switch (argv[--argc][0]) {
		case 'a':
		{
			BankAccountTester t;
			t.testStockConstructor();
		}
		break;
		case 'b':
		{
			BankAccountTester t;
			t.testBalance();
		}
		break;
		case 'c':
		{
			BankAccountTester t;
			t.testCurrentConstructor();
		}
		break;
		case 'd':
		{
			BankAccountTester t;
			t.testToString();
		}
		break;
		case 'e':
		{
			BankAccountTester t;
			t.testDay();
		}
		break;
		case 'f':
		{
			BankAccountTester t;
			t.testOperatorRedir();
		}
		break;
		case 'g':
		{
			BankAccountTester t;
			t.testBuySell();
		}
		break;
		case 'h':
		{
			BankAccountTester t;
			t.testMonth();
		}
		break;
		case 'i':
		{
			BankAccountTester t;
			t.testType();
		}
		break;
		case 'j':
		default:
		{
			BankAccountTester t;
			t.testSavingsConstructor();
		}
		break;
		}
	}
	 return 0;
}
