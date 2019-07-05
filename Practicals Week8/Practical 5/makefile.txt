# Makefile

# the C++ compiler
CXX     = g++
CC      = $(CXX)

# options to pass to the compiler
CXXFLAGS = -std=c++11	-O0 -g3

All: all
all: main

main:	main.cpp ShapeTester.o Shape.o Circle.o Rectangle.o Square.o
	$(CXX) $(CXXFLAGS) main.cpp Shape.o Circle.o Rectangle.o Square.o ShapeTester.o -o main
		
ShapeTester.o: ShapeTester.cpp ShapeTester.h Shape.h
	$(CXX) $(CXXFLAGS) -c ShapeTester.cpp -o ShapeTester.o

Shape.o: Shape.cpp Shape.h
	$(CXX) $(CXXFLAGS) -c Shape.cpp -o Shape.o

Circle.o: Circle.cpp Circle.h Shape.h
	$(CXX) $(CXXFLAGS) -c Circle.cpp -o Circle.o

Rectangle.o: Rectangle.cpp Rectangle.h Shape.h
	$(CXX) $(CXXFLAGS) -c Rectangle.cpp -o Rectangle.o

Square.o: Square.cpp Square.h Rectangle.h Shape.h
	$(CXX) $(CXXFLAGS) -c Square.cpp -o Square.o

	
deepclean: 
	rm -f *~ *.o main *.exe *.stackdump

clean:
	-rm -f *~ *.o *.stackdump

