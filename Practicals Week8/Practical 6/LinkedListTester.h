/*
 * VectorTester.h
 *
 *  Created on: 15 Oct 2014
 *      Author: np183
 */

#ifndef LINKEDLISTTESTER_H_
#define LINKEDLISTTESTER_H_

#include <stdlib.h>
#include <iosfwd>
#include <iomanip>
#include <sstream>
#include <utility>
#include <string>

#include "LinkedList.h"

template<class Object, class Rand>
class LinkedListTester {
public:
	LinkedListTester() = delete;
	LinkedListTester(const Rand& rand);
	~LinkedListTester();

	void testCtor();
	void testCopyCtor();
	void testFunctionality();
	void testOperatorEq();
	void testSize();
	void testEmpty();
	void testClear();
	void testMemory();
	// Assume that Rand does not produce strings with spaces!
	void testToString();
	// Assume that Rand does not produce strings with spaces!
	void testOSRedir();
	// Assume that Rand does not produce strings with spaces!
	void testISRedir(bool corruptible = true);

private:
	void errorOut_(const std::string& errMsg, unsigned int errBit);
	bool errorSet_(unsigned int mask);
	void passOut_(const std::string& passMsg);
	void setFuncname_(const std::string& name);

	void CompareWithStringSimple_(const std::string& result,Object* arr,int size);
	void CompareWithString_(const std::string& result,Object* arr,int size,int length,char fill);

	char error_;
	std::string funcname_;

	static constexpr int LINKEDLISTSIZE=100000;
	const Rand& rand_;
};


template<class Object, class Rand>
LinkedListTester<Object, Rand>::LinkedListTester(const Rand& random)
: error_(false), funcname_(), rand_(random) {
	unsigned int val(time(0)*rand());
	std::cout << val << std::endl;
	srand(val);
}

template<class Object, class Rand>
LinkedListTester<Object, Rand>::~LinkedListTester() {
}

template<class Object, class Rand>
void LinkedListTester<Object, Rand>::testCtor() {
	setFuncname_("testCtor");
	LinkedList<Object> ll;
	if (ll.size()!=0) {
		errorOut_("initial size is not 0",1);
	}
	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		ll.push_back(rand_());
		if (ll.size() != i+1) {
			errorOut_("wrong size",2);
			break;
		}
	}
	passOut_("did some tests to the constructors");
}

template<class Object, class Rand>
void LinkedListTester<Object, Rand>::testCopyCtor() {
	setFuncname_("testCopyCtor");
	// Create an initial vector
	LinkedList<Object> source;
	for (int i=0 ; i < LINKEDLISTSIZE ; ++i) {
		source.push_back(rand_());
	}

	LinkedList<Object> copy(source);

	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		if (source.first() != copy.first()) {
			errorOut_("different values in copy",1);
			break;
		}
		source.pop_front();
		copy.pop_front();
	}
	for (int i=0 ; i < LINKEDLISTSIZE ; ++i) {
		source.push_back(rand_());
	}

	LinkedList<Object> copy1(source);
	LinkedList<Object> move(std::move(source));
	if (source.size() != 0) {
		errorOut_("Move constructor does not erase",2);
	}
	if (move.size() != copy1.size()) {
		errorOut_("Sizes don't match between copy and move",3);
	}
	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		if (copy1.first() != move.first()) {
			errorOut_("Copy and move don't match",4);
			break;
		}
		copy1.pop_front();
		move.pop_front();
	}
	passOut_("tested the copy and move constructors");
}

template<class Object, class Rand>
void LinkedListTester<Object, Rand>::testFunctionality() {
	setFuncname_("testFunctionality");
	LinkedList<Object> ll;
	Object backup[LINKEDLISTSIZE];
	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		Object temp = rand_();
		ll.push_back(temp);
		backup[i]=temp;
	}
	int head=0;
	int tail=LINKEDLISTSIZE-1;
	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		if (true || rand()%2) {
			if (backup[head]!=ll.first()) {
				errorOut_("insert and retrieve different values",1);
				break;
			}
			ll.pop_front();
			++head;
		}
		else {
			if (backup[tail]!= ll.last()) {
				errorOut_("insert and retrieve different values",2);
				break;
			}
			ll.pop_back();
			--tail;
		}
	}

	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		ll.push_back(backup[i]);
	}
	LinkedList<Object> lRev;
	while (!ll.empty()) {
		lRev.push_back(ll.last());
		ll.pop_back();
	}
	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		if (lRev.first() != backup[LINKEDLISTSIZE-1-i]) {
			errorOut_("insert and retrieve different values",3);
			break;
		}
		lRev.pop_front();
	}
	passOut_("added and removed elements and checked that they are correct");
}

