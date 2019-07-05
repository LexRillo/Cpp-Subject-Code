/*
 * Path.cpp
 *
 *  Created on: Nov 23, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */

#include <iostream>
#include <algorithm>
#include <exception>
#include <list>
#include <cmath>
#include <iterator>
#include "Path.h"

using std::ostream;
using std::pair;
using std::make_pair;
using std::vector;

// constructor
Path::Path()
{	
	myVisited.push_back(std::make_pair(0,0));
}

// copy constructor
Path::Path(const Path& other)
{
	directions = other.directions;
	myVisited = other.myVisited;
}

// move constructor
Path::Path(Path&& other)
{
	directions = other.directions;
	myVisited = other.myVisited;
	other.directions.clear();
	other.myVisited.clear();
}

// assignment operator
Path& Path::operator=(const Path& other)
{
	directions = other.directions;
	myVisited = other.myVisited;
	return *this;
}

// move operator
Path& Path::operator=(Path&& other)
{
	directions = other.directions;
	myVisited = other.myVisited;
	other.directions.clear();
	other.myVisited.clear();
	return *this;
}

// constructor from vector
Path::Path(std::vector<Direction> path)
{
	try{
		myVisited.push_back(std::make_pair(0,0));
		for(auto const& value: path) {
			move(value);
		}
	} catch(const std::exception& e){
		std::cout << "Element in the vector is not a valid Direction" << std::endl;	
	}
}

// destructor
Path::~Path()
{
}

pair<int,int> Path::current() const
{
	// get the last point pushed into the list
	return myVisited.back();
}

// move in the direction d
void Path::move(const Direction& d)
{
	// gets the current position, interprets the direction and moves in a carthesian plane. 
	// the inputted direction and resulting point are then stored.
	std::pair<int, int> myPosition = current();
	try{
		switch(d) {
			case N: myPosition.second += 1; break;
			case S: myPosition.second -= 1; break;
			case E: myPosition.first += 1; break;
			case W: myPosition.first -= 1; break;
			case NE: myPosition.first += 1;myPosition.second += 1; break;
			case NW: myPosition.first -= 1;myPosition.second += 1; break;
			case SE: myPosition.first += 1;myPosition.second -= 1; break;
			case SW: myPosition.first -= 1;myPosition.second -= 1; break;
		}
		directions.push_back(d);
		myVisited.push_back(myPosition);
	} catch(const std::exception& e){
		std::cout << "Direction not valid" << std::endl;	
	}
}

// equality operator
bool Path::operator==(const Path& other) const {
	if(directions == other.directions){
		return true;
	}
	return false;
}

// inequality operator
bool Path::operator!=(const Path& other) const {
	if(directions == other.directions){	
		return false;
	}
	return true;
}

// lesser operator
bool Path::operator<(const Path& other) const {
	if(this->directions.size() < other.directions.size()){
		
		std::list<Direction>::const_iterator it = other.directions.begin();
		int difference = other.directions.size() - this->directions.size();
    		std::advance(it, difference);
		std::list<Direction> newlist (other.directions.begin(),it);
		if(this->directions == newlist){
			return true;
		}else{
			return false;
		}
	}
	return false;
}

// lesser or equals operator
bool Path::operator<=(const Path& other) const {
	if(*this < other || *this == other){
		return true;
	}
	return false;
}

// more operator
bool Path::operator>(const Path& other) const {
	if(this->directions.size() > other.directions.size()){		
		std::list<Direction>::const_iterator it = this->directions.begin();
		int difference = this->directions.size() - other.directions.size();
    		std::advance(it, difference);
		std::list<Direction> newlist (this->directions.begin(),it);
		if(other.directions == newlist){
			return true;
		}else{
			return false;
		}
	}
	return false;
}

// more or equals operator
bool Path::operator>=(const Path& other) const {
	if(*this > other || *this == other){
		return true;
	}
	return false;
}

// addition operator
Path Path::operator+(const Path& other) const {
	Path res;
	// performs a move for every element on the "original" and "other" directions lists
	for(auto const& value: directions) {
		res.move(value);
	}
	for(auto const& value: other.directions) {
		res.move(value);
	}
	return res;
}

// subtraction operator
Path Path::operator-(const Path& other) const {
	// it calculates a "sublist" of the last elements of the largest list and compares that list to the smallest list.
	// if they are different then it triggers an exception. Otherwise it returns the remaineder of the biggest list.
	// (And this is where I regretted my decision of using lists)
	Path res;
	if(this->directions.size() >= other.directions.size()){
		
		std::list<Direction>::const_iterator it = this->directions.begin();
		int difference = this->directions.size() - other.directions.size();
    		std::advance(it, difference);
		std::list<Direction> newlist (it,this->directions.end());
		if(other.directions == newlist){
			std::list<Direction> rest (this->directions.begin(), it);
			for(auto const& value: rest) {
				res.move(value);
			}
		}else{
			throw std::exception();
		}		
	}else{
		std::list<Direction>::const_iterator it = other.directions.begin();
		int difference = other.directions.size() - this->directions.size();
    		std::advance(it, difference);
		std::list<Direction> newlist (it,other.directions.end());
		if(this->directions == newlist){
			std::list<Direction> rest (other.directions.begin(), it);
			for(auto const& value: rest) {
				Direction newValue;
				switch(value) {
					case N: newValue = S; break;
					case S: newValue = N; break;
					case E: newValue = W; break;
					case W: newValue = E; break;
					case NE: newValue = SW; break;
					case NW: newValue = SE; break;
					case SE: newValue = NW; break;
					case SW: newValue = NE; break;
				}
				res.move(newValue);
			}
		}else{
			throw std::exception();
		}
	}
	return res;
}

