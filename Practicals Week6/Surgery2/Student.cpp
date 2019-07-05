
#include <string.h>
#include "Student.h"

Student::Student(const char* name, int id)
: name_(nullptr), nameLength_(0), id_(id)
{
	int length = 0;
	for ( ; 0 != name[length] ; ++length);

	name_ = new char[length+1];
	// Copy only up to the existing length!
	// Copy the end-of-string symbol as well!
	int i=0;
	for ( ; 0!=name[i] ; ++i) {
		name_[i] = name[i];
	}
	name_[i]=0;
	nameLength_=i;

	for (int i=0 ; i<NUMBEROFMODULES ; ++i) {
		modules_[i] = 0;
	}

}

Student::Student(const Student& other)
: name_(nullptr), nameLength_(other.nameLength_), id_(other.id_)
{
	name_ = new char[nameLength_+1];
	// Copy only up to the existing length!
	// Copy the end-of-string symbol as well!
	int i=0;
	for ( ; 0!=other.name_[i] ; ++i) {
		name_[i] = other.name_[i];
	}
	name_[i]=0;

	for (int i=0 ; i<NUMBEROFMODULES ; ++i) {
		modules_[i] = other.modules_[i];
	}
}

Student::Student(Student&& other)
: name_(other.name_), nameLength_(other.nameLength_), id_(other.id_)
{
	other.name_ = nullptr;
	other.nameLength_ = 0;

   for (int i=0 ; i<NUMBEROFMODULES ; ++i) {
		modules_[i] = other.modules_[i];
	}
}



Student::~Student() {
	if (nameLength_) {
		delete [] name_;
	}
}

void Student::setName(const char* name) {
	int length = 0;
	for ( ; name[length] ; ++length);

	if (length > nameLength_) {
		delete [] name_;
		name_ = new char[length + 1];
	}
	// I moved this line outside the if
	// Notice that this creates a situation where
	// potentially, I don't know the actual
	// size of the memory that I am holding.
	// In practical terms, this may mean that
	// I have to reallocate memory in a case
	// that I actually have enough memory.
	// The other solution would have been to
	// have a field length and name length
	// variables.
	nameLength_ = length;

	int i=0;
	for ( ; 0!=name[i]; ++i) {
		name_[i] = name[i];
	}
	name_[i]=0;
}

void Student::getName(char* name) const {
	// Notice that hear I am relying on an invariant
	// I know that the name will have an end-of-string character
	// within the first LENGTHOFNAME characters
	int i=0;
	for ( ; 0!=name_[i]; ++i) {
		name[i] = name_[i];
	}
	name[i]=0;
}

int Student::nameLength() const {
	return nameLength_;
}

int Student::id() const {
	return id_;
}

bool Student::registerModule(int module) {
	// Check that the input is valid (not 0)
	if (!module) {
		return false;
	}

	// Find a location in the modules array to put this module
	int empty=-1;
	for (unsigned int i=0 ; i < NUMBEROFMODULES ; ++i) {
		// If module already exists no point in adding it
		if (modules_[i]==module) {
			return false;
		}
		// Found a place to put this module
		if (!modules_[i] && empty<0) {
			// This is the right way to convert an unsigned int
			// to an int.
			// I am declaring: I know what I am doing, I didn't
			// just forget that i is an unsigned int and empty is an int.
			empty = static_cast<int>(i);
		}
	}

	// Insert the module into the array
	if (empty >= 0) {
		modules_[empty] = module;
		return true;
	}
	return false;
}

bool Student::isRegistered(int module) const {
	for (unsigned int i=0 ; i<NUMBEROFMODULES ; ++i) {
		if (modules_[i]==module) {
			return true;
		}
	}
	return false;
}

// Updated this functions to use the nameLength
bool Student::sameName(const Student& other) const {
	if (nameLength_ != other.nameLength_) {
		return false;
	}
	for (int i=0 ; i<nameLength_ ; ++i) {
		if (name_[i] != other.name_[i]) {
			return false;
		}
	}
	return true;
}

Student& Student::operator=(const Student& other) {
	// Notice that I am not checking if this!=&other.
	// The reason not to do that is that in case that
	// this=&other no change will occur.
	// This is considered more efficient to avoid this
	// if in all the cases that this operator= is
	// called on different objects.

	if (nameLength_ < other.nameLength_) {
		delete [] name_;
		name_ = new char[other.nameLength_+1];
	}
	nameLength_ = other.nameLength_;
	for (int i=0 ; i<nameLength_ ; ++i) {
		name_[i] = other.name_[i];
	}
	name_[nameLength_]=0;

	id_ = other.id_;
	for (int i=0 ; i<NUMBEROFMODULES ; ++i) {
		modules_[i] = other.modules_[i];
	}

	return *this;
}

Student& Student::operator=(Student&& other) {
	char* tempc = other.name_;
	other.name_ = name_;
	name_ = tempc;

	int tempi = other.nameLength_;
	other.nameLength_ = nameLength_;
	nameLength_ = tempi;

	id_ = other.id_;
	for (int i=0 ; i<NUMBEROFMODULES ; ++i) {
		modules_[i] = other.modules_[i];
	}

	return *this;
}
