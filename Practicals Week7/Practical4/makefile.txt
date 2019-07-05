# Makefile

# the C++ compiler
CXX     = g++
CC      = $(CXX)

# options to pass to the compiler
CXXFLAGS = -std=c++11	-O0 -g3

All: all
all: main

main:	main.cpp Vector.o VectorTester.o LinkedList.o LinkedListTester.o
	$(CXX) $(CXXFLAGS) main.cpp Vector.o VectorTester.o LinkedList.o LinkedListTester.o -o main
		
Vector.o: Vector.cpp Vector.h
	$(CXX) $(CXXFLAGS) -c Vector.cpp -o Vector.o
	
VectorTester.o: VectorTester.cpp VectorTester.h Vector.h
	$(CXX) $(CXXFLAGS) -c VectorTester.cpp -o VectorTester.o
	
LinkedList.o: LinkedList.cpp LinkedList.h
	$(CXX) $(CXXFLAGS) -c LinkedList.cpp -o LinkedList.o
	
LinkedListTester.o: LinkedListTester.cpp LinkedListTester.h LinkedList.h
	$(CXX) $(CXXFLAGS) -c LinkedListTester.cpp -o LinkedListTester.o
	
deepclean: 
	rm -f *~ *.o main *.exe *.stackdump

clean:
	-rm -f *~ *.o *.stackdump

