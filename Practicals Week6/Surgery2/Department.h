/*
 * Department.h
 */

#ifndef DEPARTMENT_H_
#define DEPARTMENT_H_

#include <iosfwd>
#include "Student.h"

class Department {
public:
	Department();
	Department(const Department& other);
	Department(Department&& other);

	~Department();

	void add(const char* name, unsigned int id);
	unsigned int numOfStudents() const;

	Student* getStudent(unsigned int i) const;

	void output(std::ostream& o) const;

	Department& operator=(const Department& other);
	Department& operator=(Department&& other);
private:
	unsigned int size_;
	unsigned int used_;
	Student** students_;
};


// Things to do:
// 1. Create a student container with changing size (capacity + number)
// 2. Have a copy (and move) constructor and assignment.
// 3. Add functions such as
//    a. addStudent (from data which allocated)
//    b. addStudent (given ready student)
//    c. access the students

#endif /* DEPARTMENT_H_ */
