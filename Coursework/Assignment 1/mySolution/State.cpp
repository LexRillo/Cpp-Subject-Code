#include <string>
#include <sstream>
#include <iostream>
// #include <cstdlib>
#include "State.h"

using std::string;
using std::ostream;
using std::endl;

// Default constructor
State::State()
{
	// implement me
	name_ = "";
	numberLabels = 0;
	numberTransitions = 0;
}  

// Constructor detailing name
State::State(const string& name) {
	// implement me
	setName(name);
	numberLabels = 0;
	numberTransitions = 0;
}

// Copy constructor
State::State(const State& other) {
	// implement me
	// Copying the variables from other to this (state)
	name_ = other.name_;
	numberLabels = other.numberLabels;
	numberTransitions = other.numberTransitions;
	
	// Copying the labels one by one
	labels_ = new string[numberLabels];
	for(int i= 0; i<numberLabels; i++){
		labels_[i] = other.labels_[i];
	}
	
	// Copying the transition pointers one by one
	transitions_ = new Transition*[numberTransitions];
	for(int i= 0; i<numberTransitions; i++){
		transitions_[i] = other.transitions_[i];
	}
}

// Move constructor
State::State(State&& other) {
	// implement me
	// Copying all variables from other to this (state)
	name_ = other.name_;
	numberLabels = other.numberLabels;
	numberTransitions = other.numberTransitions;
	labels_ = other.labels_;
	transitions_ = other.transitions_;

	// Nullifying all the variables from other
	other.name_ = "";
	other.numberLabels = 0;
	other.numberTransitions = 0;
	other.labels_ = nullptr;
	other.transitions_ = nullptr;
}

// Destructor
State::~State() 
{
	// implement me
	// Nullifying pointers and dynamic arrays
	if(labels_){
		labels_ = nullptr;
	}
	if(transitions_){
		delete [] transitions_;
		transitions_ = nullptr;
	}
}

// Setter for variable name_
void State::setName(const string& name) 
{
	// implement me
	name_ = name;
}

// Getter for variable name_ 
string State::getName() const 
{
	// implement me
  	return name_;
}

// Method to add a Transition to the array transitions_
bool State::addTransition(Transition* trans) 
{
	// implement me
	State* tempState = nullptr;
	State* anothertempState = nullptr;
	
	// If the transition does not start from this state return false
	if(trans->getState1(tempState)){
		if(this != tempState){
			return false;
		}
	}
	
	// If a transition to the target state already exists return false
	if(trans->getState2(tempState)){
		for(int i=0; i<numberTransitions; i++){
			transitions_[i]->getState2(anothertempState);
			if(anothertempState == tempState){
				return false;
			}
		}
	}
	
	// Allocate a new transition and add to array
	numberTransitions++;
	Transition** temp = new Transition*[numberTransitions];
	for(int i = 0; i < numberTransitions - 1; i++){
		temp[i] = transitions_[i];
	}

	// Garbage collect
	if(numberTransitions){
		delete [] transitions_;
	}
	transitions_ = temp;	
	transitions_[numberTransitions - 1] = trans;
    	return true;
}

// Getter for a Transition defined by the name of its target state
bool State::getTransition(const string& targetStateName, Transition*& result)
{
	// implement me
	State* tempState = nullptr;
	for(int i=0; i<numberTransitions; i++){
		transitions_[i]->getState2(tempState);
		if(tempState->getName() == targetStateName){
			result = transitions_[i];
			return true;
		}
	}
  	return false;
}

// Getter for a Transition defined by the name of its target state for const variables
bool State::getTransition(const string& targetStateName, const Transition*& result) const
{
	// implement me
	State* tempState = nullptr;
	for(int i=0; i<numberTransitions; i++){
		transitions_[i]->getState2(tempState);
		if(tempState->getName() == targetStateName){
			result = transitions_[i];
			return true;
		}
	}
  	return false;
}