// minimums and maximums of X and Y
// they are calculated by exploring the myVisited list and getting the appropriate maximum or minimums
int Path::minX() const {
	int xmin = 0;
	for (std::list<std::pair<int, int>>::const_iterator iterator = myVisited.begin(), end = myVisited.end(); iterator != end; ++iterator) {
    		if(iterator->first < xmin){
			xmin = iterator->first;
		}
	}
	return xmin;
}

int Path::maxX() const {
	int xmax = 0;
	for (std::list<std::pair<int, int>>::const_iterator iterator = myVisited.begin(), end = myVisited.end(); iterator != end; ++iterator) {
    		if(iterator->first > xmax){
			xmax = iterator->first;
		}
	}
	return xmax;
}

int Path::minY() const {
	int ymin = 0;
	for (std::list<std::pair<int, int>>::const_iterator iterator = myVisited.begin(), end = myVisited.end(); iterator != end; ++iterator) {
    		if(iterator->second < ymin){
			ymin = iterator->second;
		}
	}
	return ymin;
}

int Path::maxY() const {
	int ymax = 0;
	for (std::list<std::pair<int, int>>::const_iterator iterator = myVisited.begin(), end = myVisited.end(); iterator != end; ++iterator) {
    		if(iterator->second > ymax){
			ymax = iterator->second;
		}
	}
	return ymax;
}

// compares the inputed point with the points present on the myVisited list
unsigned int Path::visited(int x, int y) const {
	int index = 0;
	for (std::list<std::pair<int, int>>::const_iterator iterator = myVisited.begin(), end = myVisited.end(); iterator != end; ++iterator, ++index) {
		if(iterator->first == x && iterator->second == y){
			return index;				
		}
	}
	throw std::exception();
}

int Path::length() const
{
	return myVisited.size();
}

// copies myVisited, gets the unique points (shortening the list) and then returns the size of the new list
int Path::space() const
{
	std::list<std::pair<int, int>> uniquePoints = myVisited;
	uniquePoints.sort();
	uniquePoints.unique();
	return uniquePoints.size();
}

//prints the carthesian representation of the points
ostream& operator<<(ostream& o, const Path& p) {
	// calcutes the length and height of the carthesian map
	enum Direction { N, S, E, W, NE, NW, SE, SW };
	int length = 3*(abs(p.maxX()) + abs(p.minX()))+1;
	int height = 3*(abs(p.maxY()) + abs(p.minY()))+1;
	
	// creating a matrix that represents the map and fills it with blank chars
	std::vector<std::vector<std::string>> board;
	for (int i = 0; i < height; ++i){
	    vector<std::string> row;
	    for (int j = 0; j < length; ++j){
		row.push_back(" ");
	    }
	    board.push_back(row);
	}
	
	// calculates the position of the origin (0,0) on the map and then "paints" the trajectory according to the directions on the list
	// the first point is painted with an s while the last is "painted" with an e
	int originY = 3*abs(p.minY());
	int originX = 3*abs(p.minX());
	board[originY][originX]='s';

	int currentPosX = originX;
	int currentPosY = originY;
	for(auto const& d : p.directions){
		switch(d) {
			case N: board[currentPosY+1][currentPosX] = '|'; 
				board[currentPosY+2][currentPosX] = '|'; 
				board[currentPosY+3][currentPosX] = 'o'; 
				currentPosY = currentPosY +3; break;
			case S: board[currentPosY-1][currentPosX] = '|';
				board[currentPosY-2][currentPosX] = '|'; 
				board[currentPosY-3][currentPosX] = 'o'; 
				currentPosY = currentPosY -3; break;
			case E: board[currentPosY][currentPosX+1] = '-'; 
				board[currentPosY][currentPosX+2] = '-'; 
				board[currentPosY][currentPosX+3] = 'o'; 
				currentPosX = currentPosX +3; break;
			case W: board[currentPosY][currentPosX-1] = '-';
				board[currentPosY][currentPosX-2] = '-';  
				board[currentPosY][currentPosX-3] = 'o'; 
				currentPosX = currentPosX-3; break;
			case NE:  board[currentPosY+1][currentPosX+1] = '/';
				board[currentPosY+2][currentPosX+2] = '/';
				board[currentPosY+3][currentPosX+3] = 'o'; 
				currentPosX = currentPosX+3; currentPosY = currentPosY+3; break;
			case NW:  board[currentPosY+1][currentPosX-1] = '\\'; 
				board[currentPosY+2][currentPosX-2] = '\\'; 
				board[currentPosY+3][currentPosX-3] = 'o'; 
				currentPosX = currentPosX-3; currentPosY = currentPosY+3; break; 
			case SE: board[currentPosY-1][currentPosX+1] = '\\';
				board[currentPosY-2][currentPosX+2] = '\\'; 
				board[currentPosY-3][currentPosX+3] = 'o'; 
				currentPosX = currentPosX+3; currentPosY = currentPosY-3; break;
			case SW: board[currentPosY-1][currentPosX-1] = '/';
				board[currentPosY-2][currentPosX-2] = '/'; 
				board[currentPosY-3][currentPosX-3] = 'o'; 
				currentPosX = currentPosX-3; currentPosY = currentPosY-3; break;
		}
	}
	board[currentPosY][currentPosX] = 'e';
	
	// the map is added to the stream with the neccessary spaces and then returned
	for(int i=0; i<length +2; i++){
		o << " ";
	}
	o << "\n";
	for (int i = height -1; i >= 0; --i){
		o << " ";
		for (int j = 0; j < length; ++j){
			o << board[i][j];
		}
		o << " \n";
	}
	for(int i=0; i<length +2; i++){
		o << " ";
	}
	o << "\n";
	return o;
}

/*
 * Path.h
 *
 *  Created on: Nov 23, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */
