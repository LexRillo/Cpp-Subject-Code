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

using std::cout;
using std::endl;
using std::string;

// Default constructor
Automaton::Automaton() 
{
	// implement me
	name_ = "";
}

// Constructor detailing name
Automaton::Automaton(const std::string& name)
{
	// implement me
	setName(name);
}

// Copy constructor
Automaton::Automaton(const Automaton& other) 
{
	// implement me
	// Copying the variables from other to this (automaton)
	name_ = other.name_;
	//numberStates = other.numberStates;
	numberTransitions = other.numberTransitions;	
	// Nullifying the existing transitions_ and adding the ones from other
	transitions_ = new Transition[other.numberTransitions];
	for(int i= 0; i<other.numberTransitions; i++){
		State* tempState1;
		State* tempState2;
		string tempStateName1;
		string tempStateName2;
		Transition* trans = nullptr;
		other.transitions_[i].getState1(tempState1);
		other.transitions_[i].getState2(tempState2);
		tempStateName1 = tempState1-> getName();
		tempStateName2 = tempState2-> getName();
		addTransition(tempStateName1,tempStateName2, trans);
	}
	// Nullifying the existing states_ and adding the ones from other
	states_ = new State[other.numberStates];
	for(int i= 0; i<other.numberStates; i++){
		State* somePointer = nullptr;
		string tempStateName;
		State tempState = State(other.states_[i]);
		tempStateName = tempState.getName();
		addState(tempStateName,somePointer);
	}
}

// Move constructor
Automaton::Automaton(Automaton&& other)
{
	// implement me
	// Copying all variables from other to this (automata) 
	name_ = other.name_;
	numberStates = other.numberStates;
	numberTransitions = other.numberTransitions;
	states_ = other.states_;
	transitions_ = other.transitions_;

	// Nullifying all the variables from other
	other.name_ = "";
	other.numberStates = 0;
	other.numberTransitions = 0;
	other.states_ = nullptr;
	other.transitions_ = nullptr;
}

// Destructor
Automaton::~Automaton() 
{
	// implement me
	// Nullifying pointers and dynamic arrays
	if(states_){
		states_ = nullptr;
	}
	if(transitions_){
		transitions_ = nullptr;
	}
}

// Setter for variable name_
void Automaton::setName(const std::string& name)
{
	// implement me
	name_ = name;
}

// Getter for variable name_ 
std::string Automaton::getName() const
{
	// implement me
	return name_;
}

// Method to add a State to the array states_
bool Automaton::addState(const std::string& stateName, State*& state)
{
	// implement me
	// If a state with this name already exists return false
	if(numberStates != 0){
		State* tempState = new State[numberStates];
		for(int i = 0; i < numberStates; i++){
			if(states_[i].getName() == stateName){
				return false;
			}else{
				tempState[i] = states_[i];
			}
		}
		delete [] states_;

		// Allocate a new state and add to array
		numberStates++;
		states_ = new State[numberStates];
		for(int i = 0; i<numberStates - 1; i++){
			states_[i] = tempState[i];
		}
		State stateValue = State(stateName);
		states_[numberStates - 1] = stateValue;
		
		// Garbage collect
		delete [] tempState;
		state = &states_[numberStates - 1];
		return true;
	}else{
	// In case the states_ array is empty
		State stateValue = State(stateName);
		numberStates++;
		states_ = new State[numberStates];
		states_[0] = stateValue;
		state = &states_[0];
		return true;
	}
	return false;
}

// Getter for a State defined by its name
bool Automaton::getState(const std::string& stateName, State*& state)
{
	// implement me
	for(int i = 0; i<numberStates; i++){
		string nameOfState = states_[i].getName();
		if(nameOfState == stateName){
			state = &states_[i];
			return true;
		}
	}
	return false;
}

// Getter for a State defined by its location in state_
bool Automaton::getState(int i, State*& st)
{
	// implement me
	// If the location is invalid return false.
	if(i < numberStates){
		st = &states_[i];
		return true;
	}else{
		return false;
	}
}

// Getter for a State defined by its location in state_ for const variables
bool Automaton::getState(int i, const State*& st) const
{
	// implement me
	// If the location is invalid return false.
	if(i < numberStates){
		st = &states_[i];
		return true;
	}else{
		return false;
	}
}

// Getter for the variables numberStates (size of the array states_)
int Automaton::numberOfStates() const 
{
	// implement me
	return numberStates;
}

// Method to add a Transition to the array transitions_
bool Automaton::addTransition(const std::string& nameSt1, const std::string& nameSt2,
		Transition*& trans)
{
	// implement me
	State* temp1 = nullptr;
	State* temp2 = nullptr;
	bool found1 = false;
	bool found2 = false;
	
	// If one of the states does not exist in the automaton return false
	for(int i = 0; i<numberStates; i++){
		if(states_[i].getName() == nameSt1 || states_[i].getName() == nameSt2){
			if(states_[i].getName() == nameSt1){
				temp1 = &states_[i];
				found1 = true;
			}else if(states_[i].getName() == nameSt2){
				temp2 = &states_[i];
				found2 = true;
			}else{
				cout << "There was a big mistake" << endl;
			}
		}
	}
	if(!found1 || !found2){
		return false;
	}
	
	if (numberTransitions != 0){
 		Transition* tempTrans = new Transition(temp1, temp2); 
		
		// If this transition between the two states already exists in the automaton return false.
		for(int i = 0; i < numberTransitions; i++){
			if(*tempTrans == transitions_[i]){
				return false;    
			}	  
		}
	  	
		// Allocate a new Transition and add to array
		Transition* temp = new Transition[numberTransitions];
		numberTransitions++;
		for(int i = 0; i<numberTransitions - 1; i++){
			temp[i] = transitions_[i];
		}
		delete [] transitions_;
		transitions_ = new Transition[numberTransitions];
		for(int i = 0; i < numberTransitions - 1; i++){
			transitions_[i] = temp[i];	  
		}		  
		transitions_[numberTransitions - 1] = *tempTrans;
		trans = tempTrans;

		// Garbage collect		  
		delete [] temp;

		// Update the source state
		temp1->addTransition(&transitions_[numberTransitions]);
		return true;
	} else {
		// In case the transitions_ array is empty
		Transition* t = new Transition(temp1, temp2);
		numberTransitions++;		
		transitions_ = new Transition [numberTransitions];
		transitions_[0] = *t;
		trans = t;
		
		// Update the source state
		temp1->addTransition(&transitions_[numberTransitions -1]);
		return true;
	}
	return false;
}

