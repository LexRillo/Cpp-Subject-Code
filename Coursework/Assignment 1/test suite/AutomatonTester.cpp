/*
 * AutomatonTester.cpp
 *
 *  Created on: 1 Nov 2017
 *      Author: np183
 */

#include "AutomatonTester.h"

#include <iostream>
#include <set>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>

using std::set;
using std::vector;
using std::map;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::ostringstream;
using std::ifstream;
using std::ofstream;
using std::set;
using std::pair;

AutomatonTester::AutomatonTester() {}
AutomatonTester::~AutomatonTester() {}

void AutomatonTester::testBasic() {
	func_("testBasic");

	Automaton aut("some");
	buildCircularAutomaton_(aut,5);

	State* st1=0;
	if (aut.addState("s5",st1)) {
		errorOut_("Add another state with the same name",2);
	}

	if (!aut.addState("s6",st1)) {
		errorOut_("Failed to add another state that does not exist",3);
	}

	if (!aut.getState("s1",st1)) {
		errorOut_("Failed to get a state that exists!",4);
	}

	if (aut.getState("blah",st1)) {
		errorOut_("Got a state that does not exist!",5);
	}

	Transition* tr=0;
	if (!aut.addTransition("s5","s4",tr)) {
		errorOut_("Failed to add a new transition",6);
	}

	if (aut.addTransition("s4","s5",tr)) {
		errorOut_("Added a transition that already exists",7);
	}

	if (aut.addTransition("s33","s5",tr) ||
		aut.addTransition("s5","s33",tr)) {
		errorOut_("Added a transition to a non-existing state",8);
	}

	if (!aut.getTransition("s1","s2",tr)) {
		errorOut_("Could not get an existing transition",9);
	}

	if (aut.getTransition("s1","s5",tr)) {
		errorOut_("Got a non-existing transition",10);
	}

	passOut_("testBasic");
}

void AutomatonTester::testMemory() {
	func_("testMemory");
	for (int i=0 ; i<SMALL_ARRAY ; i++) {
		Automaton aut("large");
		buildCliqueAutomaton_(aut,70);
	}
	passOut_("testMemory");
}

void AutomatonTester::testStability() {
	func_("testStability");

	Automaton* aut = new Automaton("huge");
	vector<string> states;
	map<string,vector<string>> transmap;
	set<pair<string,string>> transset;
	buildRandomAutomaton_(*aut,states,transmap,transset,100,0.5);

	states.clear();
	transmap.clear();
	transset.clear();

	for (int i=0 ; i<100 ; ++i) {
		switch (rand() % 4) {
		case 0: {
			Automaton a1(*aut);
			break;
		}
		case 1: {
			Automaton* a1 = new Automaton(std::move(*aut));
			delete aut;
			aut=a1;
			break;
		}
		case 2: {
			Automaton *a1 = new Automaton("stam");
			buildRandomAutomaton_(*a1,states,transmap,transset,100,0.5);
			states.clear();
			transmap.clear();
			transset.clear();
			*a1 = *aut;
			delete aut;
			aut = a1;
			break;
		}
		case 3:
		default: {
			Automaton *a1 = new Automaton("stam");
			buildRandomAutomaton_(*a1,states,transmap,transset,100,0.5);
			states.clear();
			transmap.clear();
			transset.clear();
			*a1 = std::move(*aut);
			delete aut;
			aut = a1;
		}
		}
	}
	delete aut;

	passOut_("testStability");
}

