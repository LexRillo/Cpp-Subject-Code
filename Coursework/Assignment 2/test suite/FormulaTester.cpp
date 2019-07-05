#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "FormulaTester.h"
#include "Assignment.h"


using std::string;
using std::ostringstream;
using std::cout;
using std::endl;

const char NEWLINE='\n';
const string TRUESTRING="T";
const string FALSESTRING="F";
const string ANDSTRING="and";
const string ORSTRING="or";
const string NOTSTRING="not";
const int THOUSAND=1000;
const int FIFTY=50;

FormulaTester::FormulaTester(int i) : TesterBase(i) {}
FormulaTester::~FormulaTester() {}

void FormulaTester::testCopy() {
	func_("testCopy");
	// copy valid formulas
	for (int i=0 ; i<FIFTY ; i++) {
		Formula* f=0;
		Assignment ass;
		generateRandomFormula_(20,f,ass,nullptr,false,true);
		Formula* fCopy = f->copy();
		ostringstream s1,s2;

		f->print(s1);
		f->print(s2);
		if (s1.str() != s2.str() ||
			f->valid() != fCopy->valid() ||
			f->name() != fCopy->name() ||
			f->evaluate(ass) != fCopy->evaluate(ass)) {
			errorOut_("copy produced different formulas for valid formulas");
		}
		delete f;
		delete fCopy;
	}
	testDone_();

	// copy invalid formulas -> don't use evaluate
	for (int i=0 ; i<FIFTY ; i++) {
		Formula* f=0;
		Assignment ass;
		generateRandomFormula_(20,f,ass,nullptr,true,true);
		Formula* fCopy = f->copy();
		ostringstream s1,s2;

		f->print(s1);
		f->print(s2);
		if (s1.str() != s2.str() ||
			f->valid() != fCopy->valid() ||
			f->name() != fCopy->name()) {
			errorOut_("copy produced different formulas for invalid formulas",1);
		}
		delete f;
		delete fCopy;
	}

	passOut_("Copied formulas and tested for equivalence");
}

void FormulaTester::testNegate() {
	func_("testNegate");
	for (int i=0 ; i<FIFTY ; i++) {
		Formula* f=0;
		Assignment ass;
		generateRandomFormula_(20,f,ass,nullptr,false,true);
		Formula* fNeg = f->negate();

		if (f->evaluate(ass) == fNeg->evaluate(ass)) {
			errorOut_("negated formula has same evaluation");
		}
		delete f;
		delete fNeg;
	}
	passOut_("negated formulas and tested that they evaluate to negated values");
}

void FormulaTester::testMemory() {
	func_("testMemory");
	for (int i=0 ; i < THOUSAND ; i++) {
		Formula* f=0;
		Assignment ass;
		generateRandomFormula_(50,f,ass,nullptr,false,true);
		delete f;
	}
	passOut_("Created large random formulas and destroyed them");
}

void FormulaTester::testEvaluate() {
	func_("testEvaluate");
	for (int i=0 ; i < FIFTY ; i++) {
		Formula *f=0;
		Assignment ass;
		bool res = generateRandomFormula_(20,f,ass,nullptr,false,true);
		if (f->evaluate(ass) != res) {
			errorOut_("Evaluation produced the wrong result");
		}
		delete f;
	}
	passOut_("Evaluated a Random formula");
}

void FormulaTester::testValid() {
	func_("testValid");
	{
		Formula *t = new Constant(true);
		Formula *f = new Constant(false);
		if (!t->valid() || !f->valid()) {
			errorOut_("Constant not valid");
		}
		delete t;
		delete f;
	}
	testDone_();
	{
		Formula*left = new Constant(true);
		Formula *right = new Constant(false);
		Formula *f=new And(left,right);
		if (!f->valid()) {
			errorOut_("And not valid",1);
		}
		delete f;
	}
	testDone_(1);
	{
		Formula* left = new Constant(true);
		Formula* right = new Constant(false);
		Formula* f=new Or(left,right);
		if (!f->valid()) {
			errorOut_("Or not valid",2);
		}
		delete f;
	}
	testDone_(2);
	{
		Formula* left = new Constant(true);
		Formula* f=new Not(left);
		if (!f->valid()) {
			errorOut_("Not not valid",3);
		}
		delete f;
	}
	testDone_(3);
	{
		Formula* var = new Variable(randString_(10));
		if (!var->valid()) {
			errorOut_("Variable not valid",4);
			delete var;
		}
	}
	testDone_(4);
	{
		Formula* left = new Constant(true);
		Formula* f=new And(left,nullptr);
		if (f->valid()) {
			errorOut_("And is valid",5);
		}
		delete f;
	}
	testDone_(5);
	{
		Formula* left = new Constant(true);
		Formula* f=new Or(left,nullptr);
		if (f->valid()) {
			errorOut_("Or is valid",6);
		}
		delete f;
	}
	testDone_(6);
	{
		Formula* f=new Not(nullptr);
		if (f->valid()) {
			errorOut_("Not is valid",7);
		}
		delete f;
	}
	testDone_(7);
	{
		Formula* var=new Variable("");
		if (var->valid()) {
			errorOut_("Variable is valid",8);
		}
		delete var;
	}
	testDone_(8);

	Formula *left=nullptr;
	Formula *right=nullptr;
	Formula *f=nullptr;

	Assignment ass;
	generateRandomFormula_(5,left,ass,nullptr,false,false);
	generateRandomFormula_(5,right,ass,nullptr,false,false);
	f=new And(left,right);
	if (!f->valid()) {
		errorOut_("Recursive And is invalid",9);
	}
	delete f;
	testDone_(9);

	generateRandomFormula_(5,left,ass,nullptr,false,false);
	generateRandomFormula_(5,right,ass,nullptr,false,false);
	f=new Or(left,right);
	if (!f->valid()) {
		errorOut_("Recursive Or is invalid",10);
	}
	delete f;
	testDone_(10);

	generateRandomFormula_(5,left,ass,nullptr,false,false);
	f=new Not(left);
	if (!f->valid()) {
		errorOut_("Recursive Not is invalid",11);
	}
	delete f;
	testDone_(11);

	generateRandomFormula_(5,left,ass,nullptr,false,false);
	generateRandomFormula_(5,right,ass,nullptr,true,false);
	f=new And(left,right);
	if (f->valid()) {
		errorOut_("Recursive And is valid",12);
	}
	delete f;
	testDone_(12);

	generateRandomFormula_(5,left,ass,nullptr,false,false);
	generateRandomFormula_(5,right,ass,nullptr,true,false);
	f=new Or(left,right);
	if (f->valid()) {
		errorOut_("Recursive Or is valid",13);
	}
	delete f;
	testDone_(13);

	generateRandomFormula_(5,left,ass,nullptr,true,false);
	f=new Not(left);
	if (f->valid()) {
		errorOut_("Recursive Not is valid",14);
	}
	delete f;
	testDone_(14);

	passOut_("tested validity locally and recursively");
}

void FormulaTester::testName() {
	func_("testName");
	Formula *left=0;
	Formula *right=0;
	Formula *f=0;

	left = new Constant(true);
	right = new Constant(false);
	if (removeSpaces_(left->name())!=TRUESTRING ||
		removeSpaces_(right->name())!=FALSESTRING) {
		errorOut_("Name of constant wrong");
	}
	delete left;
	delete right;
	testDone_();

	left = new Constant(true);
	right = new Constant(false);
	f=new And(left,right);
	if (removeSpaces_(f->name())!=ANDSTRING) {
		errorOut_("Name of And wrong",1);
	}
	delete f;
	testDone_(1);

	left = new Constant(true);
	right = new Constant(false);
	f=new Or(left,right);
	if (removeSpaces_(f->name())!=ORSTRING) {
		errorOut_("Name of Or wrong",2);
	}
	delete f;
	testDone_(2);

	left = new Constant(true);
	f=new Not(left);
	if (removeSpaces_(f->name())!=NOTSTRING) {
		errorOut_("Name of Not wrong",3);
	}
	delete f;
	testDone_(3);

	string temp;
	f = new Variable(temp=randString_(10));
	if (removeSpaces_(f->name()) != temp) {
		errorOut_("Name of Variable wrong",4);
	}
	delete f;
	passOut_("tested the name of all Formulas");
}

