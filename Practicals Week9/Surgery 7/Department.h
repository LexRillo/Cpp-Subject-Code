/*
 * Department.h
 */

#ifndef DEPARTMENT_H_
#define DEPARTMENT_H_

#include <iosfwd>
#include <vector>
#include <memory>
#include <functional>
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

	class iterator {
	public:
		friend class Department;
		iterator() {}
		iterator(const iterator& other) { it_ = other.it_; }

		iterator& operator++() { ++it_; return *this; }
		iterator operator++(int) { iterator oit = *this; ++it_; return oit; }

		bool operator==(const iterator& other) { return other.it_ == it_; }
		bool operator!=(const iterator& other) { return other.it_ != it_; }

		std::shared_ptr<Student> operator->() { return it_->second; }
		Student& operator*() { return *(it_->second); }
	private:
		std::map<int,std::shared_ptr<Student>>::iterator it_;
	};

	iterator begin() { iterator it; it.it_ = students_.begin(); return it;  }
	iterator end() { iterator it; it.it_ = students_.end(); return it; }

	std::string toString(std::function<std::string(Student)> f=Student::basicToStringer) const;
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
