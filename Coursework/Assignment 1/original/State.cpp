#include <string>
#include <sstream>
#include <iostream>
// #include <cstdlib>
#include "State.h"

using std::string;
using std::ostream;
using std::endl;

State::State()
{
	// implement me
}  

State::State(const string& name) {
	// implement me
}

State::State(const State& other) {
	// implement me
}

State::State(State&& other) {
	// implement me
}

State::~State() 
{
	// implement me
}

void State::setName(const string& name) 
{
	// implement me
}

string State::getName() const 
{
	// implement me
  return "";
}

bool State::addTransition(Transition* trans) 
{
	// implement me
    return false;
}

bool State::getTransition(const string& targetStateName, Transition*& result)
{
	// implement me
  return false;
}

bool State::getTransition(const string& targetStateName, const Transition*& result) const
{
	// implement me
  return false;
}
bool State::getTransition(int location, Transition*& result)
{
	// implement me
    return false;
}

bool State::getTransition(int location, const Transition*& result) const
{
	// implement me
    return false;
}

int State::numberOfTransitions() const 
{
	// implement me
  return -1;
}

bool State::addLabel(const string& label) 
{
	// implement me
  return false;
}

int State::numberOfLabels() const
{
	// implement me
  return -1;
}

bool State::getLabel(int location, string& label) const
{
	// implement me
    return false;
}

State& State::operator=(const State& other)
{
	// implement me
	State removeMe;
	return removeMe;
}

State& State::operator=(State&& other)
{
	// implement me
	State removeMe;
	return removeMe;
}

bool State::operator==(const State& other) const {
	// implement me
    return false;
}

void State::print(ostream& stream) const
{
  bool first = true;
  stream << getName() << "(";
 
  for (int i=0 ; i<this->numberOfLabels() ; i++) {
    if (first) {
      first = false;
    }
    else {
      stream << ",";
    }
    string s;
    getLabel(i,s);
    stream << s;
  }
  stream << ")";
}

ostream& operator<< (ostream& stream, const State& st) 
{
  st.print(stream);
  return stream;
}

