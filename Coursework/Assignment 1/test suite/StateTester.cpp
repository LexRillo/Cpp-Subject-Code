/*
 * StateTester.cpp
 *
 *  Created on: 1 Nov 2017
 *      Author: np183
 */

#include "StateTester.h"

#include <iostream>
#include <set>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>

using std::set;
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::ostringstream;
using std::set;

StateTester::StateTester() {}
StateTester::~StateTester() {}

void StateTester::testCtor() {
	func_("testCtor");

	State st;
	string name(this->randString_(20));
	State st1(name);

	if (st.getName() != "" || st1.getName() != name) {
		errorOut_("Wrong name");
	}

	if (st.numberOfLabels() || st1.numberOfLabels()) {
		errorOut_("Empty state should have no labels",1);
	}

	if (st.numberOfTransitions() || st1.numberOfTransitions()) {
		errorOut_("Empty state should have no transitions",2);
	}

	passOut_("testCtor");
}

void StateTester::testLabel() {
	func_("testLabel");

	State st("name");

	ostringstream stream;
	set<string> labels;
	int numlabels = 0;
	for (int i=0 ; i<SMALL_ARRAY ; i++) {
		stream << i;
		if (!st.addLabel(stream.str())) {
			errorOut_("Failed to add a label");
		} else {
			++numlabels;
			labels.insert(stream.str());
		}

		if (st.numberOfLabels() != numlabels) {
			errorOut_("Wrong number of labels",1);
		}
	}

	const int size = labels.size();
	for (int i=-1 ; i <= size ; ++i) {
		string temp="";
		if (st.getLabel(i,temp) && (i<0 || size==i)) {
			errorOut_("Label returned out of bound",2);
		}

		if (!st.getLabel(i,temp) && i>=0 && i!=size) {
			errorOut_("Label not returned in bound",3);
		}

		if (i>=0 && i<size) {
			set<string>::iterator it;
			if ((it=labels.find(temp)) == labels.end()) {
				errorOut_("Wrong label returned",4);
			}
			labels.erase(it);
		}
	}

	if (st.numberOfLabels() != SMALL_ARRAY) {
		errorOut_("not all lables inserted",5);
	}

	{
		State ostate;
		if (!ostate.addLabel("blah") || ostate.addLabel("blah")) {
			errorOut_("not adding a legal label or adding the same label twice",6);
		}
	}

	passOut_("Added labels and played with them");
}

void StateTester::testTransition() {
	func_("testTransition");

	{
		State st("name");
		State other("oname");

		Transition tr(&st,&other);
		if (!st.addTransition(&tr)) {
			errorOut_("Failed to add a transition");
		}

		Transition otr(&other,&st);
		if (st.addTransition(&otr)) {
			errorOut_("Added a bad transition",1);
		}

		Transition ootr(&st,&other);
		if (st.addTransition(&ootr)) {
			errorOut_("Added the same transition twice",2);
		}

		other.setName("oname1");
		if (st.addTransition(&tr)) {
			errorOut_("Change in target state not reflected in transition",3);
		}
	}

	State* stArray[SMALL_ARRAY];
	Transition* trArray[SMALL_ARRAY];
	{
		State dynState("name");
		set<string> labels;

		for (int i=0 ; i < SMALL_ARRAY ; i++) {
			ostringstream stream;
			stream << "name" << i;
			stArray[i] = new State(stream.str());
			trArray[i] = new Transition(&dynState,stArray[i]);
			if (!dynState.addTransition(trArray[i])) {
				errorOut_("Failed to add a transition",4);
				continue;
			}
			labels.insert(stream.str());
			if (dynState.numberOfTransitions() != labels.size()) {
				errorOut_("Wrong number of transitions",5);
			}
		}

		for (set<string>::iterator i=labels.begin() ;
				i != labels.end() ;
				++i) {
			Transition* transPtr=nullptr;
			if (!dynState.getTransition(*i,transPtr) || !transPtr) {
				errorOut_("Failed to retrieve a transition",6);
			}
		}

		const int size = labels.size();
		for (int i=-1 ; i <= size ; i++) {
			Transition* transPtr = nullptr;
			if (dynState.getTransition(i,transPtr) && (i<0 || size==i)) {
				errorOut_("Transition returned out of bound",7);
			}
			if (!dynState.getTransition(i,transPtr) && i>=0 && i!= size) {
				errorOut_("Transition not returned in bound",8);
			}
			if (dynState.getTransition(i,transPtr)) {
				State* statePtr=nullptr;
				set<string>::iterator labeli;
				if (!transPtr->getState2(statePtr) || !statePtr) {
					errorOut_("Failed to get a state from a transition",9);
				} else {
					labeli = labels.find(statePtr->getName());
					if (labeli == labels.end()) {
						errorOut_("Returned state has a wrong name",10);
					}
					labels.erase(labeli);
				}
			}
		}
	}

	for (int i=0 ; i < SMALL_ARRAY ; i++) {
		delete stArray[i];
		delete trArray[i];
	}

	passOut_("testTransition");
}

