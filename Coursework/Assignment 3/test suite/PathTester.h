/*
 * PathTester.h
 *
 *  Created on: 29 Dec 2017
 *      Author: np183
 */

#ifndef PATHTESTER_H_
#define PATHTESTER_H_

#include "TesterBase.h"
#include "Path.h"

class PathTester : public TesterBase {
public:
	PathTester();
	~PathTester();

	void testConstruction();
	void testDim();
	void testVisited();
	void testComparison();
	void testOperatorPlus();
	void testOperatorMinus();
	void testLength();
	void testSpace();
	void testOperatorRedir();

private:
	Path::Direction randomDir_(bool legal=true);
	std::pair<int,int> applyDir_(std::pair<int,int>, Path::Direction);
	Path::Direction difference_(std::pair<int,int>, std::pair<int,int>);
	void extendRandomPath_(std::vector<Path::Direction>&, unsigned int size, bool legal=true);

	static constexpr unsigned int VERY_SMALL_ARRAY = 10;
	static constexpr unsigned int SMALL_ARRAY = 100;
	static constexpr unsigned int LARGE_ARRAY = 1000;
	static constexpr unsigned int VERY_LARGE_ARRAY = 1000000;
};

#endif /* PATHTESTER_H */
