/*
 * main.cpp
 *
 *  Created on: 11 Oct 2016
 *      Author: np183
 */

#include <iostream>
#include <string>
#include "InputHelper.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

typedef unsigned int uint; 


inline uint myminfunc(uint a, uint b) {
  if (a<b) return a;
  else return b;
}

inline uint mymaxfunc(uint a, uint b) {
  if (a<b) return b;
  else return a;
}

// declaration of functions that in my opinion do not need to change.
void outputMessage();
void wrongVal();
bool getStartEndJumpVal(uint& start, uint& end, uint& jump, uint& val, bool wval = true, bool wjump=true);
bool getStartEndVal(uint& start, uint& end, uint& val);
bool getStartEnd(uint& start, uint& end);


// The purpose of this exercise is to understand some of the advantages of
// using classes.
// So the program manipulates arrays of integers by doing simple actions on the values
// in them.
// In order to make your life more complicated, the program handles three arrays of
// different sizes.
// It also allows to use only part of the array.
// So each array has a size, first location used, and last location used.
// Whenever doing some manipulation of the arrays all these values need to be carried around.
// This should expose you to the importance of:
// Encapsulation - the ability to just refer to the array without carrying all sorts of
//                 information around it.
// Information hiding - the problems of allowing access to all these parameters from all the
//                      program.
// Areas to complete are marked by ... but you may have to add extra variables and extra
// code in the main in order to "connect" the functions you are implementing.

// Declarations of functions to complete
bool whichArray(...);
void initialize(...);
void increment(...);
void replace(...);
void output(...);
  
int main(int argc, char* argv[]) {

  // The sizes of the arrays
  constexpr uint SIZE0=30;
  constexpr uint SIZE1=40;
  constexpr uint SIZE2=50;

  // The arrays
  uint arr0[SIZE0];
  uint arr1[SIZE1];
  uint arr2[SIZE2];

  // The start (s)and end (e) locations in the arrays.
  // These variables indicate the active area of the array.
  uint arr0s{SIZE0},arr0e{0};
  uint arr1s{SIZE0},arr1e{0};
  uint arr2s{SIZE0},arr2e{0};
  
  
  while (true) {
    outputMessage();
    uint input{0};
    readOneUnsignedInt(input);
    switch (input) {
    case 1: {
      // Complete the function whichArray that allows the user to
      // choose which of the three arrays to work on.
      if (!whichArray(/* ... add parameters ... */)) {
	break;
      }
      
      // Get from the user where the range of locations of the array
      // to initialize and with what value
      uint start;
      uint end;
      uint val;
      if (!getStartEndVal(start,end,val)) {
	break;
      }

      // Complete the function initialize.
      // Initialize the chosen range in the chosen array with the chosen value
      initialize(/* ... add parameters ... */);
    }
      break;
    case 2: {
      // Use the function whichArray that was implemented with case 1.
      if (!whichArray(/* ... add parameters ... */)) {
	break;
      }
      // Get from the user where to update the locations of the array.
      uint start;
      uint end;
      uint val;
      uint jump;
      if (!getStartEndJumpVal(start,end,jump,val)) {
	break;
      }

      // Complete the function increment.
      // Increment (part of) the active range of the array.
      // Increment by val every jump-th element between
      // start and end.
      // Notice that the active range of the array cannot change
      increment(/* ... add parameters ... */);
    }
      break; 
    case 3: {
      // Use the function whichArray that was implemented with case 1 to
      // choose the first array
      cout << "Choose the first array. ";
      if (!whichArray(/* ... add parameters ... */)) {
	break;
      }
      // Use the function whichArray that was implemented with case 1 to
      // choose the first array
      cout << "Choose the second array. ";
      if (!whichArray(/* ... add parameters ... */)) {
	break;
      }
      // Get from the user where to update the locations of the array.
      uint start;
      uint end;
      if (!getStartEnd(start,end)) {
	break;
      }
      // Compete the function replace
      // replace the regions of the arrays between start end end between
      // the two chosen array.
      // Touch only the active parts of the arrays.
      replace(/* ... add parameters ... */);
    }
      break;
    case 4: {
      // Use the function whichArray that was implemented with case 1 to
      // choose the first array
      if (!whichArray(/* ... add parameters ... */)) {
	break;
      }
      // Complete the function output
      // Output the active part of the array
      output(/* ... add parameters ... */);
      
    }
      break;
    default: {
      return 0;
    }	
    }
    
  }
}

// Main implementation task.
// Complete these four functions

bool whichArray(...) {
  cout << "Which array would you like to operate on?" << endl;
  uint whichArr;
  if (!readOneUnsignedInt(whichArr) || whichArr>2) {
    wrongVal();
    return false;
  }
  
  switch (whichArr) {
  case 0: {
    // ...
    break;
  }
  case 1: {
    // ...
    break;
  }
  default: {
    // ...
    break;
  }
  }
  return true;
}
		
void initialize(...) {
  // ...
}

void increment(...) {
  // ...
}
 
void replace(...) {
}

void output(...) {
   // ... 
}
 

// =================================================
// Functions that in my opinion do not need changing
// =================================================
bool getStartEnd(uint& start, uint& end) {
  uint jump{0};
  uint val{0};
  return getStartEndJumpVal(start,end,jump,val,false,false);
}

bool getStartEndVal(uint& start, uint& end, uint& val) {
  uint jump{0};
  return getStartEndJumpVal(start,end,jump,val,true,false);
}

bool getStartEndJumpVal(uint& start, uint& end, uint& jump, uint& val, bool wval, bool wjump) {
  cout << "Where would you like to start?" << endl;
  if (!readOneUnsignedInt(start)) {
    wrongVal();
    return false;
  }
  cout << "Where would you like to end?" << endl;
  if (!readOneUnsignedInt(end)) {
    wrongVal();
    return false;
  }
  if (wjump) {
    cout << "What interval between updated values?" << endl;
    if (!readOneUnsignedInt(jump)) {
      wrongVal();
      return false;
    }
  }
  if (wval) {
    cout << "What value?" << endl;
    if (!readOneUnsignedInt(val)) {
      wrongVal();
      return false;
    }
  }
  return true;
}

void wrongVal() {
	cout << "Please supply correct input." << endl;
}

void outputMessage() {
  cout << "Please choose an option:" << endl;
  cout << "1. Initialize an array." << endl;
  cout << "2. Increment entries." << endl;
  cout << "3. Replace arrays." << endl;
  cout << "4. Print arrays." << endl;
  cout << "Any other input will terminate." << endl;
}
