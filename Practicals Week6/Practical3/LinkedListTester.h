/*
 * VectorTester.h
 *
 *  Created on: 15 Oct 2014
 *      Author: np183
 */

#ifndef LINKEDLISTTESTER_H_
#define LINKEDLISTTESTER_H_

#include <string>

class LinkedListTester {
public:
	LinkedListTester();
	~LinkedListTester();

	void testCtor();
	void testCopyCtor();
	void testFunctionality();
	void testOperatorEq();
	void testSize();
	void testEmpty();
	void testClear();
	void testMemory();

private:
	void errorOut_(const std::string& errMsg, unsigned int errBit);
	bool errorSet_(unsigned int mask);
	void passOut_(const std::string& passMsg);

	char error_;
	std::string funcname_;
};

#endif /* LINKEDLISTTESTER_H_ */