// Getter for a Transition defined by the name of its states
bool Automaton::getTransition(const std::string& nameSt1, const std::string& nameSt2,
		Transition*& trans)
{
	// implement me
	State* temp1 = nullptr;
	State* temp2 = nullptr;
	bool found1 = false, found2 = false;

	// If does not exist return false.
	for(int i = 0; i<numberStates; i++){
		if(states_[i].getName() == nameSt1 || states_[i].getName() == nameSt2){
			if(states_[i].getName() == nameSt1){
				temp1 = &states_[i];
				found1 = true;
			}else if(states_[i].getName() == nameSt2){
				temp2 = &states_[i];
				found2 = true;
			}else{
				cout << "There was a big mistake" << endl;
			}
		}
	}

	if(found1 == false || found2 == false){
		return false;
	}

	// Get transition
	Transition* tempTrans = new Transition(temp1,temp2);
	for(int i = 0; i<numberTransitions; i++){
		if(*tempTrans == transitions_[i]){
			Transition* anotherTrans = new Transition(transitions_[i]);
			trans = anotherTrans;
		}
	}
	return false;
}

// Getter for a Transition defined by its location in the array
bool Automaton::getTransition(int location,Transition*& trans) 
{
	// implement me
	// If the location is invalid return false.
	if(location >= numberTransitions){
		return false;
	}else{
		Transition* tempTrans = new Transition(transitions_[location]);
		trans = tempTrans;
		return true;
	}
}

// Getter for a Transition defined by its location in the array for const variables
bool Automaton::getTransition(int location,const Transition*& trans) const
{
	// implement me
	// If the location is invalid return false.
	if(location >= numberTransitions){
		return false;
	}else{
		Transition* tempTrans = new Transition(transitions_[location]);
		trans = tempTrans;
		return true;
	}
}

// Getter for the variables numberTransitions (size of the array transitions_)
int Automaton::numberOfTransitions() const
{
	// implement me
	return numberTransitions;
}


// Print method
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


// Copy operator
Automaton& Automaton::operator=(const Automaton& other)
{
	// implement me
	// Performs a shallow copy of other's variables
	name_ = other.name_;
	numberStates != other.numberStates;
	numberTransitions = other.numberTransitions;
	states_ = other.states_;
	transitions_ = other.transitions_;

}

// Move operator
Automaton& Automaton::operator=(Automaton&& other)
{
	// implement me
	// Copying all variables from other to this (automata)
	name_ = other.name_;
	numberStates != other.numberStates;
	numberTransitions = other.numberTransitions;
	states_ = other.states_;
	transitions_ = other.transitions_;

	// Nullifying all the variables from other
	other.name_ = "";
	other.numberStates = 0;
	other.numberTransitions = 0;
	other.states_ = nullptr;
	other.transitions_= nullptr;

}

// Equality operator
bool Automaton::operator==(const Automaton& other) const
{
	// implement me
	// If there are any discrepancies in the variables return false
	if (name_ != other.name_){return false;}
	if (numberStates != other.numberStates){return false;}
	if (numberTransitions != other.numberTransitions){return false;}

	// Loop through the states_ to find discrepancies
	for(int i=0; i<numberStates; i++){
		State tempState;
		tempState = other.states_[i];
		bool found = false;
		for(int j = 0; j < numberStates; j++){
			State tempState2;
			tempState2 = states_[i];
			if(tempState == tempState2){
				found = true;
			}
		}
		if(found == false){
			return false;
		}
	}
	
	// Loop through the transitions_ to find discrepancies
	for(int i=0; i<numberTransitions; i++){
		Transition tempTransition;
		tempTransition = other.transitions_[i];
		bool found = false;
		for(int j = 0; j < numberTransitions; j++){
			Transition tempTransition2;
			tempTransition2 = transitions_[i];
			if(tempTransition == tempTransition2){
				found = true;
			}
		}
		if(found == false){
			return false;
		}
	}

	return true;
}

// Inequality operator
bool Automaton::operator!=(const Automaton& other) const
{
	// implement me
	// If there are any similarities in the variables return false
	if (name_ == other.name_){return false;}
	if (numberStates == other.numberStates){return false;}
	if (numberTransitions == other.numberTransitions){return false;}
	
	// Loop through the states_ to find similarities
	for(int i=0; i<numberStates; i++){
		if(states_[i] == other.states_[i]){
			return false;
		}
	}

	// Loop through the transitions_ to find similarities
	for(int i=0; i< numberTransitions; i++){
		if(transitions_[i] == other.transitions_[i]){
			return false;
		}
	}
	return true;
}

std::ostream& operator<<(std::ostream& stream, const Automaton& aut)
{
	aut.print(stream);
	return stream;
}

