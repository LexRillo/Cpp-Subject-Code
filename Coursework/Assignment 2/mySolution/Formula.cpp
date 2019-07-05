/*
 * Formula.cpp
 *
 *  Created on: Oct 30, 2017
 *      Author: np183
 *      Module: CO7105
 *      Department of Informatics
 *      University of Leicester
 */
#include <string>
#include <iostream>
#include"Formula.h"

using std::ostream;
using std::string;

Formula::Formula()
{
}

Formula::~Formula()
{
}

// This method is virtual. It is implemented in the derived classes
bool Formula::valid() const
{
	return false;
}

// This method is virtual. It is implemented in the derived classes
bool Formula::evaluate(const Assignment&) const
{
	return false;
}

// This method is virtual. It is implemented in the derived classes
void Formula::print(ostream& stream) const
{
}

string Formula::name() const
{
	// Return the name variable
	return name_;
}

// This method is virtual. It is implemented in the derived classes
Formula* Formula::copy() const
{
	return nullptr;
}

// This method is virtual. It is implemented in the derived classes
Formula* Formula::negate() const
{
	return nullptr;
}

// Constructor of Constant
Constant::Constant(bool value)
{
	// If the value is true then the name is T. If the value is false the name is F.
	if(value){
		name_ = "T";
	}else{
		name_ = "F";
	}
}

// Validation method
bool Constant::valid() const{
	// Constant is always valid unless it's nullptr
	if(this != nullptr){
		return true;
	}
	return false;
}

// Returns the boolean value of the constant
bool Constant::evaluate(const Assignment& assignment) const{
	// Regressing from the operation done in the constructor
	// T -> true // F-> false
	if(name() == "T"){
		return true;
	}else{
		return false;
	}
}

// Copies the constant
Formula* Constant::copy() const
{
	Formula* thiscopy = nullptr;
	// Initializing the pointer to a Costant of the same boolan value
	if(name() == "T"){		
		thiscopy = new Constant(true);
	}else{
		thiscopy = new Constant(false);
	}
	return thiscopy;
}

// Copies the complement of constant
Formula* Constant::negate() const
{
	Formula* thisnegate = nullptr;
	// Initializing the pointer to a Costant of the opposite boolan value
	if(name() == "T"){
		thisnegate = new Constant(false);
	}else{
		thisnegate = new Constant(true);
	}
	return thisnegate;
}

// Prints constant
void Constant::print(ostream& stream) const
{
	if(name() == "T"){
		stream << "T";
	}else{
		stream << "F";
	}
}

// Destructor of Constant
Constant::~Constant()
{
}

// Constructor of Variable
Variable::Variable(const string& name)
{
	name_=name;
}

// Validation method
bool Variable::valid() const{
	// Variable needs to be different from nullpointer and have a name that is not blank
	if(this == nullptr && name_ == ""){
		return false;
	}
	return true;
}

// Returns the boolean value of the variable
bool Variable::evaluate(const Assignment& assignment) const{
	// Using the assignment in the argument, it allows the deduction of the boolean value of the variable
	if(assignment.operator()(name_)){
		return true;
	}else{
		return false;
	}
}

// Copies the variable
Formula* Variable::copy() const
{
	Formula* thiscopy = nullptr;
	thiscopy = new Variable(name());
	return thiscopy;
}

// Copies the variable and applies it to a Not boolean operator to negate it
Formula* Variable::negate() const
{
	Formula* thisnegate = nullptr;
	thisnegate = new Not(this->copy());
	return thisnegate;
}

// Prints the variable
void Variable::print(ostream& stream) const
{
	stream << name();
}

// Destructor of Variable
Variable::~Variable()
{
	// implement me
}

// Constructor of BinaryOperator
BinaryOperator::BinaryOperator(Formula* left, Formula* right) 
{
}

// Destructor of BinaryOperator
BinaryOperator::~BinaryOperator()
{
}

// Constructor of UnaryOperator
UnaryOperator::UnaryOperator(Formula* operand)
{
}

