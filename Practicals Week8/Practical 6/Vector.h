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
 * Make your vector a template that can contain
 * any type of class
 */
template <class T>
class Vector {
public:
	// Initialize the vector to empty
	Vector();

	// Initialize the vector to have size many elements all of them equal val
	// If size is impossible then do whatever you want.
	Vector(int size,const T& val);

	// Copy constructor - implement deep copy
	Vector(const Vector<T>&);

	// Move constructor - implement move semantics
	Vector(Vector<T>&&);

	// Destructor - make sure to clean after yourself
	~Vector();

	// This used to be addElem. Return type changed as well
	// Add the given T as the last thing in the collection
	// If there is no more space return false
	// Otherwise return true
	void push_back(const T&);

	// This used to be getElem and setElem.
	// Return the element in the specified location
	// If the specified location does not exist in the vector
	// still try to access the memory location.
	// Notice that there are two different behaviors when the Vector is const and when it is
	// not const.
	const T& operator[](int) const;
	T& operator[](int);

	// Assignment operators with copy and move semantics
	Vector<T>& operator=(const Vector<T>&);
	Vector<T>& operator=(Vector<T>&&);

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
	// Use the width and fill values of the strem.
	template <class U>
	friend std::ostream& operator<<(std::ostream&, const Vector<U>&);

	// Read elements from the stream until end of file.
	// You should return a usable stream in this case.
	// If something goes wrong before end of file (e.g., 
	// something is not a U) then
	// you should stop reading, the vector should be unmodified,
	// and leave the stream corrupt.
	template <class U>
	friend std::istream& operator>>(std::istream&, Vector<U>&);
private:
	// TODO: complete me
};

#endif /* VECTOR_H_ */