void StateTester::testCopyCtor() {
	func_("testCopyCtor");

	const string name(this->randString_(30));
	State* st = new State(name);

	ostringstream stream;
	Transition* trArray[SMALL_ARRAY];
	State* stArray[SMALL_ARRAY];
	set<string> labels;
	for (int i=0 ; i<SMALL_ARRAY ; i++) {
		stream << i;
		st->addLabel(stream.str());
		stArray[i] = new State(stream.str());
		labels.insert(stream.str());
		trArray[i] = new Transition(st,stArray[i]);
		st->addTransition(trArray[i]);
	}

	State stCopy(*st);
	delete st;
	st = nullptr;

	if (stCopy.getName() != name) {
		errorOut_("Copy constroctor not copying name");
	}
	if (stCopy.numberOfLabels() != SMALL_ARRAY) {
		errorOut_("Copy constroctor not copying number of lables",1);
	}
	if (stCopy.numberOfTransitions() != SMALL_ARRAY) {
		errorOut_("Copy constructor not copying number of transitions",2);
	}

	int size = labels.size();
	set<string> lcopy1 = labels;
	set<string> lcopy2 = labels;
	for (int i=0 ; i < size ; ++i) {
		string temp;
		set<string>::iterator it;
		stCopy.getLabel(i,temp);
		if ((it=lcopy1.find(temp)) == lcopy1.end()) {
			errorOut_("Wrong label returned",3);
		} else {
			lcopy1.erase(it);
		}

		Transition* tr(nullptr);
		State* ost(nullptr);
		stCopy.getTransition(i,tr);

		if (!tr || !tr->getState2(ost) || !ost ||
			(it=lcopy2.find(ost->getName())) == lcopy2.end()) {
			errorOut_("Wrong transition returned",4);
		} else {
			lcopy2.erase(it);
		}
	}

	for (set<string>::iterator it=labels.begin() ;
		 it != labels.end() ; ++it) {
		Transition* tr(nullptr);
		if (!stCopy.getTransition(*it,tr) || !tr) {
			errorOut_("Could not find transition",5);
		}
	}

	for (int i=0 ; i < SMALL_ARRAY ; i++) {
		delete stArray[i];
		delete trArray[i];
	}

	passOut_("testCopyCtor");
}

