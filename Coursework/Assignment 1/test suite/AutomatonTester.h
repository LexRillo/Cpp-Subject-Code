/*
 * AutomatonTester.h
 *
 *  Created on: 1 Nov 2017
 *      Author: np183
 */

#ifndef AUTOMATONTESTER_H_
#define AUTOMATONTESTER_H_

#include <vector>
#include <map>
#include <set>
#include <string>

#include "TesterBase.h"
#include "State.h"
#include "Automaton.h"

class AutomatonTester : public TesterBase {
public:
	AutomatonTester();
	~AutomatonTester();

	void testBasic();
	void testMemory();
	void testStability();
	void testCopyCtor();
	void testMoveCtor();
	void testAssOpCopy();
	void testAssOpMove();
	void testIterateState();
	void testStateChangeName();

private:
	static constexpr unsigned int VERY_SMALL_ARRAY = 10;
	static constexpr unsigned int SMALL_ARRAY = 100;
	static constexpr unsigned int LARGE_ARRAY = 1000;
	static constexpr unsigned int VERY_LARGE_ARRAY = 1000; // 000;

	void buildCircularAutomaton_(Automaton&, int);
	void buildCliqueAutomaton_(Automaton&, int, bool labels=true);
	void buildRandomAutomaton_(Automaton&,std::vector<std::string>&,
			std::map<std::string,std::vector<std::string>>&,
			std::set<std::pair<std::string,std::string>>&,
			int,float);
};

#endif /* AUTOMATONTESTER_H_ */
