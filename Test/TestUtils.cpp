#include "TestUtils.h"

void PrintAssertPassed(std::string functionName) {
	std::cout << functionName << " passed\n";
}

void Assert(float test, float expected, std::string functionName) {
	if (test == expected) {
		std::cout << functionName << " passed" << std::endl;
	}
	else {
		std::cout << functionName << " expected: " << expected << " got: " << test << " FAILED" << std::endl;
	}
}