#include <iostream>
#include "Student.h"


using std::cout;
using std::endl;

// Create a function that prints the student's name
void printStudentName(const Student& s) {
  // Notice that by putting my constants in the global scope of
  // Student.h users can use this constant!
  // If you want to avoid this or make it more ordered
  // you should define them inside the class.
  // Then they will be Student::CONSTANTNAME or as private
  // variables.
  char buffer[LENGTHOFNAME];
  s.getName(buffer);
  cout << "The student's name is: " << buffer << endl;
}


int main() {
  // Create a few students (perhaps with long names ???)
  
  Student s2("Eric",5);
  Student s3("A student with a very very very very very very very very very asldkfjas;ldkfjasdklfasdkljf long name",345);
  
  // Print them
  printStudentName(s2);
  printStudentName(s3);
  
  // Register them to some modules
  if (s3.registerModule(7105)) {
    cout << "Successfully registered to 7105" << endl;
  }
  else {
    cout << "Failed to register to 7105" << endl;
  }
  if (s3.registerModule(7105)) {
    cout << "Successfully registered to 7105" << endl;
  }
  else {
    cout << "Failed to register to 7105" << endl;
  }
  
  // Check their registartion and output something
  // Do something with student id
  if (s3.isRegistered(7105)) {
    cout << "Registered" << endl;
  }
  else {
    cout << "Not registered" << endl;
  }
  
  return 0;
}
