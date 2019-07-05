/*
 * Automaton.cpp
 * Created on: 23/10/2017
 * Author: np183
 *         Department of Informatics
 * 	   University of Leicester
 */
#include <iostream>
#include <string>
#include "Automaton.h"

Automaton::Automaton() 
{
	// implement me
}

Automaton::Automaton(const std::string& name)
{
	// implement me
}

Automaton::Automaton(const Automaton& other) 
{
	// implement me
}

Automaton::Automaton(Automaton&& other)
{
	// implement me
}

Automaton::~Automaton() 
{
	// implement me
}

void Automaton::setName(const std::string& name)
{
	// implement me
}

std::string Automaton::getName() const
{
	// implement me
	return "";
}

bool Automaton::addState(const std::string& stateName, State*& state)
{
	// implement me
	return false;
}

bool Automaton::getState(const std::string& stateName, State*& state)
{
	// implement me
	return false;
}

bool Automaton::getState(int i, State*& st)
{
	// implement me
	return false;
}

bool Automaton::getState(int i, const State*& st) const
{
	// implement me
	return false;
}

int Automaton::numberOfStates() const 
{
	// implement me
	return -1;
}

bool Automaton::addTransition(const std::string& nameSt1, const std::string& nameSt2,
		Transition*& trans)
{
	// implement me
	return false;
}

bool Automaton::getTransition(const std::string& nameSt1, const std::string& nameSt2,
		Transition*& trans)
{
	// implement me
	return false;
}

bool Automaton::getTransition(int location,Transition*& trans) 
{
	// implement me
	return false;
}

bool Automaton::getTransition(int location,const Transition*& trans) const
{
	// implement me
	return false;
}

int Automaton::numberOfTransitions() const
{
	// implement me
	return -1;
}

void Automaton::print(std::ostream& stream) const
{
	stream << "Automaton(" << getName() << "):" << std::endl;
	if (numberOfStates()>0) {
		stream << "States:" << std::endl;
		for (int i=0 ; i< numberOfStates() ; i++) {
			const State* s=nullptr;
			getState(i,s);
			stream << *s << std::endl;
		}

		if (numberOfTransitions()>0) {
			stream << "Transitions:" << std::endl;
			for (int j=0 ; j<numberOfTransitions() ; j++) {
				const Transition* t=nullptr;
				getTransition(j,t);
				stream << *t << std::endl;
			}
		}
	}
}

Automaton& Automaton::operator=(const Automaton& other)
{
	// implement me
	Automaton removeMe;
	return removeMe;
}

Automaton& Automaton::operator=(Automaton&& other)
{
	// implement me
	Automaton removeMe;
	return removeMe;
}

bool Automaton::operator==(const Automaton& other) const
{
	// implement me
	return false;
}

bool Automaton::operator!=(const Automaton& other) const
{
	// implement me
	return false;
}

std::ostream& operator<<(std::ostream& stream, const Automaton& aut)
{
	aut.print(stream);
	return stream;
}