void StateTester::testMoveCtor() {
	func_("testMoveCtor");
	const string name(this->randString_(30));
	State* st = new State(name);
	Transition* trArray[SMALL_ARRAY];
	State* stArray[SMALL_ARRAY];
	set<string> labels;

	{
		ostringstream stream;
		for (int i=0 ; i<SMALL_ARRAY ; i++) {
			stream << i;
			st->addLabel(stream.str());
			stArray[i] = new State(stream.str());
			labels.insert(stream.str());
			trArray[i] = new Transition(st,stArray[i]);
			st->addTransition(trArray[i]);
		}
	}

	State stCopy(std::move(*st));
	delete st;
	st = nullptr;

	if (stCopy.getName() != name) {
		errorOut_("Move constroctor not copying name");
	}
	if (stCopy.numberOfLabels() != SMALL_ARRAY) {
		errorOut_("Move constroctor not copying number of lables",1);
	}
	if (stCopy.numberOfTransitions() != SMALL_ARRAY) {
		errorOut_("Move constructor not copying number of transitions",2);
	}

	int size = labels.size();
	set<string> lcopy1 = labels;
	set<string> lcopy2 = labels;
	for (int i=0 ; i < size ; ++i) {
		string temp;
		set<string>::iterator it;
		stCopy.getLabel(i,temp);
		if ((it=lcopy1.find(temp)) == lcopy1.end()) {
			errorOut_("Wrong label returned",3);
		} else {
			lcopy1.erase(it);
		}

		Transition* tr(nullptr);
		State* ost(nullptr);
		stCopy.getTransition(i,tr);

		if (!tr || !tr->getState2(ost) || !ost ||
			(it=lcopy2.find(ost->getName())) == lcopy2.end()) {
			errorOut_("Wrong transition returned",4);
		} else {
			lcopy2.erase(it);
		}
	}

	for (set<string>::iterator it=labels.begin() ;
		 it != labels.end() ; ++it) {
		Transition* tr(nullptr);
		if (!stCopy.getTransition(*it,tr) || !tr) {
			errorOut_("Could not find transition",5);
		}
	}

	for (int i=0 ; i < SMALL_ARRAY ; i++) {
		delete stArray[i];
		delete trArray[i];
	}

	passOut_("testMoveCtor");
}

void StateTester::testName() {
	func_("testName");

	const string name(this->randString_(30));
	State st(name);

	if (st.getName() != name) {
		errorOut_("wrong name");
	}

	passOut_("testName");
}


void StateTester::testOpEq() {
	func_("testOpEq");

	State st("name");
	State copy1("name");
	State copy2("name");
	State copy3("oname");

	ostringstream stream;
	Transition* trArray[4*SMALL_ARRAY];
	State* stArray[4*SMALL_ARRAY];

	for (int i=0 ; i<SMALL_ARRAY ; i++) {
		stream << i;
		st.addLabel(stream.str());
		copy1.addLabel(stream.str());
		copy2.addLabel(stream.str());
		copy3.addLabel(stream.str());

		stArray[i] = new State(stream.str());
		stArray[SMALL_ARRAY+i] = new State(stream.str());
		stArray[2*SMALL_ARRAY+i] = new State(stream.str());
		stArray[3*SMALL_ARRAY+i] = new State(stream.str());

		trArray[i] = new Transition(&st,stArray[i]);
		trArray[SMALL_ARRAY+i] = new Transition(&copy1,stArray[SMALL_ARRAY+i]);
		trArray[2*SMALL_ARRAY+i] = new Transition(&copy2,stArray[2*SMALL_ARRAY+i]);
		trArray[3*SMALL_ARRAY+i] = new Transition(&copy3,stArray[3*SMALL_ARRAY+i]);
		st.addTransition(trArray[i]);
		copy1.addTransition(trArray[SMALL_ARRAY+i]);
		copy2.addTransition(trArray[2*SMALL_ARRAY+i]);
		copy3.addTransition(trArray[3*SMALL_ARRAY+i]);
	}

	if (!(st==copy1)) {
		errorOut_("Equivalent states are different");
	}

	if (st==copy3) {
		errorOut_("States with different names equivalent",1);
	}

	copy1.addLabel("blah");
	if (st==copy1) {
		errorOut_("States with different label sets equivalent",2);
	}

	State lastS("blah");
	Transition lastT(&copy2,&lastS);
	copy2.addTransition(&lastT);
	if (st==copy2) {
		errorOut_("States with different transition sets equivalent",3);
	}

	for (int i=0 ; i < 4*SMALL_ARRAY ; ++i) {
		delete stArray[i];
		delete trArray[i];
	}

	passOut_("testOpEq");
}