template<class Object, class Rand>
void LinkedListTester<Object, Rand>::testOperatorEq() {
	setFuncname_("testOperatorEq");
	// Create an initial vector
	LinkedList<Object> source;
	for (int i=0 ; i < LINKEDLISTSIZE ; ++i) {
		source.push_back(rand_());
	}
	LinkedList<Object> copy;
	copy = source;

	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		if (source.first() != copy.first()) {
			errorOut_("different values in copy",1);
			break;
		}
		source.pop_front();
		copy.pop_front();
	}

	for (int i=0 ; i < LINKEDLISTSIZE ; ++i) {
		source.push_back(rand_());
	}

	LinkedList<Object> copy1;
	copy1 = source;
	LinkedList<Object> move;
	move = std::move(source);
	if (source.size() != 0) {
		errorOut_("Move constructor does not erase",2);
	}
	if (move.size() != copy1.size()) {
		errorOut_("Sizes don't match between copy and move",3);
	}
	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		if (copy1.first() != move.first()) {
			errorOut_("Copy and move don't match",4);
			break;
		}
		copy1.pop_front();
		move.pop_front();
	}
	passOut_("tested copy and move operator=");
}

template<class Object, class Rand>
void LinkedListTester<Object, Rand>::testSize() {
	setFuncname_("testSize");
	LinkedList<Object> ll;
	for (int i=0 ; i<100 ; ++i) {
		if (ll.size() != i) {
			errorOut_("returned wrong size",1);
			break;
		}
		ll.push_back(rand_());
	}
	passOut_("the size matches what I expected");
}

template<class Object, class Rand>
void LinkedListTester<Object, Rand>::testEmpty() {
	setFuncname_("testEmpty");
	LinkedList<Object> ll;
	if (!ll.empty()) {
		errorOut_("initially not empty",1);
	}
	for (int i=0 ; i<100 ; ++i) {
		ll.push_back(rand_());
	}
	if (ll.empty()) {
		errorOut_("empty after adding things",2);
	}
	ll.clear();
	if (!ll.empty()) {
		errorOut_("after clear not empty",1);
	}
	passOut_("empty when expected it to be");
}

template<class Object, class Rand>
void LinkedListTester<Object, Rand>::testClear() {
	setFuncname_("testClear");

	LinkedList<Object> ll;
	for (int i=0 ; i<LINKEDLISTSIZE ; ++i) {
		ll.push_back(rand_());
	}
	if (ll.size() != LINKEDLISTSIZE) {
		errorOut_("could not build up a full vector",0);
		return;
	}
	ll.clear();
	if (ll.size() != 0) {
		errorOut_("did not clear",1);
	}
	passOut_("cleared the vector");
}


template<class Object, class Rand>
void LinkedListTester<Object, Rand>::testMemory() {
	setFuncname_("testMemory");
	for (int j=0 ; j<LINKEDLISTSIZE/100; ++j) {
		LinkedList<Object> ll;
		for (int i=0 ; i<LINKEDLISTSIZE/10 ; ++i) {
			if (rand()%2) {
				ll.push_back(rand_());
			}
			else {
				ll.push_front(rand_());
			}
		}
	}
	passOut_("stressed the memory usage");
}

template<class Object, class Rand>
void LinkedListTester<Object, Rand>::testToString() {
	setFuncname_("testToString");
	Object backup[LINKEDLISTSIZE/100];
	LinkedList<Object> ll;
	for (int j = 0 ; j<LINKEDLISTSIZE/100 ; ++j) {
		backup[j] = rand_();
		ll.push_back(backup[j]);
	}

	std::string result = ll.toString();
	CompareWithStringSimple_(result,backup,LINKEDLISTSIZE/100);

	int length = rand() % 100;
	result  = ll.toString(length,'_');

	passOut_("string was ok");
}

template<class Object, class Rand>
void LinkedListTester<Object, Rand>::testOSRedir() {
	setFuncname_("testOSRedir");

	Object backup[LINKEDLISTSIZE/100];
	LinkedList<Object> ll;
	for (int j=0 ; j< LINKEDLISTSIZE/100 ; ++j) {
	  backup[j] = rand_();
	  ll.push_back(backup[j]);
	}

	std::stringstream s;
	s << ll;
	CompareWithStringSimple_(s.str(),backup,LINKEDLISTSIZE/100);

	int length = rand() % 100;
	std::stringstream s1;
	s1.fill('*');
	s1.width(length);
	s1 << ll;
	CompareWithString_(s1.str(),backup,LINKEDLISTSIZE/100,length,'*');

	passOut_("output was OK");
}

