# Makefile

# the C++ compiler
CXX     = g++
CC      = $(CXX)

# options to pass to the compiler
CXXFLAGS = -std=c++11	-O0 -g3

All: all
all: main

main:	main.cpp Vector.o VectorTester.o 
	$(CXX) $(CXXFLAGS) main.cpp Vector.o VectorTester.o -o main
		
Vector.o: Vector.cpp Vector.h
	$(CXX) $(CXXFLAGS) -c Vector.cpp -o Vector.o
	
VectorTester.o: VectorTester.cpp VectorTester.h Vector.h
	$(CXX) $(CXXFLAGS) -c VectorTester.cpp -o VectorTester.o
	
deepclean: 
	rm -f *~ *.o main *.exe *.stackdump

clean:
	-rm -f *~ *.o *.stackdump

