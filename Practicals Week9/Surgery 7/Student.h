/*
 * Student.h
 *
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <functional>
#include <vector>

const int NUMBEROFMODULES=9;

class Student;

class Student {
public:
  Student() = delete;
  Student(const std::string&, int id);
  Student(const Student&);
  Student(Student&&);

  ~Student();

  
  void setName(const std::string&);
  std::string getName() const;

  int id() const;

  bool registerModule(int); // This is not const! Changing the student
  bool isRegistered(int) const;
  
  // Implemented these two
  Student& operator=(const Student&);
  Student& operator=(Student&&);

  static std::function<std::string(const Student&)> basicToStringer;

private:
  std::string name_;
  int id_;
  std::vector<int> modules_;
};

#endif /* STUDENT_H_ */

// Things to do:
// 1. Remove the fixed namelength of student using dynamic memory
// 2. Add copy constructor
// 3. Move to department
