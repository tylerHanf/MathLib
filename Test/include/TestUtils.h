#pragma once
#include <string>
#include <iostream>
#include "Logger.h"

void PrintAssertPassed(std::string functionName);
void Assert(float test, float expected, std::string functionName);

template <class T, class U, int N, int J>
void PrintAssertFailedMat(T& matTest, U& matExpected, std::string functionName) {
	if (N == 3)
		Logger::LogPrint("%s FAILED\nExpected: %m Got: %m", functionName.c_str(), matExpected, matTest);
	else
		Logger::LogPrint("%s FAILED\nExpected: %M Got: %M", functionName.c_str(), matExpected, matTest);
}

template <class T, class U, int N, int J>
void Assert(T& matTest, U& matExpected, std::string functionName) {
	bool passed = true;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < J; ++j) {
			if (fabs(matTest[i][j] - matExpected[i][j]) > 1e-14) {
				passed = false;
				break;
			}
		}
		if (!passed)
			break;
	}
	if (passed) {
		PrintAssertPassed(functionName);
	}
	else {
		PrintAssertFailedMat<T, U, N, J>(matTest, matExpected, functionName);
	}
}

template <class T, class U, int N>
void PrintAssertFailedVec(T& vecTest, U& vecExpected, std::string functionName) {
	Logger::LogPrint("%s FAILED\n Expected:", functionName.c_str());
	if (N == 2)
		Logger::LogPrint("%2 Got: %2", vecExpected, vecTest);
	else if (N == 3)
		Logger::LogPrint("%3 Got: %3", vecExpected, vecTest);
	else if (N == 4)
		Logger::LogPrint("%4 Got: %4", vecExpected, vecTest);
}

template <class T, class U, int N>
void Assert(T& vecTest, U& vecExpected, std::string functionName) {
	bool passed = true;
	for (int i = 0; i < N; ++i) {
		if (fabs(vecTest[i] - vecExpected[i]) > 1e-14) {
			passed = false;
			break;
		}
	}
	if (passed) {
		PrintAssertPassed(functionName);
	}
	else {
		PrintAssertFailedVec<T, U, N>(vecTest, vecExpected, functionName);
	}
}
