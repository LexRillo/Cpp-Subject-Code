/*
 * Animal.cpp
 *
 *  Created on: 21 Nov 2014
 *      Author: np183
 */

#include "Animal.h"

# include <iostream>

using std::string;
using std::cout;
using std::endl;


Animal::Animal() : name_("Animal") {
}

Animal::~Animal() {
}

string Animal::name() const {
	return "I don't know my name";
}

void Animal::description() const {
	cout << "I am an " << name() << " I really don't exist." << endl;
}


TwoLegs::TwoLegs(char left,char right)
: left_(left), right_(right)
{
	name_ = "TwoLegs";
}

TwoLegs::~TwoLegs() {
}

string TwoLegs::walk() const {
	string temp(1,left_);
	temp += right_;
	return temp;
}

Bird::Bird()
: TwoLegs('<','>')
{
	name_ = "Bird";
}

Bird::~Bird() {
}

string Bird::walk() const {
	string temp(1,right_);
	temp += left_;
	return temp;
}

string Bird::sound() const {
	return "chirp";
}

Falcon::Falcon()
{
}

Falcon::~Falcon() {
}

string Falcon::name() const {
  return "Falcon";
}

Penguin::Penguin()
{
}

Penguin::~Penguin() {
}

string Penguin::name() const {
	return "Penguin";
}