// Destructor of UnaryOperator
UnaryOperator::~UnaryOperator()
{
}

// Constructor of And
And::And(Formula* left,Formula* right)
  : BinaryOperator(left,right)
{
	name_ = "and";
	left_ = left;
	right_ = right;
}

// Validation method
bool And::valid() const{
	// An And operator is valid only if its not null and its operands are valid and not nullptr
	if(this != nullptr && left_ != nullptr && right_ != nullptr && left_->valid() && right_->valid()){
		return true;
	}else{
		return false;
	}
}

// Returns the boolean value of the whole operation
bool And::evaluate(const Assignment& assignment) const{
	// If both operands are true then returns true
	if(left_->evaluate(assignment) && right_->evaluate(assignment)){
		return true;
	}else{
		return false;
	}
}

// Copies the whole operation
Formula* And::copy() const
{
	// Makes a copy of the operation and calls the copy methods of the operands
	Formula* thiscopy = nullptr;
	thiscopy = new And(left_->copy(), right_->copy());
	return thiscopy;
}

// Copies the complement of the And operation
Formula* And::negate() const
{
	// Initializes an Or operation and calls the negate methods of the operands
	Formula* thisnegate = nullptr;
	thisnegate = new Or(left_->negate(), right_->negate());
	return thisnegate;
}

// Prints the whole operation
void And::print(ostream& stream) const
{
	stream << "(";
	left_->print(stream);
	stream << " and ";
	right_->print(stream);
	stream << ")";
}

// Destructor of And
And::~And()
{
}

// Constructor of Or
Or::Or(Formula* left, Formula* right)
  : BinaryOperator(left,right)
{
	name_ = "or";
	left_ = left;
	right_ = right;
}

// Validation method
bool Or::valid() const
{
	if(this != nullptr && left_ != nullptr && right_ != nullptr && left_->valid() && right_->valid()){
		return true;
	}else{
		return false;
	}
}

// Returns the boolean value of the whole operation
bool Or::evaluate(const Assignment& assignment) const
{
	// If one of the operands are true then returns true
	if(left_->evaluate(assignment) || right_->evaluate(assignment)){
		return true;
	}else{
		return false;
	}
}

// Copies the whole operation
Formula* Or::copy() const
{
	// Initializes an Or operation and calls the negate methods of the operands
	Formula* thiscopy = nullptr;
	thiscopy = new Or(left_->copy(), right_->copy());
	return thiscopy;
}

// Copies the complement of the Or operation
Formula* Or::negate() const
{
	// Initializes an And operation and calls the negate methods of the operands
	Formula* thisnegate = nullptr;
	thisnegate = new And(left_->negate(), right_->negate());
	return thisnegate;
}

// Prints the whole operation
void Or::print(ostream& stream) const
{
	stream << "(";
	left_->print(stream);
	stream << " or ";
	right_->print(stream);
	stream << ")";
}

// Destructor of Or
Or::~Or()
{
}

// Constructor of Not
Not::Not(Formula* operand)
  : UnaryOperator(operand)
{
	name_ = "not";
	member_ = operand;
}

// Validation method
bool Not::valid() const{
	if(this != nullptr && member_ != nullptr && member_->valid()){
		return true;
	}else{
		return false;
	}
}

// Returns the boolean value of the Not operation
bool Not::evaluate(const Assignment& assignment) const{
	// Evaluates the value of the operand and returns the oposite
	return !(member_->evaluate(assignment));
}

// Copies the Not operation
Formula* Not::copy() const
{
	Formula* thiscopy = nullptr;
	thiscopy = new Not(member_->copy());
	return thiscopy;
}

// Negating a Not. How amusing!
Formula* Not::negate() const
{
	return member_;
}

// Prints the Not operation
void Not::print(ostream& stream) const
{
	stream << "(not ";
	member_->print(stream);
	stream << ")";
}

// Destructor of Not
Not::~Not()
{
}
