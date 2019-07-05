#include <iostream>
#include "Student.h"
#include "Department.h"


using std::cout;
using std::endl;

int main() {
	if (false) {
		Student s("my name",5);
		s.registerModule(5);
		if (s.isRegistered(5)) {
			cout << "yes" << endl;
		}
	}

	if (false) {
		// Create a few students (perhaps with long names ???)

		Student s2("Eric",5);
		Student s3("A student with a very very very very very very very very very asldkfjas;ldkfjasdklfasdkljf long name",345);

		// Print them
		cout << s2.getName() << endl;
		cout << s3.getName() << endl;

		Student s4(s2);

		cout << s4.getName() << endl;

		s4.setName("Short name");

		cout << s2.getName() << endl;
		cout << s4.getName() << endl;

		// testing a bit the copy operator
		s3 = s2;
		cout << s3.getName() << endl;

		s3.setName("Something Longer than Eric");

		cout << s2.getName() << endl;
		cout << s3.getName() << endl;
	}

	if (true) {
		Department d;
		cout << d.numOfStudents() << endl;

		std::shared_ptr<Student> p(new Student("First student to be destroyed by other_d",34));
		d.add(p);

		Department other_d(std::move(d));

		other_d.add(std::shared_ptr<Student>(new Student("blah",5)));
		other_d.add(std::shared_ptr<Student>(new Student("A student with a very very very very very very very very very asldkfjas;ldkfjasdklfasdkljf long name",345)));
		other_d.add(std::shared_ptr<Student>(new Student("Eric",7)));

		// Exercise the copy constructor
		Department dcopy(other_d);
		cout << "This should be a department with 4 students" << endl;
		cout << dcopy;

		// Change d
		other_d.add(std::shared_ptr<Student>(new Student("Yet another student",3483498)));
		cout << "This should be a department with 5 students" << endl;
		cout << other_d;

		// Exercise the deep copy assignment operator
		other_d = dcopy;
		cout << "This should be a department with 4 students again" << endl;
		cout << other_d;
	}
	return 0;
}


// Things to do:
// 1. See that the Student is working with the new dynamic memory
// 2. Add a department and add student to it
// 3. Print a department
