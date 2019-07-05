/*
 * Student.h
 *
 */

#ifndef STUDENT_H_
#define STUDENT_H_

const int NUMBEROFMODULES=9;
const int LENGTHOFNAME=30;

class Student {
public:
  // Once a non-default constructor is added I want
  // to explicitly forbid the creation of a student
  // without a name and an ID
  // So I add the delete instruction.
  // Whoever reads the header file will notice that there is no
  // default constructor
  Student() = delete;
  Student(char* name, int id);

  // Destructor!
  ~Student();
  
  void setName(char*);
  void getName(char*) const;

  int id() const;

  bool registerModule(int); // This is not const! Changing the student
  bool isRegistered(int) const;
  
  bool sameName(const Student& other) const;
 private:
  char name_[LENGTHOFNAME];
  int id_;
  int modules_[NUMBEROFMODULES];
};

#endif /* STUDENT_H_ */


// Things to do:
// A student should have a:
// 1. Name - character array of a given length
// 2. Student id
// 3. Array of modules
//
// Supported functionalities:
// Construct a student with name and ID.
// It doesn't make sense to change the name of the student or the ID.
// It doesn't make sense to construct an empty student.
//
// Other functionalities:
// 1. name()
// 2. id()
// 3. registerModule()
// 4. isRegistered()
//
// Further points:
// 1. Constants
// 2. Delete members
// 3. Naming convention
// 4. Explain that private parts of other students are accessible
