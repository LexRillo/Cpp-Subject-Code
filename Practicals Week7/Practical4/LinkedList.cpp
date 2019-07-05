/*
 * LinkedList.cpp
 */

#include "LinkedList.h"

using std::string;
using std::ostream;
using std::istream;

LinkedList::LinkedList()
{
  // TODO: implement me
}

LinkedList::LinkedList(const LinkedList& other)
{
  // TODO: implement me
}

LinkedList::LinkedList(LinkedList&& other)
{
  // TODO: implement me
}

LinkedList::~LinkedList() {
  // TODO: implement me
}

void LinkedList::push_back(int val) {
  // TODO: implement me
}

void LinkedList::push_front(int val) {
  // TODO: implement me
}

void LinkedList::pop_back() {
  // TODO: implement me
}

void LinkedList::pop_front() {
  // TODO: implement me
}

int LinkedList::first() const {
  // TODO: implement me
	return 0;
}

int LinkedList::last() const {
  // TODO: implement me
	return 0;
}

LinkedList& LinkedList::operator=(const LinkedList& other) {
  // TODO: implement me
	return *this;
}

LinkedList& LinkedList::operator=(LinkedList&& other) {
  // TODO: implement me
  return *this;
}

int LinkedList::size() const {
  // TODO: implement me
  return -1;
}

bool LinkedList::empty() const {
  // TODO: implement me
  return false;
}

void LinkedList::clear() {
  // TODO: implement me
}

string LinkedList::toString(unsigned int width, char fill) const {
  // TODO: implement me
	return "";
}

ostream& operator<<(ostream& os, const LinkedList& l) {
  // TODO: implement me
  return os;
}

istream& operator>>(istream& is, LinkedList& l) {
  // TODO: implement me
	return is;
}

