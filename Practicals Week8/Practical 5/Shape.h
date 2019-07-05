/*
 * Shape.h
 *
 *  Created on: 23 Oct 2014
 *      Author: np183
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include <iosfwd>
#include <string>

// This is the base class for all the shapes
// Every shape has a boder color (string)
// It is either filled or unfilled and in the case
// that it is filled it also has a fill color (string).
//
// All shapes support functions setting and checking the
// colors and whether or not they are filled.
// Also, it is possible to check the area of a shape and
// its perimeter.
// It is also possible to convert it to a string and to
// redirect it into a stream.
// Choose which functions should be virtual and where
// should they be implemented
class Shape {
public:
	// It should be impossible to create a shape without additional details
	// I am leaving this function here so that compilation of the bare
	// version I am giving students will work
	Shape() {}

	// Constructor initializing all these details
	Shape(const std::string& borderColor,bool fill=false, const std::string& fillColor="");

	// Copy/Move constructors (as there are no pointers here
	// you can just use the standard implementations by the compiler)
	Shape(const Shape&) = default;
	Shape(Shape&&) = default;

	// Virtual destructor - create your own tests
	// to check that the destructor behaves correctly
	virtual ~Shape();

	// Setter and getter for border color
	std::string borderColor() const;
	void setBorderColor(const std::string& color);

	// Setter and getter for fill
	bool fill() const;
	void setFill(bool);

	// Setter and getter for fill color
	std::string fillColor() const;
	void setFillColor(const std::string& color);

	// Functions for computing the area, perimeter, and to string
	float area() const;
	float perimeter() const;

	// The right way to represent a shape is as follows.
	// For Rectangle:
        // Rectangle of width X and height Y (border: COLOR)
        // or
        // Rectangle of width X and height Y (border: COLOR, fill: COLOR)
	// For Square:
        // Square with side X (...)
        // The parentheses behave as in Rectangle
	// For Circle:
	// Circle of radius X (...)
	// The parentheses behave as in Rectangle
	std::string toString() const;

	friend std::ostream& operator<<(std::ostream&, const Shape&);
private:
	// TODO:
	// Add private members.

};

#endif /* SHAPE_H_ */
