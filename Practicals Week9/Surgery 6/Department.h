/*
 * Department.h
 */

#ifndef DEPARTMENT_H_
#define DEPARTMENT_H_

#include <iosfwd>
#include <vector>
#include <memory>
#include <map>
#include "Student.h"

class Department {
public:
	Department();
	Department(const Department& other);
	Department(Department&& other);

	~Department();

	void add(std::shared_ptr<Student>);
	unsigned int numOfStudents() const;

	std::shared_ptr<Student> getStudent(unsigned int i) const;

	friend std::ostream& operator<<(std::ostream& o, const Department&);

	Department& operator=(const Department& other);
	Department& operator=(Department&& other);
private:
	std::map<int,std::shared_ptr<Student>> students_;
};


// Things to do:
// 1. Create a student container with changing size (capacity + number)
// 2. Have a copy (and move) constructor and assignment.
// 3. Add functions such as
//    a. addStudent (from data which allocated)
//    b. addStudent (given ready student)
//    c. access the students

#endif /* DEPARTMENT_H_ */
