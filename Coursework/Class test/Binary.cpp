#include <iostream>
#include "Binary.h"

using std::ostream;

// Functions requiring only understanding of the data structure
// ============================================================

Binary::Binary()
{
	// Implement me
}

Binary::Binary(const Binary& other)
{
	// Implement me
}

Binary::Binary(Binary&& other)
{
	// Implement me
}

Binary::~Binary() 
{
	// Implement me
}

Binary& Binary::operator=(const Binary& other)
{
	// Implement me
	return *this;
}

Binary& Binary::operator=(Binary&& other)
{
	// Implement me
	return *this;
}


// Functions requiring basic understanding of Boolean numbers
// ==========================================================
Binary Binary::operator<<(unsigned int shift) const
{
	Binary res;  // Set up res to have the reruired output
	// Implement me
	return res;
}

Binary Binary::operator>>(unsigned int shift) const
{
	Binary res;  // Set up res to have the reruired output
	// Implement me
	return res;
}

Binary Binary::operator|(const Binary& other) const
{
	Binary res;  // Set up res to have the reruired output
	// Implement me
	return res;
}

Binary Binary::operator&(const Binary& other) const
{
	Binary res;  // Set up res to have the reruired output
	// Implement me
	return res;
}

ostream& operator<< (ostream& stream, const Binary& bin)
{
	// Implement me
	return stream;
}

// Functions requiring good understanding of Boolean numbers
// =========================================================

Binary::Binary(unsigned int source)
{
	// Implement me
}

Binary::operator int() const throw (std::exception) {
	if (size_ > 32) {
		throw std::exception();
	}
	int res; // setup res to have the required result
	// implement me
	return res;;
}

Binary& Binary::operator++(int blah)
{
	// Implement me
	return *this;
}

Binary Binary::operator+(const Binary& other) const
{
	Binary res;  // Set up res to have the reruired output
	// Implement me
	return res;
}

