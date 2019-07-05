#include <cstdlib>
#include <iostream>
#include <string>
#include "InputHelper.h"

using std::string;
using std::cin;


bool readOneUnsignedInt(unsigned int &input) {
	string temp;
	while (temp.length() == 0) {
		getline(cin, temp);
	}
	if (temp.find_first_not_of("0123456789") != string::npos) {
		return false;
	}
	char **ptr{ nullptr };
	input = std::strtoul(temp.c_str(), ptr, 0);

	return true;
}

unsigned int readCharacters(char* input, unsigned int limit, const char* allowed) {
	string temp;
	while (temp.length() == 0) {
		getline(cin,temp);
	}
	if (temp.length() > limit || temp.find_first_not_of(allowed) != string::npos) {
		return false;
	}
	for (unsigned int i=0 ; i<temp.length() && i<limit ; ++i)  {
		input[i] = temp[i];
	}
	return temp.length();
}
