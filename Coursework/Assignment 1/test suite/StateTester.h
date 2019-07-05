/*
 * StateTester.h
 *
 *  Created on: 1 Nov 2017
 *      Author: np183
 */

#ifndef STATETESTER_H_
#define STATETESTER_H_

#include "TesterBase.h"
#include "State.h"

class StateTester : public TesterBase {
public:
	StateTester();
	~StateTester();

	void testCtor();
	void testLabel();
	void testTransition();

	void testCopyCtor();
	void testMoveCtor();
	void testName();

	void testOpEq();

	void testAssignmentOpCopy();
	void testAssignmentOpMove();

	void testStability();
	void testMoveMemory();
private:
	static constexpr unsigned int VERY_SMALL_ARRAY = 10;
	static constexpr unsigned int SMALL_ARRAY = 100;
	static constexpr unsigned int LARGE_ARRAY = 1000;
	static constexpr unsigned int VERY_LARGE_ARRAY = 1000; // 000;
};

#endif /* STATETESTER_H_ */