void AutomatonTester::testCopyCtor() {
	func_("testCopyCtor");

	Automaton* aut = new Automaton("huge");
	vector<string> states;
	map<string,vector<string>> transmap;
	set<pair<string,string>> transset;
	buildRandomAutomaton_(*aut,states,transmap,transset,100,0.5);

	Automaton copy(*aut);
	delete aut;
	aut = nullptr;

	for (vector<string>::iterator i=states.begin() ;
		 i != states.end() ; ++i) {
		State* s(nullptr);
		if (!copy.getState(*i,s) || !s) {
			errorOut_("Failed to retrieve a state");
		}
		if (transmap.find(*i) == transmap.end()) {
			Transition* t(nullptr);
			if (s->getTransition(0,t)) {
				errorOut_("Retrieved a non-existing transition",1);
			}
		} else {
			int temp = s->numberOfTransitions();
			int temp1 = transmap[*i].size();
			if (s->numberOfTransitions() != transmap[*i].size()) {
				errorOut_("Wrong number of transitions",2);
				continue;
			}

			set<string> transs(transmap[*i].begin(),transmap[*i].end());

			for (int j=0 ; j<s->numberOfTransitions() ; ++j) {
				Transition* t(nullptr);
				if (!s->getTransition(j,t) || !t) {
					errorOut_("Failed to retrieve transition (index,state)",3);
					continue;
				}
				State* s2(nullptr);
				if (!t->getState2(s2)) {
					errorOut_("Transition with no target state (index,state)",4);
					continue;
				}
				set<string>::iterator it;
				if ((it=transs.find(s2->getName())) == transs.end()) {
					errorOut_("Retrieved a non-existing transition (index,state)",5);
					continue;
				}
				transs.erase(it);
			}

			for (auto it=transmap[*i].begin() ; it != transmap[*i].end() ; ++it) {
				Transition* t(nullptr);
				if (!s->getTransition(*it,t) || !t) {
					errorOut_("Failed to retrieve a transition (label,state)",6);
				}
			}
		}
	}

	for (auto it=transset.begin(); it != transset.end() ; ++it) {
		Transition* t(nullptr);
		if (!copy.getTransition(it->first,it->second,t) || !t) {
			errorOut_("Failed to retrieve a transition (label,aut)",8);
		}
	}

	int size = transset.size();
	if (copy.numberOfTransitions() != size) {
		errorOut_("Wrong number of transitions",9);
	} else {
		for (int i=0 ; i<size ; ++i) {
			Transition* t(nullptr);
			if (!copy.getTransition(i,t) || !t) {
				errorOut_("Failed to retrieve a transition (index,aut)",10);
				continue;
			}
			State* s1(nullptr);
			State* s2(nullptr);
			if (!t->getState1(s1) || !t->getState2(s2)) {
				errorOut_("Transition with no target state (index,aut)",11);
				continue;
			}
			auto it=transset.find(make_pair(s1->getName(),s2->getName()));
			if (it == transset.end()) {
				errorOut_("Retrieved a wrong transition (index,aut)",12);
			}
			transset.erase(it);
		}
	}
	passOut_("testCopyCtor");
}

void AutomatonTester::testMoveCtor() {
	func_("testMoveCtor");

	Automaton* aut = new Automaton("huge");
	vector<string> states;
	map<string,vector<string>> transmap;
	set<pair<string,string>> transset;
	buildRandomAutomaton_(*aut,states,transmap,transset,100,0.5);

	Automaton copy(std::move(*aut));
	delete aut;
	aut = nullptr;

	for (vector<string>::iterator i=states.begin() ;
		 i != states.end() ; ++i) {
		State* s(nullptr);
		if (!copy.getState(*i,s) || !s) {
			errorOut_("Failed to retrieve a state");
		}
		if (transmap.find(*i) == transmap.end()) {
			Transition* t(nullptr);
			if (s->getTransition(0,t)) {
				errorOut_("Retrieved a non-existing transition",1);
			}
		} else {
			if (s->numberOfTransitions() != transmap[*i].size()) {
				errorOut_("Wrong number of transitions",2);
				continue;
			}

			set<string> transs(transmap[*i].begin(),transmap[*i].end());

			for (int j=0 ; j<s->numberOfTransitions() ; ++j) {
				Transition* t(nullptr);
				if (!s->getTransition(j,t) || !t) {
					errorOut_("Failed to retrieve transition (index,state)",3);
					continue;
				}
				State* s2(nullptr);
				if (!t->getState2(s2)) {
					errorOut_("Transition with no target state (index,state)",4);
					continue;
				}
				set<string>::iterator it;
				if ((it=transs.find(s2->getName())) == transs.end()) {
					errorOut_("Retrieved a non-existing transition (index,state)",5);
					continue;
				}
				transs.erase(it);
			}

			for (auto it=transmap[*i].begin() ; it != transmap[*i].end() ; ++it) {
				Transition* t(nullptr);
				if (!s->getTransition(*it,t) || !t) {
					errorOut_("Failed to retrieve a transition (label,state)",6);
				}
			}
		}
	}

	for (auto it=transset.begin(); it != transset.end() ; ++it) {
		Transition* t(nullptr);
		if (!copy.getTransition(it->first,it->second,t) || !t) {
			errorOut_("Failed to retrieve a transition (label,aut)",8);
		}
	}

	int size = transset.size();
	if (copy.numberOfTransitions() != size) {
		errorOut_("Wrong number of transitions",9);
	} else {
		for (int i=0 ; i<size ; ++i) {
			Transition* t(nullptr);
			if (!copy.getTransition(i,t) || !t) {
				errorOut_("Failed to retrieve a transition (index,aut)",10);
				continue;
			}
			State* s1(nullptr);
			State* s2(nullptr);
			if (!t->getState1(s1) || !t->getState2(s2)) {
				errorOut_("Transition with no target state (index,aut)",11);
				continue;
			}
			auto it=transset.find(make_pair(s1->getName(),s2->getName()));
			if (it == transset.end()) {
				errorOut_("Retrieved a wrong transition (index,aut)",12);
			}
			transset.erase(it);
		}
	}
	passOut_("testMoveCtor");
}

