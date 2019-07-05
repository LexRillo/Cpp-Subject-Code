#include <iostream>
#include "Student.h"
#include "Department.h"


using std::cout;
using std::endl;

// Create a function that prints the student's name
void printStudentName(const Student& s) {
	// In order to make this safe I added a name_length function to student
	char buffer[s.nameLength()+1];
	s.getName(buffer);
	cout << "The student's name is: " << buffer << endl;
}

int main() {
	if (true) {
		// Create a few students (perhaps with long names ???)

		Student s2("Eric",5);
		Student s3("A student with a very very very very very very very very very asldkfjas;ldkfjasdklfasdkljf long name",345);

		// Print them
		printStudentName(s2);
		printStudentName(s3);

		Student s4(s2);
		printStudentName(s4);
		s4.setName("Short name");
		printStudentName(s2);
		printStudentName(s4);

		// testing a bit the copy operator
		s3 = s2;
		printStudentName(s3);
		s3.setName("Something Longer than Eric");
		printStudentName(s2);
		printStudentName(s3);



	}

	if (true) {
		Department d;
		cout << d.numOfStudents() << endl;

		d.add("First student to be destroyed by other_d",34);

		Department other_d(std::move(d));

		// Notice that here I'm doing something that shouldn't be done!
		// I'm using d again even though I declared above that I will not be doing
		// this!
		// I said that d will be destroyed and it's OK to scavenge it's memory.
		// But here I'm using it again.
		d.add("blah",5);
		d.add("A student with a very very very very very very very very very asldkfjas;ldkfjasdklfasdkljf long name",345);
		d.add("Eric",7);

		// Exercise the copy constructor
		Department dcopy(d);
		cout << "This should be a department with 3 students" << endl;
		dcopy.output(cout);

		cout << endl;

		// Change d
		d.add("Yet another student",3483498);
		cout << "This should be a department with 4 students" << endl;
		d.output(cout);

		cout << endl;

		// Exercise the deep copy assignment operator
		other_d = d;
		cout << "This should be a department with 4 students again" << endl;
		other_d.output(cout);

		cout << endl;

		// Exercise the move assignment operator
		d = dcopy;
		cout << "This should be a department with 3 students" << endl;
		d.output(cout);

		cout << endl;
	}

	return 0;
}


// Things to do:
// 1. See that the Student is working with the new dynamic memory
// 2. Add a department and add student to it
// 3. Print a department
