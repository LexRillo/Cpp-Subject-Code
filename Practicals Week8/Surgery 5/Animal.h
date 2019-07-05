/*
 * Animal.h
 *
 *  Created on: 21 Nov 2014
 *      Author: np183
 */

#ifndef ANIMAL_H_
#define ANIMAL_H_

#include <string>

class Animal {
public:
	Animal();
	virtual ~Animal();

	virtual std::string name() const;
	void description() const;
protected:
	std::string name_;
};

class TwoLegs : public Animal {
public:
	TwoLegs() = delete;
	TwoLegs(char left,char right);
	~TwoLegs() override;

	std::string walk() const;
protected:
	char left_;
	char right_;
};


class Bird : public TwoLegs {
public:
	Bird();
	~Bird() override;
	std::string walk() const;
	std::string sound() const;

//private:
};

class Falcon : public Bird {
public:
	Falcon();
	~Falcon() override;

	std::string name() const override;
	
};

class Penguin : public Bird {
public:
	Penguin();
	~Penguin() override;

	std::string name() const override;
};

#endif /* ANIMAL_H_ */
