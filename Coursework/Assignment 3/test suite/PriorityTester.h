/*
 * PriorityTester.h
 *
 *  Created on: 28 Dec 2017
 *      Author: np183
 */

#ifndef PRIORITYTESTER_H_
#define PRIORITYTESTER_H_

#include <vector>
#include <string>
#include "TesterBase.h"
#include "Priority.h"

class PriorityTester : public TesterBase {
public:
	PriorityTester();
	~PriorityTester();

	void testCtor();
	void testPopSep();
	void testPopMix();
	void testSame();
	void testIterator();
	void testItAccess();
	void testItInc();
	void testStability();

private:
	template <typename T>
	void makePriority_(unsigned int size, Priority<T>&, std::vector<T*> &,int which);

	template<typename T> T* random_(T a);

	static constexpr unsigned int VERY_SMALL_ARRAY = 10;
	static constexpr unsigned int SMALL_ARRAY = 100;
	static constexpr unsigned int LARGE_ARRAY = 1000;
	static constexpr unsigned int VERY_LARGE_ARRAY = 1000000;

	static constexpr int KEYONE = 1;
	static constexpr int KEYTWO = -1;
	static constexpr int KEYBOTH = 0;
};

template<> double* PriorityTester::random_(double d);
template<> std::string* PriorityTester::random_(std::string s);

#endif /* PRIORITYTESTER_H_ */