void AutomatonTester::testAssOpCopy() {
	func_("testAssOpCopy");

	Automaton* aut = new Automaton("huge");
	vector<string> states;
	map<string,vector<string>> transmap;
	set<pair<string,string>> transset;
	buildRandomAutomaton_(*aut,states,transmap,transset,100,0.5);

	Automaton copy("another");
	this->buildCliqueAutomaton_(copy,100,true);
	copy = *aut;
	delete aut;
	aut = nullptr;

	for (vector<string>::iterator i=states.begin() ;
		 i != states.end() ; ++i) {
		State* s(nullptr);
		if (!copy.getState(*i,s) || !s) {
			errorOut_("Failed to retrieve a state");
		}
		if (transmap.find(*i) == transmap.end()) {
			Transition* t(nullptr);
			if (s->getTransition(0,t)) {
				errorOut_("Retrieved a non-existing transition",1);
			}
		} else {
			int temp = s->numberOfTransitions();
			int temp1 = transmap[*i].size();
			if (s->numberOfTransitions() != transmap[*i].size()) {
				errorOut_("Wrong number of transitions",2);
				continue;
			}

			set<string> transs(transmap[*i].begin(),transmap[*i].end());

			for (int j=0 ; j<s->numberOfTransitions() ; ++j) {
				Transition* t(nullptr);
				if (!s->getTransition(j,t) || !t) {
					errorOut_("Failed to retrieve transition (index,state)",3);
					continue;
				}
				State* s2(nullptr);
				if (!t->getState2(s2)) {
					errorOut_("Transition with no target state (index,state)",4);
					continue;
				}
				set<string>::iterator it;
				if ((it=transs.find(s2->getName())) == transs.end()) {
					errorOut_("Retrieved a non-existing transition (index,state)",5);
					continue;
				}
				transs.erase(it);
			}

			for (auto it=transmap[*i].begin() ; it != transmap[*i].end() ; ++it) {
				Transition* t(nullptr);
				if (!s->getTransition(*it,t) || !t) {
					errorOut_("Failed to retrieve a transition (label,state)",6);
				}
			}
		}
	}

	for (auto it=transset.begin(); it != transset.end() ; ++it) {
		Transition* t(nullptr);
		if (!copy.getTransition(it->first,it->second,t) || !t) {
			errorOut_("Failed to retrieve a transition (label,aut)",8);
		}
	}

	int size = transset.size();
	if (copy.numberOfTransitions() != size) {
		errorOut_("Wrong number of transitions",9);
	} else {
		for (int i=0 ; i<size ; ++i) {
			Transition* t(nullptr);
			if (!copy.getTransition(i,t) || !t) {
				errorOut_("Failed to retrieve a transition (index,aut)",10);
				continue;
			}
			State* s1(nullptr);
			State* s2(nullptr);
			if (!t->getState1(s1) || !t->getState2(s2)) {
				errorOut_("Transition with no target state (index,aut)",11);
				continue;
			}
			auto it=transset.find(make_pair(s1->getName(),s2->getName()));
			if (it == transset.end()) {
				errorOut_("Retrieved a wrong transition (index,aut)",12);
			}
			transset.erase(it);
		}
	}
	passOut_("testAssOpCopy");
}

