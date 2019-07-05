/*
 * Vector.h
 */

#ifndef VECTOR_H_
#define VECTOR_H_

/*
 * Change your container to include constructors.
 */
class Vector {
public:
	// At this point the vector has a fixed size of 100
	static constexpr int SIZE=100;

	// Initialize the vector to empty
	Vector();

	// Initialize the vector to have size many elements all of them equal val
	// If size is impossible then do whatever you want.
	Vector(int size,int val=0);

	// Add the given integer as the last thing in the collection
	// If there is no more space return false
	// Otherwise return true
	bool addElem(int);

	// Return the element in the specified location
	// If the specified location does not exist in the vector
	// behavior is undefined (can be anything)
	int getElem(int) const;

	// Set the specified location in the collection to the value
	// If the collection hasn't reached the size to support this location
	// return false.
	// Otherwise, set the location and return true.
	// That is, setElem cannot be used to increase the number of elements
	// in the collection.
	bool setElem(int loc,int val);

	// Return the number of elements in the collection.
	int size() const;

	// Initizlie the collection to be empty
	void clear();
private:
	// TODO: complete me
};

#endif /* VECTOR_H_ */
