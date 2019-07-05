/*
 * BankAccountTester.h
 *
 *  Created on: Dec 2, 2017
 *      Author: np183
 */

#ifndef BANKACCOUNTTESTER_H_
#define BANKACCOUNTTESTER_H_

#include "TesterBase.h"
#include "BankAccount.h"

class BankAccountTester : public TesterBase {
public:
	BankAccountTester(int i=0);
	~BankAccountTester();

	void testCurrentConstructor();
	void testSavingsConstructor();
	void testStockConstructor();
	void testBalance();
	void testType();
	void testToString();
	void testOperatorRedir();
	void testDay();
	void testMonth();
	void testBuySell();
private:
	// See https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
	bool eq_(float,float);
	bool neq_(float,float);
};

#endif /* BANKACCOUNTTESTER_H_ */
