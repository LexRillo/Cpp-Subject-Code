/*
 * VectorTester.h
 *
 *  Created on: 15 Oct 2014
 *      Author: np183
 */

#ifndef VECTORTESTER_H_
#define VECTORTESTER_H_

#include <string>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <utility>

#include "Vector.h"

template<class Object, class Rand>
class VectorTester {
public:
	VectorTester() = delete;
	VectorTester(const Rand& rand);
	~VectorTester();

	void testCtor();
	void testCopyCtor();
	void testPushBack();
	void testOperatorSqBr();
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

	static constexpr int VECSIZE=100000;
	const Rand& rand_;
};


template<class Object, class Rand>
  VectorTester<Object, Rand>::VectorTester(const Rand& random) 
  : error_(false), funcname_(), rand_(random) {
	unsigned int val(time(0)*rand());
	std::cout << val << std::endl;
	srand(val);
}

template<class Object, class Rand>
VectorTester<Object, Rand>::~VectorTester() {
}

template<class Object, class Rand>
void VectorTester<Object, Rand>::testCtor() {
  setFuncname_("testCtor");
	Vector<Object> vec;
	if (vec.size()!=0) {
		errorOut_("initial size is not 0",1);
	}
	for (int i=0 ; i<VECSIZE ; ++i) {
	  vec.push_back(rand_());
		if (vec.size() != i+1) {
			errorOut_("wrong size",2);
			break;
		}
	}

	int size=rand()%VECSIZE;
	Object val(rand_());
	Vector<Object> vec1(size,val);
	if (vec1.size()!=size) {
		errorOut_("set to the wrong size",3);
	}
	else {
		for (int i=0 ; i < size ; ++i) {
			if (vec1[i]!=val) {
				errorOut_("values initialized incorrectly",4);
				break;
			}
		}
	}
	passOut_("did some tests to the constructors");
}

template<class Object, class Rand>
void VectorTester<Object, Rand>::testCopyCtor() {
  setFuncname_("testCopyCtor");
	// Create an initial vector
	Vector<Object> source;
	for (int i=0 ; i < VECSIZE ; ++i) {
	  source.push_back(rand_());
	}
	Vector<Object> copy(source);

	for (int i=0 ; i<VECSIZE ; ++i) {
		if (source[i] != copy[i]) {
			errorOut_("different values in copy",1);
			break;
		}
	}

	Vector<Object> move(std::move(source));
	if (source.size() != 0) {
		errorOut_("Move constructor does not erase",1);
	}
	if (move.size() != copy.size()) {
		errorOut_("Sizes don't match between copy and move",2);
	}
	for (int i=0 ; i<VECSIZE ; ++i) {
		if (copy[i] != move[i]) {
			errorOut_("Copy and move don't match",3);
			break;
		}
	}
	passOut_("tested the copy and move constructors");
}

template<class Object, class Rand>
void VectorTester<Object, Rand>::testPushBack() {
  setFuncname_("testPushBack");
	Vector<Object> vec;
	Object backup[VECSIZE];
	for (int i=0 ; i<VECSIZE ; ++i) {
	  Object temp(rand_());
		vec.push_back(temp);
		backup[i]=temp;
	}
	for (int i=0 ; i<VECSIZE ; ++i) {
		if (vec[i] != backup[i]) {
			errorOut_("insert and retrieve the same values",1);
			break;
		}
	}

	passOut_("added 100 elements and checked that they are retrieved");
}

template<class Object, class Rand>
void VectorTester<Object, Rand>::testOperatorSqBr() {
  setFuncname_("testOperatorSqBr");

  Object fixed =  rand_();
  Vector<Object> vec(VECSIZE,fixed);
	Object rec[VECSIZE];
	for (int i=0 ; i<VECSIZE ; ++i) {
	  rec[i]=fixed;
	}

	for (int i=0 ; i<VECSIZE ; ++i) {
		int loc = rand() % 200;
		Object val(rand_());
		vec[loc] = val;
		rec[loc] = val;
	}

	for (int i=0 ; i<VECSIZE ; ++i) {
		if (vec[i] != rec[i]) {
			errorOut_("wrong value retrieved",1);
			break;
		}
	}
	passOut_("set elements and retrieved them");
}


template<class Object, class Rand>
void VectorTester<Object, Rand>::testOperatorEq() {
  setFuncname_("testOperatorEq");
	// Create an initial vector
	Vector<Object> source;
	for (int i=0 ; i < VECSIZE ; ++i) {
		source.push_back(rand_());
	}
	Vector<Object> copy(50,Object());
	copy = source;

	for (int i=0 ; i<VECSIZE ; ++i) {
		if (source[i] != copy[i]) {
			errorOut_("different values in copy",1);
			break;
		}
	}

	Vector<Object> move(50,rand_());
	move = std::move(source);
	if (source.size() != 50 && source.size() != 0) {
		errorOut_("Move constructor does not swap or erase",1);
	}
	if (move.size() != copy.size()) {
		errorOut_("Sizes don't match between copy and move",2);
	}
	for (int i=0 ; i<VECSIZE ; ++i) {
		if (copy[i] != move[i]) {
			errorOut_("Copy and move don't match",3);
			break;
		}
	}
	passOut_("tested the copy and move constructors");

}

template<class Object, class Rand>
void VectorTester<Object, Rand>::testSize() {
  setFuncname_("testSize");
	Vector<Object> vec;
	for (int i=0 ; i<100 ; ++i) {

		if (vec.size() != i) {
			errorOut_("returned wrong size",1);
			break;
		}
		vec.push_back(rand_());
	}
	passOut_("the size matches what I expected");
}

template<class Object, class Rand>
void VectorTester<Object, Rand>::testEmpty() {
  setFuncname_("testEmpty");
	Vector<Object> vec;
	if (!vec.empty()) {
		errorOut_("initially not empty",1);
	}
	for (int i=0 ; i<100 ; ++i) {
	  vec.push_back(rand_());
	}
	if (vec.empty()) {
		errorOut_("empty after adding things",2);
	}
	vec.clear();
	if (!vec.empty()) {
		errorOut_("after clear not empty",1);
	}
	passOut_("empty when expected it to be");
}

template<class Object, class Rand>
void VectorTester<Object, Rand>::testClear() {
  setFuncname_("testClear");

	Vector<Object> vec;
	for (int i=0 ; i<VECSIZE ; ++i) {
	  vec.push_back(Object());
	}
	if (vec.size() != VECSIZE) {
		errorOut_("could not build up a full vector",0);
		return;
	}
	vec.clear();
	if (vec.size() != 0) {
		errorOut_("did not clear",1);
	}
	passOut_("cleared the vector");
}


template<class Object, class Rand>
void VectorTester<Object, Rand>::testMemory() {
  setFuncname_("testMemory");
	for (int j=0 ; j<VECSIZE/100; ++j) {
		Vector<Object> vec;
		for (int i=0 ; i<VECSIZE/10 ; ++i) {
		  vec.push_back(rand_());
		}
		vec[VECSIZE/10-1]=rand_();
	}

	passOut_("stressed the memory usage");
}

template<class Object, class Rand>
void VectorTester<Object, Rand>::testToString() {
  setFuncname_("testToString");
	Object backup[VECSIZE/100];
	Vector<Object> vec;
	for (int j = 0 ; j<VECSIZE/100 ; ++j) {
	  backup[j] = rand_();
	  vec.push_back(backup[j]);
	}

	std::string result = vec.toString();

	CompareWithStringSimple_(result,backup,VECSIZE/100);
	int length = rand() % 100;
	result  = vec.toString(length,'_');
	CompareWithString_(result,backup,VECSIZE/100,length,'_');

	passOut_("string was ok");
}

