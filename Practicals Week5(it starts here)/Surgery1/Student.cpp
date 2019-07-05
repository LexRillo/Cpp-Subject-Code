
#include <string.h>
#include "Student.h"

/*
Student::Student()
  : id_(0)
{

  name_[0]=0;
  for (int i=0 ; i<NUMBEROFMODULES ; ++i) {
    modules_[i] = 0;
  }
  
}
*/

Student::Student(char* name, int id)
  : id_(id)
{
  // Copy only up to the existing length!
  // Copy the end-of-string symbol as well!
  int i=0;
  for ( ; 0!=name[i] && i<LENGTHOFNAME-1; ++i) {
    name_[i] = name[i];
  }
  name_[i]=0;

  for (int i=0 ; i<NUMBEROFMODULES ; ++i) {
    modules_[i] = 0;
  }
  
}

// There is nothing to do here!
// Destructor will become more important
// when we handle dynamic memory
Student::~Student() {
}

void Student::setName(char* name) {
  int i=0;
  for ( ; 0!=name[i] && i<LENGTHOFNAME-1; ++i) {
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

// An example showing that I can look into the private
// data member of another instance.
// Private keyword means that the PROGRAMMER of the class
// knows this.
// As the programmer, it is OK for me to look into the
// private data members of other instances
bool Student::sameName(const Student& other) const {
  for (unsigned int i=0 ; i<LENGTHOFNAME ; ++i) {
    if (name_[i] != other.name_[i]) {
      return false;
    }
  }
  return true;
}


