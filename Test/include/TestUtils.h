#pragma once
#include <string>
#include <iostream>

void PrintAssertPassed(std::string functionName);
void Assert(float test, float expected, std::string functionName);

template <class T, class U, int N, int J>
void PrintAssertFailedMat(T& matTest, U& matExpected, std::string functionName) {
	std::cout << functionName << " Expected ( ";
	for (int i = 0; i < N; ++i) { 
		for (int j = 0; j < J; ++j) {
			std::cout << matExpected[i][j] << "  ";
		}
		std::cout << "\n";
	}
	std::cout << " ), Got (";
	for (int i = 0; i < N; ++i) { 
		for (int j = 0; j < J; ++j) {
			std::cout << matTest[i][j] << "  ";
		}
		std::cout << "\n";
	}
	std::cout << " )\n";
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
	std::cout << functionName << " Expected (";
	for (int i = 0; i < N - 1; ++i) { std::cout << vecExpected[i] << ", "; }
	std::cout << vecExpected[N - 1] << "), Got (";
	for (int i = 0; i < N - 1; ++i) { std::cout << vecTest[i] << ", "; }
	std::cout << vecTest[N - 1] << ") FAILED\n";
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
