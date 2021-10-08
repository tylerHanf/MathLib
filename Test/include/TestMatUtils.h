#pragma once
#include <iostream>
#include <string>
#include "glm/glm/common.hpp"
#include "glm/glm/mat3x3.hpp"

template <class T, int N>
void PrintAssertFailedMat(T& matTest, T& matExpected, std::string functionName) {
	std::cout << functionName << " Expected (";
	for (int i = 0; i < N - 1; ++i) { std::cout << matExpected[i] << ", "; }
	std::cout << matExpected[N - 1] << "), Got (";
	for (int i = 0; i < N - 1; ++i) { std::cout << matTest[i] << ", "; }
	std::cout << matTest[N - 1] << ") FAILED\n";
}

template <class T, class U, int N>
void PrintAssertFailedMat(T& matTest, U& matExpected, std::string functionName) {
	std::cout << functionName << " Expected (";
	for (int i = 0; i < N - 1; ++i) { std::cout << matExpected[i] << ", "; }
	std::cout << matExpected[N - 1] << "), Got (";
	for (int i = 0; i < N - 1; ++i) { std::cout << matTest[i] << ", "; }
	std::cout << matTest[N - 1] << ") FAILED\n";
}

template <class T, int N>
void Assert(T& matTest, T& matExpected, std::string functionName) {
	bool passed = true;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (matTest[i][j] != matExpected[i][j]) {
				passed = false;
				break;
			}
		}
	}
	if (passed) {
		PrintAssertPassed(functionName);
	}
	else {
		PrintAssertFailedMat<T, N>(matTest, matExpected, functionName);
	}
}

template <class T, class U, int N>
void Assert(T& matTest, U& matExpected, std::string functionName) {
	bool passed = true;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (matTest[i][j] != matExpected[i][j]) {
				passed = false;
				break;
			}
		}
	}
	if (passed) {
		PrintAssertPassed(functionName);
	}
	else {
		PrintAssertFailedMat<T, U, N>(matTest, matExpected, functionName);
	}
}
