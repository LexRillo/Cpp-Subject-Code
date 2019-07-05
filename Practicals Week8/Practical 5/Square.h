/*
 * Square.h
 *
 *  Created on: 23 Oct 2014
 *      Author: np183
 */

#ifndef SQUARE_H_
#define SQUARE_H_

#include "Rectangle.h"

// Squre inherits from Rectangle
// Override the necessary functions
class Square : public Rectangle {
public:
	// It should be impossible to create a square without additional info
	Square() {}
	Square(float side, const std::string& borderColor, bool fill=false, const std::string& fillColor="");
	Square(const Square& other) = default;
	Square(Square&& other) = default;
	virtual ~Square() override;

	// Choose which functions to implement here
};

#endif /* SQUARE_H_ */
