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
#include <map>

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
		typename std::multimap<int,T*>::iterator it_;
	};

	// Return an iterator that is going to work according
	// to first priority or second priority based on the key
	iterator begin(Key k);
	// Return an end marker for the iterator that works
	// according to the first priority or the second
	iterator end(Key k);

private:
	std::multimap<int,T*> map1_;
	std::multimap<int,T*> map2_;
	// completemap keeps a record of all the elements that have been pushed
	std::map<int,std::pair<std::pair<int,T*>,std::pair<int,T*>>> completemap;
	// pushesDone keeps track of the pushes that have been done overall. It is useful to identify elements on completemap
	int pushesDone = 0;
};

// constructor
template<class T>
Priority<T>::Priority()
{
}

// copy constructor
template<class T>
Priority<T>::Priority(const Priority& other)
{
	map1_ = other.map1_;
	map2_ = other.map2_;
	completemap = other.completemap;
	pushesDone = other.pushesDone;
}

// move constructor
template<class T>
Priority<T>::Priority(Priority&& other)
{
	map1_ = other.map1_;
	other.map1_.clear();
	map2_ = other.map2_;
	other.map2_.clear();
	completemap = other.completemap;
	other.completemap.clear();
	pushesDone = other.pushesDone;
	other.pushesDone = 0;
}

// assignment operator
template<class T>
Priority<T>& Priority<T>::operator=(const Priority<T>& other)
{
	map1_ = other.map1_;
	map2_ = other.map2_;
	completemap = other.completemap;
	pushesDone = other.pushesDone;
	return *this;
}

// move operator
template<class T>
Priority<T>& Priority<T>::operator=(Priority<T>&&other)
{
	map1_ = other.map1_;
	other.map1_.clear();
	map2_ = other.map2_;
	other.map2_.clear();
	completemap = other.completemap;
	other.completemap.clear();
	pushesDone = other.pushesDone;
	other.pushesDone = 0;
	return *this;
}

// destructor
template<class T>
Priority<T>::~Priority()
{
}

template<class T>
void Priority<T>::push_back(T *val,int key1, int key2)
{
	// The value is pushed in both multimaps and then on the completemap and pushesDone is increased
	std::pair<int, T*> myPair1;
	myPair1 = std::make_pair(key1,val);
	map1_.insert(myPair1);

	std::pair<int, T*> myPair2;
	myPair2 = std::make_pair(key2,val);
	map2_.insert(myPair2);
	
	std::pair<int,std::pair<std::pair<int,T*>,std::pair<int,T*>>> completepair;
	completepair = std::make_pair(pushesDone, std::make_pair(myPair1,myPair2));	
	completemap.insert(completepair);
	
	pushesDone++;
}

template<class T>
T* Priority<T>::pop_front(Key k)
{
	// Since multimap is always sorted by key, the first element of the requested map will be the one with the lowest priority
	// For that reason I get that element and store it on an iterator, I clear both multimaps and search for that element on the completemap
	// I then get all the elements of the completemap on the multimaps
	// The result is that the element is eliminated from both maps
	if(!map1_.empty() || !map2_.empty()){
		iterator it = begin(k);
		std::pair <int,T*> thisPair;
		thisPair = std::make_pair(it.it_->first,it.it_->second);
		map1_.clear();
		map2_.clear();
		for(auto it = completemap.cbegin(); it != completemap.cend(); ++it){
			if(it->second.first.first == thisPair.first && it->second.first.second == thisPair.second){
				completemap.erase(it);
			}else if(it->second.second.first == thisPair.first && it->second.second.second == thisPair.second){
				completemap.erase(it);
			}else{
				map1_.insert(it->second.first);
				map2_.insert(it->second.second);
			}
		}
		return it.it_->second;
	}else{
		return nullptr;
	}
}

//iterator constructor
template<class T>
Priority<T>::iterator::iterator()
{
}

// copy constructor of iterator
template<class T>
Priority<T>::iterator::iterator(const Priority<T>::iterator& other)
{
	it_ = other.it_;
}

// assignement operator
template<class T>
typename Priority<T>::iterator& Priority<T>::iterator::operator=(const Priority<T>::iterator& other)
{
	it_ = other.it_;
	return *this;
}

// access operator
template<class T>
T& Priority<T>::iterator::operator*()
{
	return *(it_->second);
}

// access operator
template<class T>
T* Priority<T>::iterator::operator->()
{
	return (it_->second);
}

// preincrement operator
template<class T>
typename Priority<T>::iterator& Priority<T>::iterator::operator++()
{
	++it_; return *this;
}

// postincrement operator
template<class T>
typename Priority<T>::iterator Priority<T>::iterator::operator++(int)
{
	iterator tempit = *this; 
	it_++; 
	return tempit;
}

// equality operator
template<class T>
bool Priority<T>::iterator::operator==(const Priority<T>::iterator& other) const
{
	return other.it_ == it_;
}

// inequality operator
template<class T>
bool Priority<T>::iterator::operator!=(const Priority<T>::iterator& other) const
{
	return other.it_ != it_;
}

template<class T>
typename Priority<T>::iterator Priority<T>::begin(Key k)
{
	// returns the first element of the multimap associated with the selected priority
	iterator it;
	if(k == ONE){
		it.it_ = map1_.begin();
	}else if(k == TWO){
		it.it_ = map2_.begin();
	}
	return it;
}

template<class T>
typename Priority<T>::iterator Priority<T>::end(Key k)
{
	// returns the last element of the multimap associated with the selected priority
	iterator it;
	if(k == ONE){
		it.it_ = map1_.end();
	}else if(k == TWO){
		it.it_ = map2_.end();
	}
	return it;
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