template<class Object, class Rand>
void LinkedListTester<Object, Rand>::testISRedir(bool corruptible) {
  setFuncname_("testISRedir");
  std::stringstream s1,s2;
  Object backup[LINKEDLISTSIZE/100];
  bool notfirst = false;
  for (int j=0 ; j<LINKEDLISTSIZE/100 ; ++j) {
    backup[j] = rand_();
    if (notfirst) {
      s1 << " ";
      s2 << " ";
    }
    s1 << std::setprecision(30) << backup[j];
    s2 << std::setprecision(30) << backup[j];
    notfirst = true;
  }
  s2 << "blah";
  s1.seekg(0);
  s2.seekg(0);

  LinkedList<Object> l1,l2;
  s1 >> l1;
  s2 >> l2;

  if (corruptible && l2.size() > 0) {
    errorOut_("read from a corrupt stream",0);
  }
  if (corruptible && s2) {
    errorOut_("stream with error should be unusable",1);
  }

  if (l1.size() != LINKEDLISTSIZE/100) {
    errorOut_("failed to read well structured stream",2);
  }
  else {
    for (int j=0 ; j<LINKEDLISTSIZE/100 ; ++j) {
      if (backup[j] != l1.first()) {
	errorOut_("wrong values in read vector",3);
	break;
      }
      l1.pop_front();
    }

    if (!s1 || s1.peek()!=std::char_traits<char>::eof() || !s1.eof()) {
      errorOut_("stream without error should be usable and at eof",4);
    }
  }
	passOut_("managed to input well");
}

template<class Object, class Rand>
void LinkedListTester<Object, Rand>::errorOut_(const std::string& errMsg, unsigned int errBit) {
	std::cerr << funcname_ << " " << "(fail";
        if (errBit)
                std::cerr << errBit;
        std::cerr << "): " << errMsg << std::endl;
        error_|=(1<<errBit);
}

template<class Object, class Rand>
bool LinkedListTester<Object, Rand>::errorSet_(unsigned int mask) {
        return error_& mask;
}

template<class Object, class Rand>
void LinkedListTester<Object, Rand>::passOut_(const std::string& passMsg) {
        if (!error_) {
                std::cerr << funcname_ << " " << "(pass): " << passMsg << std::endl;
        }
}

template<class Object, class Rand>
void LinkedListTester<Object, Rand>::setFuncname_(const std::string& name) {
	funcname_ = name + "<" + rand_.toString() + ">";
}

template<class Object, class Rand>
void LinkedListTester<Object, Rand>::CompareWithStringSimple_(const std::string& result,
						Object* arr,
						int size)
{
	std::string::size_type begin=0;
	for (int j=0 ; j<size ; ++j) {
		std::string::size_type end = result.find(' ',begin);
		if (end == std::string::npos) {
			end = result.length();
		}
		std::string currentelem = result.substr(begin,end-begin);
		begin = end+1;

		std::stringstream temp;
		temp << arr[j];
		if (currentelem != temp.str()) {
			errorOut_("print to one line did not work well",1);
			return;
		}
	}
}

template<class Object, class Rand>
void LinkedListTester<Object, Rand>::CompareWithString_(const std::string& result, Object* arr,
					  int size, int length, char fill)
{
	int j=0;
	std::string::size_type begin = 0;
	while (begin < result.length()) {
		std::string::size_type end=result.find('\n',begin);
		if (end == std::string::npos) {
			end = result.length();
		}
		std::string currentline = result.substr(begin,end-begin);
		begin=end+1;
		if (currentline.length() > length && currentline.find(fill)==std::string::npos && currentline.find(' ')==std::string::npos) {
			errorOut_("too long lines",2);
			return;
		}
		std::string::size_type endl=0;
		for (std::string::size_type beginl=0;
			 beginl < currentline.length();
			 beginl = endl+1) {
			endl=currentline.find(fill,beginl);
			if (endl==std::string::npos) {
				endl = currentline.length();
			}
			std::string currentelem = currentline.substr(beginl,endl-beginl);

			std::stringstream temp;
			temp << arr[j];
			if (currentelem != temp.str()) {
				errorOut_("something went wrong",3);
				return;
			}
			++j;
		}
	}
}



#endif /* LINKEDLISTTESTER_H_ */