void AutomatonTester::testAssOpMove() {
	func_("testAssOpMove");

	Automaton* aut = new Automaton("huge");
	vector<string> states;
	map<string,vector<string>> transmap;
	set<pair<string,string>> transset;
	buildRandomAutomaton_(*aut,states,transmap,transset,100,0.5);

	Automaton copy("another");
	this->buildCliqueAutomaton_(copy,100,true);
	copy = std::move(*aut);
	delete aut;
	aut = nullptr;

	for (vector<string>::iterator i=states.begin() ;
		 i != states.end() ; ++i) {
		State* s(nullptr);
		if (!copy.getState(*i,s) || !s) {
			errorOut_("Failed to retrieve a state");
		}
		if (transmap.find(*i) == transmap.end()) {
			Transition* t(nullptr);
			if (s->getTransition(0,t)) {
				errorOut_("Retrieved a non-existing transition",1);
			}
		} else {
			if (s->numberOfTransitions() != transmap[*i].size()) {
				errorOut_("Wrong number of transitions",2);
				continue;
			}

			set<string> transs(transmap[*i].begin(),transmap[*i].end());

			for (int j=0 ; j<s->numberOfTransitions() ; ++j) {
				Transition* t(nullptr);
				if (!s->getTransition(j,t) || !t) {
					errorOut_("Failed to retrieve transition (index,state)",3);
					continue;
				}
				State* s2(nullptr);
				if (!t->getState2(s2)) {
					errorOut_("Transition with no target state (index,state)",4);
					continue;
				}
				set<string>::iterator it;
				if ((it=transs.find(s2->getName())) == transs.end()) {
					errorOut_("Retrieved a non-existing transition (index,state)",5);
					continue;
				}
				transs.erase(it);
			}

			for (auto it=transmap[*i].begin() ; it != transmap[*i].end() ; ++it) {
				Transition* t(nullptr);
				if (!s->getTransition(*it,t) || !t) {
					errorOut_("Failed to retrieve a transition (label,state)",6);
				}
			}
		}
	}

	for (auto it=transset.begin(); it != transset.end() ; ++it) {
		Transition* t(nullptr);
		if (!copy.getTransition(it->first,it->second,t) || !t) {
			errorOut_("Failed to retrieve a transition (label,aut)",8);
		}
	}

	int size = transset.size();
	if (copy.numberOfTransitions() != size) {
		errorOut_("Wrong number of transitions",9);
	} else {
		for (int i=0 ; i<size ; ++i) {
			Transition* t(nullptr);
			if (!copy.getTransition(i,t) || !t) {
				errorOut_("Failed to retrieve a transition (index,aut)",10);
				continue;
			}
			State* s1(nullptr);
			State* s2(nullptr);
			if (!t->getState1(s1) || !t->getState2(s2)) {
				errorOut_("Transition with no target state (index,aut)",11);
				continue;
			}
			auto it=transset.find(make_pair(s1->getName(),s2->getName()));
			if (it == transset.end()) {
				errorOut_("Retrieved a wrong transition (index,aut)",12);
			}
			transset.erase(it);
		}
	}
	passOut_("testAssOpMove");
}

void AutomatonTester::testIterateState() {
	func_("testIterateState");


	Automaton aut("MyAut");

	for (int i=0 ; i<VERY_SMALL_ARRAY ; i++) {
		ostringstream stream;
		stream << "state" << i;
		State* stateP=0;
		if (!aut.addState(stream.str(),stateP)) {
			errorOut_("Failed to add a state.");
		}
	}

	if (aut.numberOfStates() != VERY_SMALL_ARRAY) {
		errorOut_("The number of states is wrong.",1);
	}

	for (int i=0 ; i<VERY_SMALL_ARRAY ; i++) {
		State* st1=0;
		if (!aut.getState(i,st1)) {
			errorOut_("Failed to get back a state",2);
		}
		for (int j=0 ; j<VERY_SMALL_ARRAY ; j++) {
			State* st2=0;
			if (!aut.getState(j,st2)) {
				errorOut_("Failed to get back a state",2);
			}
			Transition* tr=0;
			if (!aut.addTransition(st1->getName(),st2->getName(),tr)) {
				errorOut_("Failed to add a transition",3);
			}
		}
	}

	if (aut.numberOfTransitions() != VERY_SMALL_ARRAY * VERY_SMALL_ARRAY) {
		errorOut_("The number of transitions is wrong",4);
	}

	// iterate over the transitions
	for (int i=0 ; i<VERY_SMALL_ARRAY * VERY_SMALL_ARRAY ; i++) {
		Transition* tr=0;
		if (!aut.getTransition(i,tr)) {
			errorOut_("Failed to get a transition",5);
		}
		State* s1=0;
		State* s2=0;
		if (!tr->getState1(s1) || !tr->getState2(s2)) {
			errorOut_("Failed to get states from a transition",6);
		}
		{
			ostringstream stream;
			stream << "state" << i/10;
			if (s1->getName() != stream.str()) {
				errorOut_("The state has wrong name!",7);
			}
		}
		{
			ostringstream stream;
			stream << "state" << i%10;
			if (s2->getName() != stream.str()) {
				errorOut_("The state has wrong name!",7);
			}
		}
	}
	passOut_("testIterateState");
}

