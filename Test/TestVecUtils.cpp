#include <iostream>
#include <string>
#include "TestVecUtils.h"


void PrintAssertPassed(std::string functionName) {
	std::cout << functionName << " passed\n";
}

void Assert(float fTest, float fExpected, std::string functionName) {
	if (fTest == fExpected) {
		std::cout << functionName << " passed\n";
	}
	else {
		std::cout << functionName << " Expected " << fExpected << ", Got " << fTest << " FAILED\n";
	}
}
