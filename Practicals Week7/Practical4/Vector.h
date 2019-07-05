/*
 * Vector.h
 *
 *  Created on: 15 Oct 2014
 *      Author: np183
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <string>
#include <iosfwd>
/*
 * Add toString, operator<<, and operator>> for reading
 * Vectors
 */
class Vector {
public:
	// Initialize the vector to empty
	Vector();

	// Initialize the vector to have size many elements all of them equal val
	// If size is impossible then do whatever you want.
	Vector(int size,int val=0);

	// Copy constructor - implement deep copy
	Vector(const Vector&);

	// Move constructor - implement move semantics
	Vector(Vector&&);

	// Destructor - make sure to clean after yourself
	~Vector();

	// This used to be addElem. Return type changed as well
	// Add the given integer as the last thing in the collection
	// If there is no more space return false
	// Otherwise return true
	void push_back(int);

	// This used to be getElem and setElem.
	// Return the element in the specified location
	// If the specified location does not exist in the vector
	// still try to access the memory location.
	// Notice that there are two different behaviors when the Vector is const and when it is
	// not const.
	int operator[](int) const;
	int& operator[](int);

	// Assignment operators with copy and move semantics
	Vector& operator=(const Vector&);
	Vector& operator=(Vector&&);

	// Return the number of elements in the collection.
	int size() const;
	bool empty() const;

	// Initizlie the collection to be empty
	void clear();

	// return a string with all the contents of the vector.
	// If the width is 0 - just add all the elements
	//                     on one line
	// If the width is non zero - 
	// print as many values as possible with at most width
	// characters per line.
	// If one entry is more than the required width, then just
	// add that entry to the line and that's it.
	// The fill character should be used for separating 
	// the entries in the vector.
	std::string toString(unsigned int width=0, char fill=' ') const;

	// Similar to toString.
	// Use the width and fill values of the stream.
	friend std::ostream& operator<<(std::ostream&, const Vector&);

	// Read elements from the stream until end of file.
	// You should return a usable stream in this case.
	// If something goes wrong before end of file (e.g., 
	// something is not an integer) then
	// you should stop reading, the vector should be unmodified,
	// and leave the stream corrupt.
	friend std::istream& operator>>(std::istream&, Vector&);
private:
	// TODO: implement me
};

#endif /* VECTOR_H_ */