void AutomatonTester::testStateChangeName() {
	func_("testStateChangeName");

	Automaton aut("MyAut");

	for (int i=0 ; i<VERY_SMALL_ARRAY ; i++) {
		ostringstream stream;
		stream << "state" << i;
		State* stateP=0;
		if (!aut.addState(stream.str(),stateP)) {
			errorOut_("Failed to add a state");
		}
	}

	State* s1=0;
	if (!aut.getState(0,s1)) {
		errorOut_("Failed to get back a state (1)",1);
	}

	if (s1->getName() != "state0") {
		errorOut_("The state has a wrong name",2);
	}

	s1->setName("blah");

	State* s2=0;
	if (!aut.getState(0,s2)) {
		errorOut_("Failed to get back a state (2)",3);
	}

	if (s2->getName() != "blah") {
		errorOut_("The state has not changed its name",4);
	}

	passOut_("testStateChangeName");
}

void AutomatonTester::buildCircularAutomaton_(Automaton& aut, int size) {
	for (int i=0 ; i<size ; ++i) {
		ostringstream s;
		s << "s" << i+1;
		State* stp(nullptr);
		if (!aut.addState(s.str(),stp) || !stp) {
			errorOut_("Failed to add a state");
		}
	}

	for (int i=0 ; i<size ; ++i) {
		ostringstream s1,s2;
		s1 << "s" << i+1;
		s2 << "s" << (size-1==i ? 1 : i+2);
		Transition* t(nullptr);
		if (!aut.addTransition(s1.str(),s2.str(),t) || !t) {
			errorOut_("Failed to add a transition",1);
		}
	}
}

void AutomatonTester::buildCliqueAutomaton_(Automaton& aut, int size, bool labels) {
	for (int i=0 ; i<size ; ++i) {
		ostringstream s;
		s << "s" << i+1;
		State* stp(nullptr);
		if (!aut.addState(s.str(),stp) || !stp) {
			errorOut_("Failed to add a state");
			continue;
		}
		for (int j=0 ; labels && j<=i ; ++j) {
			ostringstream l;
			l << j+1;
			stp->addLabel(l.str());
		}
	}

	for (int i=0 ; i<size ; ++i) {
		ostringstream s1;
		s1 << "s" << i+1;
		for (int j=0 ; j<size ; ++j) {
			ostringstream s2;
			s2 << "s" << j+1;
			Transition* t(nullptr);
			if (!aut.addTransition(s1.str(),s2.str(),t) || !t) {
				errorOut_("Failed to add a transition",1);
			}
		}
	}
}

void AutomatonTester::buildRandomAutomaton_(Automaton& aut,
		vector<string>& states,map<string,vector<string>>& transmap,
		set<pair<string,string>>& transset,
		int size,float density) {

	for (int i=0 ; i < size ; ) {
		string name(randString_(10));
		State *s(nullptr);
		if (aut.addState(name,s)) {
			states.push_back(name);
			++i;
		}
	}

	float numTrans(0.0);
	while (numTrans/(size*size) < density) {
		int state1 = rand() % size;
		int state2 = rand() % size;
		Transition* t(nullptr);
		if (aut.addTransition(states[state1],states[state2],t)) {
			transset.insert(make_pair(states[state1],states[state2]));
			if (transmap.find(states[state1]) == transmap.end()) {
				vector<string> v;
				v.push_back(states[state2]);
				transmap.insert(make_pair(states[state1],v));
			}
			else {
				transmap[states[state1]].push_back(states[state2]);
			}
			++numTrans;
		}
	}
}
