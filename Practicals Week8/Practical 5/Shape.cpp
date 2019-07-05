/*
 * Shape.cpp
 *
 *  Created on: 23 Oct 2014
 *      Author: np183
 */

#include "Shape.h"

using std::string;
using std::ostream;

Shape::Shape(const std::string& borderColor,bool fill, const std::string& fillColor)
{
	// TODO: implement me
}

Shape::~Shape() {
	// TODO: implement me
}

string Shape::borderColor() const {
	// TODO: implement me
	return "";
}

void Shape::setBorderColor(const std::string& color) {
	// TODO: implement me
}

bool Shape::fill() const {
	// TODO: implement me
	return false;
}
void Shape::setFill(bool fill) {
	// TODO: implement me
}

string Shape::fillColor() const {
	// TODO: implement me
	return "";
}

void Shape::setFillColor(const std::string& color) {
	// TODO: implement me
}

float Shape::area() const {
	// TODO: implement me or remove me
	return 0.0;
}

float Shape::perimeter() const {
	// TODO: implement me or remove me
	return 0.0;
}

string Shape::toString() const {
	// TODO: implement me or remove me
	return "";
}

std::ostream& operator<<(std::ostream& o, const Shape& s) {
	// TODO: implement me
	return o;
}
