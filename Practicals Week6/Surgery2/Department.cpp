/*
 * Department.cpp
 */

#include <iostream>
#include "Department.h"

using std::ostream;
using std::endl;

constexpr unsigned int INITIALSIZE=10;
constexpr unsigned int SIZEMULTIPLY=2;


Department::Department()
: size_(INITIALSIZE),used_(0), students_(new Student*[INITIALSIZE])
{
}

Department::Department(const Department& other)
: size_(other.size_), used_(other.used_),
  students_(new Student*[size_])
{
	for (unsigned int i=0 ; i<used_ ; ++i) {
		students_[i] = new Student(*(other.students_[i]));
	}
}

Department::Department(Department&& other)
: size_(other.size_), used_(other.used_),
  students_(other.students_)
{
	other.used_ = 0;
	other.size_ = 0;
	other.students_ = nullptr;
}

Department::~Department() {
	for (unsigned int i=0 ; i<used_ ; ++i) {
		delete students_[i];
	}
	if (students_) {
		delete [] students_;
	}
}

// Implemented this function
void Department::add(const char* name, unsigned int id)
{
	// If I need more space: reallocate, copy, and delete
	// old memory
	if (used_ >= size_) {
		size_ = std::max(INITIALSIZE,SIZEMULTIPLY*size_);
		Student** temp = new Student*[size_];
		for (unsigned int i=0 ; i<used_ ; ++i) {
			temp[i] = students_[i];
		}
		delete [] students_;
		students_ = temp;
	}
	students_[used_++] = new Student(name,id);
}

unsigned int Department::numOfStudents() const
{
	return used_;
}

Student* Department::getStudent(unsigned int i) const {
	if (i < used_) {
		return students_[i];
	}
	return nullptr;
}

void Department::output(ostream& o) const {
	o << "The students are:" << endl;
	for (unsigned int i=0 ; i<used_ ; ++i) {
		char buffer[students_[i]->nameLength()+1];
		students_[i]->getName(buffer);
		o << i+1 << ")" << buffer << endl;
	}
}

Department& Department::operator=(const Department& other) {
	// As I am deleting the students of this department
	// I have to be sure that I am not copying onto myself.
	if (this != &other) {
		for (unsigned int i=0 ; i<used_ ; ++i) {
			delete students_[i];
		}
		if (size_ < other.used_) {
			delete [] students_;
			students_ = new Student*[other.size_];
			size_ = other.size_;
		}
		used_ = other.used_;
		for (unsigned int i=0 ; i<used_ ; ++i) {
			students_[i] = new Student(*(other.students_[i]));
		}
	}
	return *this;
}

Department& Department::operator=(Department&& other) {
	Student** tempp = other.students_;
	other.students_ = students_;
	students_ = tempp;

	unsigned int tempi = other.size_;
	other.size_ = size_;
	size_ = tempi;

	tempi = other.used_;
	other.used_ = used_;
	used_ = tempi;

	return *this;
}

