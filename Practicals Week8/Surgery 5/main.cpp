#include <iostream>
#include "Animal.h"

using std::cout;
using std::endl;

class A {
public:
	A() { cout << "A" << endl; }
	virtual ~A() { cout << "~A"  << endl; }
};

class B : public A {
public:
	B() { cout << "B" << endl; }
	~B() override { cout << "~B" << endl; }
};

class C : public B {
public:
	C() : ptr(new int[1000]) { cout << "C" << endl; }
	~C() override { delete [] ptr; cout << "~C" << endl; }
private:
	int* ptr;
};

void callDescription(Animal* a) {
  a->description();
}

int main() {
	if (false) {
		A* a = new A;
		A* b = new B;
		B* c = new C;

		delete a;
		delete b;
		delete c;

	}
	if (true) {
	  // Animal a;
	  //		TwoLegs b('(',')');
	  //	Bird c;
	  Animal* animals[2];
	  animals[0] = new Falcon;
	  animals[1] = new Penguin;

		//cout << a.name() << endl;
		//cout << b.name() << " " << b.walk() << endl;
	  TwoLegs* t= dynamic_cast<TwoLegs*>(animals[0]);
	  cout << animals[0]->name() << " " << t->walk() << endl;
	  //	  cout << p.name() << " " << p.walk() << endl;
		//cout << "I am a " << f.name() << ". I walk like " << f.walk() << ". And my sound is " << f.sound() <<endl;
		//cout << "I am a " << p.name() << ". I walk like " << p.walk() << ". And my sound is " << p.sound() <<endl;

		//a.description();
		//b.description();
	  //	p.description();
	  //	f.description();
		//p.description();
	  for (int i=0 ; i<2 ; ++i) {
	    callDescription(animals[i]);
	    animals[i]->description();
	  }

	  for (int i=0 ; i<2 ; ++i) {
	    delete animals[i];
	  }
	}
}
