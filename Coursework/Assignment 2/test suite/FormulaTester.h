#include <string>
#include <iostream>

#ifndef FORMULATESTER_H_
#define FORMULATESTER_H_ 1


#include "Formula.h"
#include "Assignment.h"
#include "TesterBase.h"

enum FormulaType { CONSTANT=0, VARIABLE, AND, OR, NOT, INVALID };
enum FunctionType { VALID=0, EVALUATE, NAME, PRINT };

class FormulaTester : public TesterBase {
public:
	FormulaTester(int i=0);
	~FormulaTester();

	void testCopy();
	void testNegate();
	void testMemory();
	void testEvaluate();
	void testPrint();
	void testValid();
	void testName();

private:
	bool generateRandomFormula_(int depth, Formula*& formula,
			Assignment& ass, std::string* print, bool forceInvalid,
			bool forceRecursion=false);
};

#endif