void StateTester::testAssignmentOpCopy() {
	func_("testAssignmentOpCopy");

	const string name(this->randString_(30));
	State* st = new State(name);

	ostringstream stream;
	Transition* trArray[SMALL_ARRAY];
	State* stArray[SMALL_ARRAY];
	set<string> labels;
	for (int i=0 ; i<SMALL_ARRAY ; i++) {
		stream << i;
		st->addLabel(stream.str());
		stArray[i] = new State(stream.str());
		labels.insert(stream.str());
		trArray[i] = new Transition(st,stArray[i]);
		st->addTransition(trArray[i]);
	}

	State stCopy;

	{
		Transition* trArray1[SMALL_ARRAY];
		State* stArray1[SMALL_ARRAY];
		for (int i=0 ; i<SMALL_ARRAY ; i++) {
			stCopy.addLabel(randString_(10));
			stArray1[i] = new State(randString_(10));
			trArray1[i] = new Transition(st,stArray1[i]);
			stCopy.addTransition(trArray1[i]);
		}
		stCopy = *st;
		delete st;
		st = nullptr;

		for (int i=0 ; i<SMALL_ARRAY ; ++i) {
			delete stArray1[i];
			delete trArray1[i];
		}
	}

	if (stCopy.getName() != name) {
		errorOut_("Copy assignment op not copying name");
	}
	if (stCopy.numberOfLabels() != SMALL_ARRAY) {
		errorOut_("Copy assignment op not copying number of lables",1);
	}
	if (stCopy.numberOfTransitions() != SMALL_ARRAY) {
		errorOut_("Copy assignment op not copying number of transitions",2);
	}

	int size = labels.size();
	set<string> lcopy1 = labels;
	set<string> lcopy2 = labels;
	for (int i=0 ; i < size ; ++i) {
		string temp;
		set<string>::iterator it;
		stCopy.getLabel(i,temp);
		if ((it=lcopy1.find(temp)) == lcopy1.end()) {
			errorOut_("Wrong label returned",3);
		} else {
			lcopy1.erase(it);
		}

		Transition* tr(nullptr);
		State* ost(nullptr);
		stCopy.getTransition(i,tr);

		if (!tr || !tr->getState2(ost) || !ost ||
			(it=lcopy2.find(ost->getName())) == lcopy2.end()) {
			errorOut_("Wrong transition returned",4);
		} else {
			lcopy2.erase(it);
		}
	}

	for (set<string>::iterator it=labels.begin() ;
		 it != labels.end() ; ++it) {
		Transition* tr(nullptr);
		if (!stCopy.getTransition(*it,tr) || !tr) {
			errorOut_("Could not find transition",5);
		}
	}

	for (int i=0 ; i < SMALL_ARRAY ; i++) {
		delete stArray[i];
		delete trArray[i];
	}

	passOut_("testAssignmentOpCopy");
}

void StateTester::testAssignmentOpMove() {
	func_("testAssignmentOpMove");
	const string name(this->randString_(30));
	State* st = new State(name);

	ostringstream stream;
	Transition* trArray[SMALL_ARRAY];
	State* stArray[SMALL_ARRAY];
	set<string> labels;
	for (int i=0 ; i<SMALL_ARRAY ; i++) {
		stream << i;
		st->addLabel(stream.str());
		stArray[i] = new State(stream.str());
		labels.insert(stream.str());
		trArray[i] = new Transition(st,stArray[i]);
		st->addTransition(trArray[i]);
	}

	State stCopy;

	{
		Transition* trArray1[SMALL_ARRAY];
		State* stArray1[SMALL_ARRAY];
		for (int i=0 ; i<SMALL_ARRAY ; i++) {
			stCopy.addLabel(randString_(10));
			stArray1[i] = new State(randString_(10));
			trArray1[i] = new Transition(st,stArray1[i]);
			stCopy.addTransition(trArray1[i]);
		}
		stCopy = std::move(*st);
		delete st;
		st = nullptr;

		for (int i=0 ; i<SMALL_ARRAY ; ++i) {
			delete stArray1[i];
			delete trArray1[i];
		}
	}

	if (stCopy.getName() != name) {
		errorOut_("Copy assignment op not copying name");
	}
	if (stCopy.numberOfLabels() != SMALL_ARRAY) {
		errorOut_("Copy assignment op not copying number of lables",1);
	}
	if (stCopy.numberOfTransitions() != SMALL_ARRAY) {
		errorOut_("Copy assignment op not copying number of transitions",2);
	}

	int size = labels.size();
	set<string> lcopy1 = labels;
	set<string> lcopy2 = labels;
	for (int i=0 ; i < size ; ++i) {
		string temp;
		set<string>::iterator it;
		stCopy.getLabel(i,temp);
		if ((it=lcopy1.find(temp)) == lcopy1.end()) {
			errorOut_("Wrong label returned",3);
		} else {
			lcopy1.erase(it);
		}

		Transition* tr(nullptr);
		State* ost(nullptr);
		stCopy.getTransition(i,tr);

		if (!tr || !tr->getState2(ost) || !ost ||
			(it=lcopy2.find(ost->getName())) == lcopy2.end()) {
			errorOut_("Wrong transition returned",4);
		} else {
			lcopy2.erase(it);
		}
	}

	for (set<string>::iterator it=labels.begin() ;
		 it != labels.end() ; ++it) {
		Transition* tr(nullptr);
		if (!stCopy.getTransition(*it,tr) || !tr) {
			errorOut_("Could not find transition",5);
		}
	}

	for (int i=0 ; i < SMALL_ARRAY ; i++) {
		delete stArray[i];
		delete trArray[i];
	}

	passOut_("testAssignmentOpMove");
}