void FormulaTester::testPrint() {
	func_("testPrint");
	for (int i=0 ; i<FIFTY ; i++) {
		Formula* f=0;
		Assignment ass;
		string expectedres;
		generateRandomFormula_(5,f,ass,&expectedres,false,true);
		if (!f) {
			errorOut_("Could not generate formula");
		}
		else {
			testDone_();
			ostringstream s1;
			f->print(s1);
			delete f;
			string printres = s1.str();
			if (expectedres == printres)
				continue;

			printres = removeSpaces_(printres);
			expectedres = removeSpaces_(expectedres);
			if (printres == expectedres) {
				errorOut_("print not as expected but same when removing spaces",2);
				continue;
			}

			if (lc_(expectedres) == lc_(printres)) {
				errorOut_("print not as expected but same when removing spaces and lowercase-ing",3);
				continue;
			}

			errorOut_("print not as expected",1);
		}
	}
	passOut_("Printed random formulas as expected");
}

bool FormulaTester::generateRandomFormula_(int maxDepth,
		Formula*& formula,
		Assignment& ass,
		string* print,
		bool forceInvalid,
		bool forceRecursion) {
	// If depth>0 then forceRecursion must be set to true.
	// the type of formula should be:
	// If forceRecursion is true: 2-5 (and, or, not)
	// If forceRecursion is false and forceInvalid is true: 1-5 (variable-invalid)
	// If forceRecursion is false and forceInvalid is false: 0-4 (const-not)
	// INVALID=4

	int temp(rand());
	if (forceRecursion) { // 2-4: and, or, not
		temp = temp%3+2;
	} else if (forceInvalid) { // 1-5: variable, and, or, not, invalid
		temp = temp%5+1;
	} else { // 0-5: const, variable, and, or, not
		temp = temp%5;
	}

	if (0 == maxDepth) { // const, variable
		if (forceInvalid) {
			temp = (rand()%2)*4+1; // Variable, invalid
		}
		else {
			temp=rand()%2; // Const, variable
		}
	}

	bool res=false;
	bool leftBool=true,rightBool=true;
	Formula* leftForm=0;
	Formula* rightForm=0;
	FormulaType type = (FormulaType) temp;
	bool localForceInvalid= rand()%2;
	switch (type) {
	case CONSTANT:
	{
		res = rand()%2;
		formula = new Constant(res);
		if (print) {
			*print = (res ? "T" : "F");
		}
		return res;
	}
	case VARIABLE:
	{
		res = rand()%2;
		if (forceInvalid) {
			formula = new Variable("");
		} else {
			string temp = this->randString_(10);
			formula = new Variable(temp);
			if (print) {
				*print = temp;
			}
			ass.set(temp,res);
		}
		return res;
	}
	case AND:
	{
		string temp1;
		string temp2;
		string* t1p = (print ? &temp1 : nullptr);
		string* t2p = (print ? &temp2 : nullptr);
		leftBool =
				generateRandomFormula_(--maxDepth,leftForm,ass,t1p,localForceInvalid&&forceInvalid);
		rightBool =
				generateRandomFormula_(maxDepth,rightForm,ass,t2p,!localForceInvalid&&forceInvalid);
		formula = new And(leftForm,rightForm);
		if (print) {
			*print = "(" + temp1 + " and " + temp2 + ")";
		}
		return leftBool && rightBool;
	}
	case OR:
	{
		string temp1;
		string temp2;
		string* t1p = (print ? &temp1 : nullptr);
		string* t2p = (print ? &temp2 : nullptr);
		leftBool =
				generateRandomFormula_(--maxDepth,leftForm,ass,t1p,localForceInvalid&&forceInvalid);
		rightBool =
				generateRandomFormula_(maxDepth,rightForm,ass,t2p,!localForceInvalid&&forceInvalid);
		formula = new Or(leftForm,rightForm);
		if (print) {
			*print = "(" + temp1 + " or " + temp2 + ")";
		}
		return leftBool || rightBool;
	}
	case NOT:
	{
		string temp1;
		string* t1p = (print ? &temp1 : nullptr);
		leftBool =
				generateRandomFormula_(--maxDepth,leftForm,ass,t1p,forceInvalid);
		formula = new Not(leftForm);
		if (print) {
			*print = "(not " + temp1 + ")";
		}
		return !leftBool;
	}
	case INVALID:
	default:
		formula = nullptr;
		return false;
	}
}

