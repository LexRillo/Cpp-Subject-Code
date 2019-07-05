/*
 * TesterBase.h
 *
 *  Created on: 31 Oct 2015
 *      Author: np183
 */

#ifndef TESTERBASE_H_
#define TESTERBASE_H_

#include <string>


class TesterBase {
public:
	TesterBase();
	~TesterBase();
protected:
	void errorOut_(const std::string& errMsg, unsigned int errBit=0);
	void testDone_(unsigned int errBit=0);
	bool errorSet_(unsigned int mask);
	bool testSet_(unsigned int mask);
	void passOut_(const std::string& passMsg);
	void func_(const std::string& funcname,const std::string& success="",const std::string& fail="");
	float randFloat_(unsigned int, unsigned int);
	std::string randString_(unsigned int);
	std::string randStringSpace_(unsigned int);
	char randChar_();
	char randCharSpace_();
private:
	int error_;
	int tested_;
	std::string funcname_;
};

#endif /* TESTERBASE_H_ */