void StateTester::testStability() {
	func_("testStability");
	for (int i=0 ; i<LARGE_ARRAY ; ++i) {
		Transition* trArray[VERY_LARGE_ARRAY];
		State* stArray[VERY_LARGE_ARRAY];
		{
			State st(randString_(10));

			for (int j=0 ; j<VERY_LARGE_ARRAY ; j++) {
				st.addLabel(randString_(5));
				stArray[j] = new State(randString_(5));
				trArray[j] = new Transition(&st,stArray[j]);
				st.addTransition(trArray[j]);
			}
		}

		for (int j=0 ; j<VERY_LARGE_ARRAY ; ++j) {
			delete stArray[j];
			delete trArray[j];
		}

	}
	passOut_("testStability");
}

void StateTester::testMoveMemory() {
	func_("testMoveMemory");

	{
		State* array[VERY_LARGE_ARRAY];
		Transition* trArray[VERY_LARGE_ARRAY];
		State* stArray[VERY_LARGE_ARRAY];

		for (int i=0 ; i<LARGE_ARRAY ; ++i) {
			{
				array[0] = new State(randString_(10));
				for (int j=0 ; j<VERY_LARGE_ARRAY ; j++) {
					array[0]->addLabel(randString_(5));
					stArray[j] = new State(randString_(5));
					trArray[j] = new Transition(array[0],stArray[j]);
					array[0]->addTransition(trArray[j]);
				}
			}

		}

		for (int i=1 ; i<VERY_LARGE_ARRAY ; ++i) {
			array[i] = new State(std::move(*(array[i-1])));
		}

		for (int j=0 ; j<VERY_LARGE_ARRAY ; ++j) {
			delete stArray[j];
			delete trArray[j];
		}
		for (int j=0 ; j<VERY_LARGE_ARRAY ; ++j) {
			delete array[j];
		}
	}
	testDone_();

	{
		State* array[VERY_LARGE_ARRAY];
		Transition* trArray[VERY_LARGE_ARRAY];
		State* stArray[VERY_LARGE_ARRAY];

		for (int i=0 ; i<LARGE_ARRAY ; ++i) {
			{
				array[0] = new State(randString_(10));
				for (int j=0 ; j<VERY_LARGE_ARRAY ; j++) {
					array[0]->addLabel(randString_(5));
					stArray[j] = new State(randString_(5));
					trArray[j] = new Transition(array[0],stArray[j]);
					array[0]->addTransition(trArray[j]);
				}
			}

		}

		for (int i=1 ; i<VERY_LARGE_ARRAY ; ++i) {
			array[i] = new State("");
			(*array[i]) = std::move(*(array[i-1]));
			delete array[i-1];
		}

		for (int j=0 ; j<VERY_LARGE_ARRAY ; ++j) {
			delete stArray[j];
			delete trArray[j];
		}

		delete array[VERY_LARGE_ARRAY-1];
	}

	passOut_("testMoveMemory");
}