template<class Object, class Rand>
void VectorTester<Object, Rand>::testOSRedir() {
  setFuncname_("testOSRedir");
	Object backup[VECSIZE/100];
	Vector<Object> vec;
	for (int j = 0 ; j<VECSIZE/100 ; ++j) {
	  backup[j] = rand_();
	  vec.push_back(backup[j]);
	}

	std::stringstream s;
	s << vec;
	CompareWithStringSimple_(s.str(),backup,VECSIZE/100);

	int length = rand() % 100;
	std::stringstream s1;
	s1.fill('(');
	s1.width(length);
	s1 << vec;
	CompareWithString_(s1.str(),backup,VECSIZE/100,length,'(');

	passOut_("output was OK");
}

template<class Object, class Rand>
void VectorTester<Object, Rand>::testISRedir(bool corruptible) {
  setFuncname_("testISRedir");

  std::stringstream s1,s2;
  Object backup[VECSIZE/100];
  bool notfirst = false;
  for (int j=0 ; j<VECSIZE/100 ; ++j) {
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

  Vector<Object> v1,v2;
  s1 >> v1;
  s2 >> v2;

  if (corruptible && v2.size() > 0) {
    errorOut_("read from a corrupt stream",0);
  }
  if (corruptible && s2) {
    errorOut_("stream with error should be unusable",1);
  }

  if (v1.size() != VECSIZE/100) {
    errorOut_("failed to read well structured stream",2);
  }
  else {
    for (int j=0 ; j<VECSIZE/100 ; ++j) {
      if (backup[j] != v1[j]) {
	errorOut_("wrong values in read vector",3);
	break;
      }
    }

    if (!s1 || s1.peek()!=std::char_traits<char>::eof() || !s1.eof()) {
      errorOut_("stream without error should be usable and at eof",4);
    }
  }
  passOut_("managed to input well");
}



template<class Object, class Rand>
void VectorTester<Object, Rand>::errorOut_(const std::string& errMsg, unsigned int errBit) {
  std::cerr << funcname_ << " " << "(fail";
        if (errBit)
	  std::cerr << errBit;
	std::cerr << "): " << errMsg << std::endl;
        error_|=(1<<errBit);
}

template<class Object, class Rand>
bool VectorTester<Object, Rand>::errorSet_(unsigned int mask) {
        return error_& mask;
}

template<class Object, class Rand>
void VectorTester<Object, Rand>::passOut_(const std::string& passMsg) {
        if (!error_) {
	  std::cerr << funcname_ << " " << "(pass): " << passMsg << std::endl;
        }
}

template<class Object, class Rand>
  void VectorTester<Object, Rand>::setFuncname_(const std::string& name) {
  funcname_ = name + '<' + rand_.toString() + '>';
}

template<class Object, class Rand>
void VectorTester<Object, Rand>::CompareWithStringSimple_(const std::string& result,Object* arr, int size) {
	std::string::size_type begin=0;
	int j=0;
	for ( ; begin < result.length() && j<size ; ++j) {
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
	if (j != size) {
	  errorOut_("was expecting more elements",2);
	}
}


template<class Object, class Rand>
void VectorTester<Object, Rand>::CompareWithString_(const std::string& result, Object* backup, int size, int length, char fill) 
{
  std::string::size_type begin = 0;
	int j=0;
	while (begin < result.length()) {
		std::string::size_type end=result.find('\n',begin);
		if (end == std::string::npos) {
			end = result.length();
		}
		std::string currentline = result.substr(begin,end-begin);
		begin=end+1;
		if (currentline.length() > length && currentline.find(fill)!=std::string::npos && currentline.find(' ')!=std::string::npos) {
			errorOut_("too long lines",3);
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
			temp << backup[j];
			if (currentelem != temp.str()) {
				errorOut_("something went wrong",4);
				return;
			}
			++j;
		}
	}
}

#endif /* VECTORTESTER_H_ */
