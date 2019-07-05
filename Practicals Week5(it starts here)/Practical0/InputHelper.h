#ifndef INPUTHELPER_H_
#define INPUTHELPER_H_


// This function reads a line from standard input.
// If the line is empty it tries again.
// If the line contains exactly one unsigned int it returns true and sets
// the value of the reference input to the value.
// Otherwise it returns false and does not change the reference.
bool readOneUnsignedInt(unsigned int &input);

// This function reads a line from standard input.
// If the line is empty it tries again.
// If the line contains at most the upper limit characters all in the (null terminated)
// string of allowed characters it returns the number of characters it read and sets
// the char array's first part to this input.
// Otherwise it returns 0 and does not change the array.
unsigned int readCharacters(char* input, unsigned int limit, const char* allowed);

#endif /* INPUTHELPER_H_ */