// Getter for a Transition defined by its location in the array
bool State::getTransition(int location, Transition*& result)
{
	// implement me
	// If the location is invalid return false.
	if(location < numberTransitions){
		result = transitions_[location];
		return true;
	}
    	return false;
}

// Getter for a Transition defined by its location in the array for const variables
bool State::getTransition(int location, const Transition*& result) const
{
	// implement me
	// If the location is invalid return false.
	if(location < numberTransitions){
		result = transitions_[location];
		return true;
	}
    	return false;
}

// Getter for the variables numberTransitions (size of the array transitions_)
int State::numberOfTransitions() const 
{
	// implement me
  	return numberTransitions;
}

// Method to add a Label to the array labels_
bool State::addLabel(const string& label) 
{
	// implement me
	// Check if the label already exists
	if(numberLabels != 0){
		for(int i = 0; i < numberLabels; i++){
			if(labels_[i] == label){
				return false;
			}
		}
	}
	
	// Allocate a new label and add to array
	numberLabels++;
	string* temp = new string[numberLabels];
	for(int i = 0; i < numberLabels - 1; i++){
		temp[i] = labels_[i];
	}
	if(numberLabels){
		delete [] labels_;
	}	
	labels_ = temp;	
	labels_[numberLabels - 1] = label;
    	return true;
}

// Getter for the variables numberLabels (size of the array labels_)
int State::numberOfLabels() const
{
	// implement me
  	return numberLabels;
}

// Getter for a Label defined by its location in the array
bool State::getLabel(int location, string& label) const
{
	// implement me
	// If the location is invalid return false.
	if(location < numberLabels){
		label = labels_[location];
		return true;
	}
    	return false;
}

// Copy operator
State& State::operator=(const State& other)
{
	// implement me
	// Performs a shallow copy of other's variables
	if (this != &other) {
		name_ = other.name_;

		if (numberLabels < other.numberLabels) {
			delete [] labels_;
			labels_ = new string[other.numberLabels+1];
		}
		numberLabels = other.numberLabels;
		for (int i=0 ; i<numberLabels ; ++i) {
			labels_[i] = other.labels_[i];
		}

		if (numberTransitions < other.numberTransitions) {
			delete [] transitions_;
			transitions_ = new Transition*[other.numberTransitions];
		}
		numberTransitions = other.numberTransitions;
		for (int i=0 ; i<numberTransitions ; ++i) {
			transitions_[i] = other.transitions_[i];
		}
	}
	return *this;
}

// Move operator
State& State::operator=(State&& other)
{
	// implement me
	// Copying all variables from other to this (state) and nullifying them
	if (this != &other) {
		name_ = other.name_;
		other.name_ = "";
		
		labels_ = other.labels_;
		other.labels_ = nullptr;

		numberLabels = other.numberLabels;
		other.numberLabels = 0;

		transitions_ = other.transitions_;
		other.transitions_ = nullptr;

		numberTransitions = other.numberTransitions;
		other.numberTransitions = 0;
	}
	return *this;
}

// Equality operator
bool State::operator==(const State& other) const {
	// implement me
	// If there are any discrepancies in the variables return false
	if (name_ != other.name_){return false;}
	if (numberTransitions != other.numberTransitions){return false;}
	if (numberLabels != other.numberLabels){return false;}

	// Loop through the transitions_ to find discrepancies
	for(int i=0; i<numberTransitions; i++){
		Transition trans = *transitions_[i];
		Transition anothertrans = *other.transitions_[i];
		if(!(trans == anothertrans)){
			return false;
		}
	}
	
	// Loop through the labels_ to find discrepancies
	for(int i=0; i<numberLabels; i++){
		string tempLabel;
		other.getLabel(i, tempLabel);
		bool found = false;
		for(int j = 0; j < numberLabels; j++){
			string tempLabel2;
			getLabel(j, tempLabel2);
			if(tempLabel == tempLabel2){
				found = true;
			}
		}
		if(found == false){
			return false;
		}
	}
    	return true;
}

// Print method
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

