#include <iostream>
#include "Binary.h"

using std::cout;
using std::endl;

void print(Binary& n);
void random(Binary& n);

int main() {
	unsigned int val(time(0)*rand());
	cout << val << endl;
	srand(val);


	if (true) { // Test default constructor, copy and move constructors and destructor
	  Binary n;

	  cout << "1. This should be 0:" << endl;
	  print(n);
	  random(n);
	  cout << "2. This is a random binary number:" << endl;
	  print(n);

	  {
		  Binary m(n);

		  cout << "3. This is a copy of the first random number:" << endl;
		  print(m);
	  } // Here destructor of m is called

	  {
		  Binary o(std::move(n));
		  cout << "4. This is a move of the first random number:" << endl;
		  print(o);
	  }
  }

  if (false) { // Test assignment operator
	  Binary n;
	  random(n);
	  cout << "5. This is a random binary number:" << endl;
	  print(n);

	  Binary m;
	  random(m);
	  print(m);
	  m = n;
	  cout << "6. This should be a copy of the previous random number:" << endl;
	  print(m);

	  Binary o;
	  random(o);
	  o = std::move(n);
	  cout << "7. This should be a copy of the previous random number:" << endl;
	  print(o);
  }


  if (false) { // Test of shift left, shift right, bitwise or, bitwise and,
	// and stream redirection
	  Binary n;
	  random(n);
	  cout << "8. This is a random binary number:" << endl;
	  print(n);

	  {
		  Binary m = n<<static_cast<unsigned int>(5);
		  cout << "9. This is a shift left of the previous by 5" << endl;
		  print(m);

		  Binary o = m >> static_cast<unsigned int>(7);
		  cout << "10.This is a shift right of the previous by 7" << endl;
		  print(o);
	  }

	  Binary m;
	  random(m);
	  cout << "11.These are two random numbers:" << endl;
	  print(n);
	  print(m);
	  {
		  Binary o(m|n);
		  cout << "12.This is the bitwise or of the previous two:" << endl;
		  print (o);
	  }

	  {
		  Binary o(m&n);
		  cout << "13.This is the bitwise and of the previous two:" << endl;
		  print(o);
	  }

	  cout << "14.This is your implementation of stream redirection:" << endl;
	  cout << n << endl;
	  cout << m << endl;
  }

  if (false) { // Test constructor from int, int cast, op++, op+

	  int temp(rand()%2000);
	  Binary n(temp);
	  cout << "15. Converting " << temp;
	  temp = rand()%2000;
	  Binary m(temp);
	  cout << " and " << temp << " to binary:" << endl;
	  print(n);
	  print(m);

	  cout << "16.This is the conversion of the first to integer:" << endl;
	  cout << int(n) << endl;

	  {
		  Binary o = n+m;
		  cout << "17.This is their sum" << endl;
		  print(o);
	  }

	  {
		  n++;
		  cout << "18.This is the first incremented by 1:" << endl;
		  print(n);
	  }
  }
}

void print(Binary& n) {
	bool* arr = n.theArry();
	unsigned int size = n.size();

	cout << size << " bits" << endl;
	if (size) {
		for (unsigned int i=size-1 ; true ; --i) {
			if (arr[i]) {
				cout << 1;
			} else {
				cout << 0;
			}
			if (!i) {
				break;
			}
		}
		cout << endl;
	}
}

void random(Binary& n) {
	bool* arr = n.theArry();
	if (arr) {
		delete [] arr;
		arr=nullptr;
	}
	unsigned int size = rand() % 10;
	while (!size) {
		size = rand() % 10;
	}
	arr = new bool [size];
	for (unsigned int i=0 ; i<size-1 ; ++i) {
		arr[i] = rand() %2;
	}
	arr[size-1] = true;
	n.setPrivate(arr,size);
}

