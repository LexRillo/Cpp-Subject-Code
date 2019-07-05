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
#include <exception>
#include "Path.h"

using std::ostream;
using std::pair;
using std::make_pair;
using std::vector;

Path::Path()
{
}

Path::Path(const Path& other)
{
}

Path::Path(Path&& other)
{
}

Path& Path::operator=(const Path& other)
{
	return *this;
}

Path& Path::operator=(Path&& other)
{
	return *this;
}

Path::Path(std::vector<Direction> path)
{
}

Path::~Path()
{
}

pair<int,int> Path::current() const
{
	return make_pair(0,0);
}

void Path::move(const Direction& d)
{
}

bool Path::operator==(const Path& other) const {
	return false;
}

bool Path::operator!=(const Path& other) const {
	return false;
}

bool Path::operator<(const Path& other) const {
	return false;
}

bool Path::operator<=(const Path& other) const {
	return false;
}

bool Path::operator>(const Path& other) const {
	return false;
}

bool Path::operator>=(const Path& other) const {
	return false;
}

Path Path::operator+(const Path& other) const {
	Path res;
	return res;
}

Path Path::operator-(const Path& other) const {
	Path res;
	return res;
}

int Path::minX() const {
	return 0;
}

int Path::maxX() const {
	return 0;
}

int Path::minY() const {
	return 0;
}

int Path::maxY() const {
	return 0;
}

unsigned int Path::visited(int x, int y) const {
	return 0;
}

int Path::length() const
{
	return 0;
}

int Path::space() const
{
	return 0;
}

ostream& operator<<(ostream& o, const Path& p) {
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
