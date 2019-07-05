/*
 * VectorTester.h
 *
 *  Created on: 15 Oct 2014
 *      Author: np183
 */

#ifndef VECTORTESTER_H_
#define VECTORTESTER_H_

#include <string>

class VectorTester {
public:
	VectorTester();
	~VectorTester();

	void testCtor();
	void testCopyCtor();
	void testPushBack();
	void testOperatorSqBr();
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

#endif /* VECTORTESTER_H_ */
