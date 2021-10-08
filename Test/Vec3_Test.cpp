#include <iostream>
#include "TestUtils.h"
#include "Vec3_Test.h"
#include "glm/glm/geometric.hpp"
#include "glm/glm/vec3.hpp"
#include "Vec4.h"
#include "Vec3.h"
#include "Vec2.h"

void TestVec3(void) {
	// Test empty constructor
	Vec3 empty;
	Vec3 expectedEmpty(0, 0, 0);
	Assert<Vec3, Vec3, 3>(empty, expectedEmpty, "Vec3::Vec3()");

	// Test float constructor
	Vec3 floatCons(1, 2, 3);

	// Test copy constructor
	Vec3 toCopy(1, 2, 3);
	Vec3 copyOf(toCopy);
	Assert<Vec3, Vec3, 3>(toCopy, copyOf, "Vec3::Vec3(Vec3&)");

	// Test Vec2 constructor
	Vec2 v2(1, 2);
	Vec3 testVec2(v2);
	Vec3 expectedVec2(1, 2, 0);
	Assert<Vec3, Vec3, 3>(testVec2, expectedVec2, "Vec3::Vec3(Vec2&)");

	// Test Vec4 constructor
	Vec4 v4(1, 2, 3, 4);
	Vec3 testVec4(v4);
	Vec3 expectedVec4(1, 2, 3);
	Assert<Vec3, Vec3, 3>(testVec4, expectedVec4, "Vec3::Vec3(Vec4&)");

	// Test Length
	Vec3 testLengthVec(1, 2, 3);
	float testLength = testLengthVec.Length();
	float expectedLength = sqrtf(1 + 2 * 2 + 3 * 3);
	Assert(testLength, expectedLength, "Vec3::Length()");

	// Test Normalize
	Vec3 testNorm(1, 2, 3);
	testNorm.Normalize();
	Vec3 expectedNorm(1 / expectedLength, 2 / expectedLength, 3 / expectedLength);
	Assert<Vec3, Vec3, 3>(testNorm, expectedNorm, "Vec3::Normalize()");

	// Test Dot
	Vec3 testDotVec(1, 2, 3);
	Vec3 dotWithVec(4, 5, 6);
	float testDot = testDotVec.Dot(dotWithVec);
	glm::vec3 expectedDotVec(1, 2, 3);
	glm::vec3 expectedDotWith(4, 5, 6);
	float expectedDot = glm::dot(expectedDotVec, expectedDotWith);
	Assert(testDot, expectedDot, "Vec3::Dot()");

	// Test Cross
	Vec3 testCrossVec(1, 2, 3);
	Vec3 crossVecWith(4, 5, 6);
	Vec3 testResult = testCrossVec.Cross(crossVecWith);
	glm::vec3 expectedCrossVec(1, 2, 3);
	glm::vec3 expectedCrossVecWidth(4, 5, 6);
	glm::vec3 expectedResult = glm::cross(expectedCrossVec, expectedCrossVecWidth);
	Assert<Vec3, glm::vec3, 3>(testResult, expectedResult, "Vec3::Cross()");

	// Test Unit
	Vec3 initUnit(1, 2, 3);
	Vec3 testUnit = Vec3::Unit(initUnit);
	initUnit.Normalize();
	Assert<Vec3, Vec3, 3>(testUnit, initUnit, "Vec3::Unit()");

	// Test operator=
	Vec3 initEQ(1, 2, 3);
	Vec3 testEQ;

	testEQ = initEQ;
	Assert<Vec3, Vec3, 3>(testEQ, initEQ, "Vec3::operator=");

	// Test operator+
	Vec3 add0(1, 2, 3);
	Vec3 add1(4, 5, 6);
	Vec3 addResult = add0 + add1;
	Vec3 expectedAdd(5, 7, 9);
	Assert<Vec3, Vec3, 3>(addResult, expectedAdd, "Vec3::operator+");

	// Test operator+=
	add0 += add1;
	Assert<Vec3, Vec3, 3>(add0, expectedAdd, "Vec3::operator+=");

	// Test operator-
	Vec3 sub0(4, 5, 6);
	Vec3 sub1(1, 2, 3);
	Vec3 subResult = sub0 - sub1;
	Vec3 subExpected(3, 3, 3);
	Assert<Vec3, Vec3, 3>(subResult, subExpected, "Vec3::operator-");
	
	// Test operator-=
	sub0 -= sub1;
	Assert<Vec3, Vec3, 3>(sub0, subExpected, "Vec3::operator-=");

	// Test operator*
	Vec3 mul0(1, 2, 3);
	float mulScale = 2;
	Vec3 mulResult = mul0 * mulScale;
	Vec3 mulExpected(2, 4, 6);
	Assert<Vec3, Vec3, 3>(mulResult, mulExpected, "Vec3::operator*");

	// Test operator*=
	mul0 *= mulScale;
	Assert<Vec3, Vec3, 3>(mul0, mulExpected, "Vec3::operator*=");

	// Test operator/
	Vec3 div0(4, 4, 4);
	float divScale = 2;
	Vec3 divResult = div0 / divScale;
	Vec3 divExpected(2, 2, 2);
	Assert<Vec3, Vec3, 3>(divResult, divExpected, "Vec3::operator/");

	// Test operator/=
	div0 /= divScale;
	Assert<Vec3, Vec3, 3>(div0, divExpected, "Vec3::operator/=");
}