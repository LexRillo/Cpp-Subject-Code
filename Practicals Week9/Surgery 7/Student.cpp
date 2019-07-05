
#include <string.h>
#include "Student.h"

using std::string;
using std::vector;

std::function<string(const Student&)> Student::basicToStringer = [](const Student& s) -> string {
	  return s.getName();
};

Student::Student(const string& name, int id)
: name_(name), id_(id)
{
}

Student::Student(const Student& other)
: name_(other.name_), id_(other.id_), modules_(other.modules_)
{
}

Student::Student(Student&& other)
: name_(std::move(other.name_)), id_(other.id_), modules_(std::move(other.modules_))
{
}

Student::~Student() {
}

void Student::setName(const string& name) {
	name_ = name;
}

string Student::getName() const {
	return name_;
}

int Student::id() const {
	return id_;
}

bool Student::registerModule(int module) {
	// Check that the input is valid (not 0)
	if (!module) {
		return false;
	}

	for (auto i=modules_.begin() ;
			i != modules_.end();
			++i) {
		if (*i==module) {
			return false;
		}
	}
	modules_.push_back(module);
	return true;
}

bool Student::isRegistered(int module) const {
	if (modules_.size() > NUMBEROFMODULES) {
		return false;
	}

	for (unsigned int i=0 ; i<modules_.size() ; ++i) {
		if (modules_[i]==module) {
			return true;
		}
	}
	return false;
}

Student& Student::operator=(const Student& other) {
	name_ = other.name_;
	id_ = other.id_;
	modules_ = other.modules_;
	return *this;
}

	Student& Student::operator=(Student&& other) {
	name_ = std::move(other.name_);
	id_ = other.id_;
	modules_ = other.modules_;
	return *this;
}
