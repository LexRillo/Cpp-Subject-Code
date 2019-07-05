/*
 * Vector.h
 */

#ifndef VECTOR_H_
#define VECTOR_H_

/*
 * Incorporate dynamic memory and copy and move constructors
 * The vector now should modify its size to match the amount of elements it needs to fit.
 * Notice also that some function names are changed now to match common standards
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
private:
	// TODO: complete me
};

#endif /* VECTOR_H_ */
