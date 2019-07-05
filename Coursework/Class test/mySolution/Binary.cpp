#include <iostream>
#include "Binary.h"

using std::ostream;

// Functions requiring only understanding of the data structure
// ============================================================

Binary::Binary()
{
	// Implement me
	number_ = nullptr;
	size_ = 0;
}

Binary::Binary(const Binary& other)
{
	// Implement me
	size_ = other.size_;
	number_ = new bool[other.size_];
	for(int i =0; i < other.size_; i++){
		number_[i] = other.number_[i];
	}
}

Binary::Binary(Binary&& other)
{
	// Implement me
	size_ = other.size_;
	number_ = other.number_;

	other.size_=0;
	other.number_= nullptr;
}

Binary::~Binary() 
{
	delete [] number_;
}

Binary& Binary::operator=(const Binary& other)
{
	// Implement me
	if(size_ < other.size_){
		delete [] number_;
		number_ = new bool[other.size_];
	}
	size_ = other.size_;
	for(int i = 0; i < other.size_; i++){
		number_[i] = other.number_[i]; 
	}
	return *this;
}

Binary& Binary::operator=(Binary&& other)
{
	// Implement me
	size_ = other.size_;
	number_ = other.number_;
	other.size_ =0;
	other.number_=nullptr;
	
	return *this;
}


// Functions requiring basic understanding of Boolean numbers
// ==========================================================
Binary Binary::operator<<(unsigned int shift) const
{
	Binary res(*this);  // Set up res to have the reruired output
	if(res.size_ != 0){
		bool* tempnumber_ = new bool[res.size_ + shift];
//		for(int i = 0; i < res.size_ + shift; i++){
//			if(i < res.size_){
//				tempnumber_[i] = res.number_[i];
//			}else{
//				tempnumber_[i] = 0;			
//			}
//		}	
		for(int i = 0; i < res.size_ + shift; i++){
			if(i < shift){
				tempnumber_[i] = 0;
			}else{
				tempnumber_[i] = res.number_[i-shift];
			}
		}	
		res.number_ = tempnumber_;
		res.size_ = res.size_ + shift;
	}else{
		std::cout << "Zero cannot be left shifted" << std::endl;
	}
	return res;
}

Binary Binary::operator>>(unsigned int shift) const
{
	Binary res(*this);  // Set up res to have the reruired output
	if(res.size_ != 0 || shift < res.size_){
		bool* tempnumber_ = new bool[res.size_ - shift];
		for(int i = shift; i < res.size_; i++){
			tempnumber_[i - shift] = res.number_[i];
		}
		delete [] res.number_;	
		res.size_ = res.size_ - shift;
		res.number_ = tempnumber_;
	}else if(res.size_ == shift){
		res.size_ = 0;
		delete [] res.number_;
		res.number_ = nullptr;
	}else{
		std::cout << "Cannot perform that operation" << std::endl;	
	}
	return res;
}

Binary Binary::operator|(const Binary& other) const
{
	Binary res(*this);  // Set up res to have the reruired output
	// Implement me
	if(res.size_ != 0 && other.size_ != 0){
		if(res.size_ == other.size_){
			for(int i = 0; i < res.size_; i++){
				if(res.number_[i] == 1 || other.number_[i] == 1){
					res.number_[i] = 1;
				}
			}
		}else if(res.size_ > other.size_){
			for(int i = 0; i < other.size_; i++){
				if(res.number_[i] == 1 || other.number_[i] == 1){
					res.number_[res.size_ - other.size_ + i] = 1;
				}
			}
		}else if(res.size_ < other.size_){
			bool* tempnumber_ = new bool[other.size_];
			for(int i = 0; i < other.size_; i++){
				tempnumber_[i] = other.number_[i];
				if(i<= res.size_ && res.number_[i] == 1){					
					// if number_ contains 1 then I overwrite temp to 1
					tempnumber_[i] = 1;					
				}
			}
			delete [] res.number_;
			res.number_ = tempnumber_;
		}
	}else{
		std::cout << "One of the booleans is 0" << std::endl;
	}
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

