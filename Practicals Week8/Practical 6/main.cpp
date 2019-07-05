/*
 * main.cpp
 *
 *  Created on: 15 Oct 2014
 *      Author: np183
 */

#include <iostream>
#include <string>

#include "VectorTester.h"
#include "LinkedListTester.h"


using std::cin;
using std::cout;
using std::endl;
using std::string;

class RandFloat {
public:
  RandFloat() {}
  float operator()() const {
    float temp = static_cast<float>(rand());
    temp /= rand();
    return temp;
  }
  string toString() const { return "float"; }
};

class RandInt {
public:
  RandInt() {}
  int operator()() const {
    return rand();
  }
  string toString() const { return "int"; }
};


class RandString {
public:
  RandString() {}
  string operator()() const {
    return std::to_string(rand());
  }
  string toString() const { return "string"; }
};

int main(int argc, char* argv[]) {
  RandFloat randFloat;
  RandInt randInt;
  RandString randString;
  
  if (false) {
    for (unsigned int i=0 ; i<1 ; ++i) {
      VectorTester<float,RandFloat> t3(randFloat);
      t3.testISRedir();
    }
    return 0;
    
  }
  
  while (argc > 1) {
    
    switch (argv[--argc][0]) {
    case 'a':
      {
	VectorTester<int,RandInt> t1(randInt);
	t1.testCtor();
	VectorTester<float,RandFloat> t2(randFloat);
	t2.testCtor();
	VectorTester<string,RandString> t3(randString);
	t3.testCtor();
      }
      break;
    case 'b':
      {
	VectorTester<int,RandInt> t1(randInt);
	t1.testCopyCtor();
	VectorTester<float,RandFloat> t2(randFloat);
	t2.testCopyCtor();
	VectorTester<string,RandString> t3(randString);
	t3.testCopyCtor();
      }
      break;
    case 'c':
      {
	VectorTester<int,RandInt> t1(randInt);
	t1.testPushBack();
	VectorTester<float,RandFloat> t2(randFloat);
	t2.testPushBack();
	VectorTester<string,RandString> t3(randString);
	t3.testPushBack();
      }
      break;
    case 'd':
      {
	VectorTester<int,RandInt> t1(randInt);
	t1.testOperatorSqBr();
	VectorTester<float,RandFloat> t2(randFloat);
	t2.testOperatorSqBr();
	VectorTester<string,RandString> t3(randString);
	t3.testOperatorSqBr();
      }
      break;
    case 'e':
      {
	VectorTester<int,RandInt> t1(randInt);
	t1.testOperatorEq();
	VectorTester<float,RandFloat> t2(randFloat);
	t2.testOperatorEq();
	VectorTester<string,RandString> t3(randString);
	t3.testOperatorEq();
      }
      break;
    case 'f':
      {
	VectorTester<int,RandInt> t1(randInt);
	t1.testSize();
	VectorTester<float,RandFloat> t2(randFloat);
	t2.testSize();
	VectorTester<string,RandString> t3(randString);
	t3.testSize();
      }
      break;
    case 'g':
      {
	VectorTester<int,RandInt> t1(randInt);
	t1.testEmpty();
	VectorTester<float,RandFloat> t2(randFloat);
	t2.testEmpty();
	VectorTester<string,RandString> t3(randString);
	t3.testEmpty();
      }
      break;
    case 'h':
      {
	VectorTester<int,RandInt> t1(randInt);
	t1.testClear();
	VectorTester<float,RandFloat> t2(randFloat);
	t2.testClear();
	VectorTester<string,RandString> t3(randString);
	t3.testClear();
      }
      break;
    case 'i':
      {
	VectorTester<int,RandInt> t1(randInt);
	t1.testMemory();
	VectorTester<float,RandFloat> t2(randFloat);
	t2.testMemory();
	VectorTester<string,RandString> t3(randString);
	t3.testMemory();
      }
      break;
    case 'j':
      {
	LinkedListTester<int,RandInt> t1(randInt);
	t1.testCtor();
	LinkedListTester<float,RandFloat> t2(randFloat);
	t2.testCtor();
	LinkedListTester<string,RandString> t3(randString);
	t3.testCtor();
      }
      break;
    case 'k':
      {
	LinkedListTester<int,RandInt> t1(randInt);
	t1.testCopyCtor();
	LinkedListTester<float,RandFloat> t2(randFloat);
	t2.testCopyCtor();
	LinkedListTester<string,RandString> t3(randString);
	t3.testCopyCtor();
		  }
      break;
    case 'l':
      {
	LinkedListTester<int,RandInt> t1(randInt);
	t1.testFunctionality();
	LinkedListTester<float,RandFloat> t2(randFloat);
	t2.testFunctionality();
	LinkedListTester<string,RandString> t3(randString);
	t3.testFunctionality();
      }
      break;
    case 'm':
      {
	LinkedListTester<int,RandInt> t1(randInt);
	t1.testOperatorEq();
	LinkedListTester<float,RandFloat> t2(randFloat);
	t2.testOperatorEq();
	LinkedListTester<string,RandString> t3(randString);
	t3.testOperatorEq();
      }
      break;
    case 'n':
      {
	LinkedListTester<int,RandInt> t1(randInt);
	t1.testSize();
	LinkedListTester<float,RandFloat> t2(randFloat);
	t2.testSize();
	LinkedListTester<string,RandString> t3(randString);
	t3.testSize();
      }
      break;
    case 'o':
      {
	LinkedListTester<int,RandInt> t1(randInt);
	t1.testEmpty();
	LinkedListTester<float,RandFloat> t2(randFloat);
	t2.testEmpty();
	LinkedListTester<string,RandString> t3(randString);
	t3.testEmpty();
      }
      break;
    case 'p':
      {
	LinkedListTester<int,RandInt> t1(randInt);
	t1.testClear();
	LinkedListTester<float,RandFloat> t2(randFloat);
	t2.testClear();
	LinkedListTester<string,RandString> t3(randString);
	t3.testClear();
      }
      break;
    case 'q':
      {
	LinkedListTester<int,RandInt> t1(randInt);
	t1.testMemory();
	LinkedListTester<float,RandFloat> t2(randFloat);
	t2.testMemory();
	LinkedListTester<string,RandString> t3(randString);
	t3.testMemory();
      }
      break;
    case 'r':
      {
	VectorTester<int,RandInt> t1(randInt);
	t1.testToString();
	VectorTester<float,RandFloat> t2(randFloat);
	t2.testToString();
	VectorTester<string,RandString> t3(randString);
	t3.testToString();
      }
      break;
    case 's':
      {
	VectorTester<int,RandInt> t1(randInt);
	t1.testOSRedir();
	VectorTester<float,RandFloat> t2(randFloat);
	t2.testOSRedir();
	VectorTester<string,RandString> t3(randString);
	t3.testOSRedir();
      }
      break;
    case 't':
      {
	VectorTester<int,RandInt> t1(randInt);
	t1.testISRedir();
	VectorTester<float,RandFloat> t2(randFloat);
	t2.testISRedir();
	// There is no way to create a corrupt input
	// for strings.
	VectorTester<string,RandString> t3(randString);
	t3.testISRedir(false);
      }
      break;
    case 'u':
      {
	LinkedListTester<int,RandInt> t1(randInt);
	t1.testToString();
	LinkedListTester<float,RandFloat> t2(randFloat);
	t2.testToString();
	LinkedListTester<string,RandString> t3(randString);
	t3.testToString();
      }
      break;
    case 'v':
      {
	LinkedListTester<int,RandInt> t1(randInt);
	t1.testOSRedir();
	LinkedListTester<float,RandFloat> t2(randFloat);
	t2.testOSRedir();
	LinkedListTester<string,RandString> t3(randString);
	t3.testOSRedir();
      }
      break;
    case 'w':
    default:
      {
	LinkedListTester<int,RandInt> t1(randInt);
	t1.testISRedir();
	LinkedListTester<float,RandFloat> t2(randFloat);
	t2.testISRedir();
	LinkedListTester<string,RandString> t3(randString);
	t3.testISRedir(false);
      }
      break;
    }
  }
  return 0;
}

