/*
 * Priority.h
 *
 *  Created on: Nov 28, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */

#ifndef PRIORITY_H_
#define PRIORITY_H_

#include <iosfwd>

/*
 * This assignment practices the usage of STL.
 * The class is a simple version of priority queue.
 *
 * It's a container that accepts pointers to some type.
 * You are NOT in charge of the memory deallocation for these pointers.
 * With every pointers you get two priorities (integers).
 *
 * Then, one can request to get the most important item according
 * to priority 1 or according to priority 2.
 * Once an item has been asked for it is removed from the data.
 *
 * The easiest way to implement this (in my opinion) is to wrap
 * the functionality of std::multimap in a very light way.
 *
 * One sticky point that you have to notice is what happens when
 * there are multiple items with the same priority (hence the
 * multimap).
 */
template <class T>
class Priority {
public:

	enum Key { ONE, TWO };

	// Default constructor.
	// Initialize an empty priority queue
	Priority();

	// Copy and move constructors and assignment operators
	Priority(const Priority&);
	Priority(Priority&&);
	Priority& operator=(const Priority&);
	Priority& operator=(Priority&&);

	// Clean up
	~Priority();

	// Add an item to the queue
	// The first int is priority 1 and the second is priority 2
	// The pointer should be added to the queue
	// The memory behind the pointer is not your responsibility!
	void push_back(T *,int, int);

	// Pop an item from the queue.
	// If the key is ONE then the item with minimal
	// priority according to the first priority should be popped.
	// If the key is TWO then the item with minimal
	// priority according to the second priority should be popped.
	//
	// If the queue is empty return the nullptr
	T* pop_front(Key);

	// Iterate over the elements in the queue according to either
	// the first priority or the second priority
	class iterator {
	public:
		// This is required to allow Priority to access
		// the private members of the iterator
		friend class Priority;
		// Create an uninitialized iterator
		iterator();

		// Copy constructor and assignment operator
		iterator(const iterator&);
		iterator& operator=(const iterator&);

		// Access operators
		T& operator*();
		T* operator->();

		// Increment the iterator
		// pre-increment
		iterator& operator++();
		// post-increment
		iterator operator++(int);

		// Check if two iterators are the same or not
		bool operator==(const iterator&) const;
		bool operator!=(const iterator&) const;
	private:
		// Add private members
	};

	// Return an iterator that is going to work according
	// to first priority or second priority based on the key
	iterator begin(Key k);
	// Return an end marker for the iterator that works
	// according to the first priority or the second
	iterator end(Key k);

private:
	// add private members
};

template<class T>
Priority<T>::Priority()
{
	// implement me
}

template<class T>
Priority<T>::Priority(const Priority& other)
{
	// implement me
}

template<class T>
Priority<T>::Priority(Priority&& other)
{
	// implement me
}

template<class T>
Priority<T>& Priority<T>::operator=(const Priority<T>& other)
{
	// implement me
}

template<class T>
Priority<T>& Priority<T>::operator=(Priority<T>&&other)
{
	// implement me
}

template<class T>
Priority<T>::~Priority()
{
	// implement me
}

template<class T>
void Priority<T>::push_back(T *val,int key1, int key2)
{
	// implement me
}

template<class T>
T* Priority<T>::pop_front(Key k)
{
	// implement me
	return nullptr;
}

template<class T>
Priority<T>::iterator::iterator()
{
	// implement me
}

template<class T>
Priority<T>::iterator::iterator(const Priority<T>::iterator& other)
{
	// implement me
}

template<class T>
typename Priority<T>::iterator& Priority<T>::iterator::operator=(const Priority<T>::iterator& other)
{
	// implement me
}

template<class T>
T& Priority<T>::iterator::operator*()
{
	T removeMe;
	// implement me
	return removeMe;
}

template<class T>
T* Priority<T>::iterator::operator->()
{
	// implement me
	return nullptr;
}

template<class T>
typename Priority<T>::iterator& Priority<T>::iterator::operator++()
{
	iterator removeMe;
	// implement me
	return removeMe;
}

template<class T>
typename Priority<T>::iterator Priority<T>::iterator::operator++(int)
{
	iterator removeMe;
	// implement me
	return removeMe;
}

template<class T>
bool Priority<T>::iterator::operator==(const Priority<T>::iterator& other) const
{
	// implement me
	return false;
}

template<class T>
bool Priority<T>::iterator::operator!=(const Priority<T>::iterator& other) const
{
	// implement me
	return false;
}

template<class T>
typename Priority<T>::iterator Priority<T>::begin(Key k)
{
	iterator removeMe;
	// implement me
	return removeMe;
}

template<class T>
typename Priority<T>::iterator Priority<T>::end(Key k)
{
	iterator removeMe;
	// implement me
	return removeMe;
}

#endif
/*
 * Priority.h
 *
 *  Created on: Nov 28, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */
