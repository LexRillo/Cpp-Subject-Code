/*
 * Vector.cpp
 */

#include "Vector.h"

using std::string;
using std::ostream;
using std::istream;

Vector::Vector()
{
  // TODO: implement me
}

Vector::Vector(int size, int val)
{
  // TODO: implement me
}

Vector::Vector(const Vector& other)
{
  // TODO: implement me
}

Vector::Vector(Vector&& other)
{
  // TODO: implement me
}

Vector::~Vector() {
  // TODO: implement me
}

void Vector::push_back(int val) {
  // TODO: implement me
}

int Vector::operator[](int loc) const {
  // TODO: implement me
  return 0;
}

int& Vector::operator[](int loc) {
  // TODO: implement me
}

Vector& Vector::operator=(const Vector& other) {
  // TODO: implement me
  return *this;
}

Vector& Vector::operator=(Vector&& other) {
  // TODO: implement me
  return *this;

}

int Vector::size() const {
  // TODO: implement me
  return -1;
}

bool Vector::empty() const {
  // TODO: implement me
  return false;
}

void Vector::clear() {
  // TODO: implement me
}


string Vector::toString(unsigned int width, char fill) const {
  // TODO: implement me
  return "";
}

ostream& operator<<(ostream& os, const Vector& v) {
  // TODO: implement me
  return os;
}

istream& operator>>(istream& is, Vector& v) {
  // TODO: implement me
  return is;
}

