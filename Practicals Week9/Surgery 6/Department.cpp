/*
 * Department.cpp
 */

#include <iostream>
#include "Department.h"

using std::ostream;
using std::endl;
using std::make_pair;

Department::Department()
{
}

Department::Department(const Department& other)
: students_(other.students_)
{
}

Department::Department(Department&& other)
: students_(std::move(other.students_))
{
}

Department::~Department() {
}

void Department::add(std::shared_ptr<Student> s) {
	students_.insert(make_pair(s->id(),s));
}


unsigned int Department::numOfStudents() const
{
	return students_.size();
}

std::shared_ptr<Student> Department::getStudent(unsigned int id) const {
	auto i=students_.find(id);
	if (i == students_.end()) {
		return nullptr;
	}
	return i->second;
}

ostream& operator<<(ostream& o, const Department& d) {
	o <<"The students are:" << endl;
	unsigned int i=1;
	for (auto it=d.students_.begin() ; it != d.students_.end() ; ++it) {
		o << i++ << ")" << it->second->getName() << endl;
	}
	return o;
}

Department& Department::operator=(const Department& other) {
	students_ = other.students_;
	return *this;
}

Department& Department::operator=(Department&& other) {
	students_ = std::move(other.students_);
	return *this;
}

