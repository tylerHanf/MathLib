#pragma once
#include <iostream>
#include <string>
#include "glm/glm/common.hpp"
#include "glm/glm/vec2.hpp"

void PrintAssertPassed(std::string functionName);
void Assert(float fTest, float fExpected, std::string functionName);

template <class T, int N>
void PrintAssertFailedVec(T& vecTest, T& vecExpected, std::string functionName) {
	std::cout << functionName << " Expected (";
	for (int i = 0; i < N - 1; ++i) { std::cout << vecExpected[i] << ", "; }
	std::cout << vecExpected[N - 1] << "), Got (";
	for (int i = 0; i < N - 1; ++i) { std::cout << vecTest[i] << ", "; }
	std::cout << vecTest[N - 1] << ") FAILED\n";
}

template <class T, class U, int N>
void PrintAssertFailedVec(T& vecTest, U& vecExpected, std::string functionName) {
	std::cout << functionName << " Expected (";
	for (int i = 0; i < N - 1; ++i) { std::cout << vecExpected[i] << ", "; }
	std::cout << vecExpected[N - 1] << "), Got (";
	for (int i = 0; i < N - 1; ++i) { std::cout << vecTest[i] << ", "; }
	std::cout << vecTest[N - 1] << ") FAILED\n";
}

template <class T, int N>
void Assert(T& vecTest, T& vecExpected, std::string functionName) {
	bool passed = true;
	for (int i = 0; i < N; ++i) {
		if (vecTest[i] != vecExpected[i]) {
			passed = false;
			break;
		}
	}
	if (passed) {
		PrintAssertPassed(functionName);
	}
	else {
		PrintAssertFailedVec<T, N>(vecTest, vecExpected, functionName);
	}
}

template <class T, class U, int N>
void Assert(T& vecTest, U& vecExpected, std::string functionName) {
	bool passed = true;
	for (int i = 0; i < N; ++i) {
		if (vecTest[i] != vecExpected[i]) {
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
