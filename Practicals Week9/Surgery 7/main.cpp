#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <vector>
#include "Student.h"
#include "Department.h"


using std::cout;
using std::endl;
using std::vector;
using std::ostream;
using std::stringstream;
using std::for_each;

// template <typename S,typename T>
int main() {
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
		other_d.add(std::shared_ptr<Student>(new Student("Yet another student",3483498)));

		other_d = dcopy;

		// Define lambda functions that register a student to modules given in a
		// vector
		auto registerModules = [](Student& s,vector<int> modules) {
			for (auto module : modules) {
				s.registerModule(module);
			}
		};


		vector<int> modules={3015,3204,3304,3605};

		// Register all students in the department to the
		// modules in the vector
		for_each(other_d.begin() , other_d.end() , [&](Student& s) {
			registerModules(s,modules);
		});

		// output the department with normal toString;
		cout << other_d.toString();

		// Prepare a specialized toString method with a lambda function
		auto withModules = [](const Student& s) {
			stringstream t;
			t << s.getName() << " (";
			bool first = true;
			for (unsigned int i=3000 ; i<4000; ++i) {
				if (s.isRegistered(i)) {
					if (!first) {
						t << " ";
					}
					first = false;
					t << i;
				}
			}
			t << ")";
			return t.str();
		};
		cout << other_d.toString(withModules);
	}
	return 0;
}

