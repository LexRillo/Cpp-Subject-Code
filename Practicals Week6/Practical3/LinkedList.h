/*
 * LinkedList.h
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

/*
 * Create a container using a doubly linked list
 */
class LinkedList {
public:
	// Initialize the linkedlist to empty
	LinkedList();

	// Copy constructor - implement deep copy
	LinkedList(const LinkedList&);

	// Move constructor - implement move semantics
	LinkedList(LinkedList&&);

	// Destructor - make sure to clean after yourself
	~LinkedList();

	// Add an element at the front or at the back
	void push_back(int);
	void push_front(int);

	// Remove the first/last element.
	// If the list is empty do nothing.
	void pop_back();
	void pop_front();

	// Return the first/last element
	int first() const;
	int last() const;

	// Assignment operators with copy and move semantics
	LinkedList& operator=(const LinkedList&);
	LinkedList& operator=(LinkedList&&);

	// Return the number of elements in the collection.
	int size() const;
	bool empty() const;

	// Initizlie the collection to be empty
	void clear();
private:
	struct LNode {
		int data_;
		LNode* next_;
		LNode* prev_;
	};

	// TODO: complete me
};

#endif /* LinkedList_H_ */
