
#ifndef BINARY_
#define BINARY_

#include <iosfwd>
#include <exception>

// Implement a Binary class that represents large numbers in
// binary.
// The class stores an array of Boolean variables
// that represent a non-negative integer.
// An integer is represented in binary with the least
// significant bit (i.e., the one worth 1s) in
// location 0 of the array.
// The representation is tight:
// That is, the array will not
// contain binary numbers looking like 010.
// The last element in the array is always true.
// The representation of 0 should be the nullptr with size 0.
//
// The order of the functions in the header file (and the cpp file)
// is according to the way I perceive their complexity.
// 1. Functions that do not require any understanding of Boolean
//    numbers and only require understanding of the data structure
//    (and array of bool with its size).
// 2. Functions that require very simple understanding of
//    Boolean numbers.
// 3. Functions that require good understanding of Boolean
//    numbers.
class Binary 
{
	// The data members:
	// number_ - an array of boolean values
	// size_ - the size of this array
private:
	unsigned int size_;
	bool* number_;

public: 
	// Functions requiring only understanding of the data structure
	// ============================================================

	// Construct a Binary number whose value is 0
	Binary();
	// Copy constructor
	Binary(const Binary&);
	// Move constructor
	Binary(Binary&&);
	// Clean your mess
	~Binary();

	// Implement the assignment operator with copy semantics
	Binary& operator=(const Binary&);
	// Implement the assignment operator with move semantics
	Binary& operator=(Binary&&);

	// Functions requiring basic understanding of Boolean numbers
	// ==========================================================

	// Implement the zero-filled shift left operator.
	// This operator accepts an unsigned int parameter and
	// moves the binary number by this number of digits to the
	// left.
	// For example, 1 << 5= 100000, where 1 is the binary
	// number and 5 is the integer.
	Binary operator<<(unsigned int) const;

	// Implement the shift right operator.
	// This operator accepts an unsigned int parameter and
	// moves the binary number by this number of digits to the
	// right.
	// For example, 10000 >> 4 = 1.
	// Or, 10101 >> 2 = 101 and 10101 >> 5 = 0
	//
	// Notice that subtraction with unsigned ints works a bit strange
	// 0-1 is MAXINT and not -1!
	Binary operator>>(unsigned int) const;

	// Implement the bitwise-or operator.
	// This operator creates a new binary number
	// whose bits are the or of the bits in the respective
	// positions of the two binary numbers.
	// For example, 1001|10=1011 and 10001|101=10101.
	// Notice what happens when one number is longer than the
	// other.
	Binary operator|(const Binary&) const;

	// Implement the bitwise-and operator.
	// This operator creates a new binary number
	// whose bits are the and of the bits in the respective
	// positions of the two binary numbers.
	// For example, 1001&10=0 and 10001&101=1.
	// Notice what happens when one number is longer than the
	// other.
	Binary operator&(const Binary&) const;

	// Implement the "readable" output operator
	// The numbers should be written as we would expect to
	// read them.
	// So the result of:
	// Binary b;
	// ++b; ++b;
	// cout << b;
	// Should be 10.
	//
	// Notice that the order of output is reversed to the order
	// of storage in the array!
	friend std::ostream& operator<< (std::ostream&,const Binary&);

	// Functions requiring good understanding of Boolean numbers
	// =========================================================

	// A constructor that accepts an integer and
	// initializes the Binary number to that integer.
	explicit Binary(unsigned int);

	// Implement a conversion to integer function
	// This function should throw an exception if the
	// integer is larger than 32 bits (this part is implemented for you).
	//
	// Otherwise, it should construct an integer
	// with the right value and return it.
	// Run time of this method should be reasonable.
	// E.g.,
	// Binary temp;
	// int toReturn=0;
	// while (!temp==*this) {
	//    ++temp;
	//    ++toReturn;
	// }
	// Is ***not*** considered efficient
	operator int() const throw (std::exception);

	// Increases the value of the Binary number by 1.
	// Notice that the parameter should be ignored.
	// It is used to distinguish between a call to
	// ++i and i++.
	// Here we implement i++.
	Binary& operator++(int);

	// Add two Binary numbers and return the
	// result of addition.
	Binary operator+(const Binary&) const;


	// These functions return the private data members.
	// This violates the basic principles of c++ but is
	// used for evaluation purposes.
	// Their implementation is provided.
	// Don't learn from it!
	bool* theArry() { return number_; }
	unsigned int size() { return size_; }
	void setPrivate(bool* newNum,unsigned int newSize) { number_=newNum; size_=newSize; }
};

#endif
