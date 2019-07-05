/*
 * Student.h
 *
 */

#ifndef STUDENT_H_
#define STUDENT_H_

const int NUMBEROFMODULES=9;

class Student {
public:
  Student() = delete;
  Student(const char* name, int id);
  Student(const Student&);
  Student(Student&&);

  ~Student();

  
  void setName(const char*);
  void getName(char*) const;

  // Added a nameLength function and returned the nameLength data
  // member to be private
  int nameLength() const;

  int id() const;

  bool registerModule(int); // This is not const! Changing the student
  bool isRegistered(int) const;
  
  bool sameName(const Student& other) const;

  // Implemented these two
  Student& operator=(const Student&);
  Student& operator=(Student&&);
 private:
  char* name_;
  int nameLength_;
  int id_;
  int modules_[NUMBEROFMODULES];
};

#endif /* STUDENT_H_ */

// Things to do:
// 1. Remove the fixed namelength of student using dynamic memory
// 2. Add copy constructor
// 3. Move to department
