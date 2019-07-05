/*
 * LinkedList.h
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iosfwd>
#include <string>

/*
 * Make your linked list a template that can contain
 * any type of class
 */
template <class T>
class LinkedList {
public:
	// Initialize the linkedlist to empty
	LinkedList();

	// Copy constructor - implement deep copy
	LinkedList(const LinkedList<T>&);

	// Move constructor - implement move semantics
	LinkedList(LinkedList<T>&&);

	// Destructor - make sure to clean after yourself
	~LinkedList();

	// Add an element at the front or at the back
	void push_back(const T&);
	void push_front(const T&);

	// Remove the first/last element.
	// If the list is empty do nothing.
	void pop_back();
	void pop_front();

	// Return the first/last element
	const T& first() const;
	const T& last() const;

	// Assignment operators with copy and move semantics
	LinkedList<T>& operator=(const LinkedList<T>&);
	LinkedList<T>& operator=(LinkedList<T>&&);

	// Return the number of elements in the collection.
	int size() const;
	bool empty() const;

	// Initizlie the collection to be empty
	void clear();


	// return a string with all the contents of the LinkedList.
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
	template<class U>
	friend std::ostream& operator<<(std::ostream&, const LinkedList<U>&);

	// Read elements from the stream until end of file.
	// You should return a usable stream in this case.
	// If something goes wrong before end of file (e.g., 
	// something is not a U) then
	// you should stop reading, the linked list should be unmodified,
	// and leave the stream corrupt.
	template<class U>
	friend std::istream& operator>>(std::istream&, LinkedList<U>&);
private:
	struct LNode {
		T data_;
		LNode* next_;
		LNode* prev_;
	};

	// TODO: Complete me
};

#endif /* LinkedList_H_ */
