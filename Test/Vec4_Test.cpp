#include "Vec4_Test.h"
#include "TestUtils.h"
#include "glm/glm/vec4.hpp"
#include "glm/glm/geometric.hpp"
#include "Vec4.h"
#include "Vec3.h"
#include "Vec2.h"

void TestVec4(void) {
	// Test empty constructor
	Vec4 empty;
	Vec4 expectedEmpty(0, 0, 0, 0);
	Assert<Vec4, Vec4, 4>(empty, expectedEmpty, "Vec4::Vec4()");

	// Test float constructor
	Vec4 floatCons(1, 2, 3, 4);

	// Test copy constructor
	Vec4 toCopy(1, 2, 3, 4);
	Vec4 copyOf(toCopy);
	Assert<Vec4, Vec4, 4>(toCopy, copyOf, "Vec4::Vec4(Vec4&)");

	// Test Vec2 constructor
	Vec2 v2(1, 2);
	Vec4 testVec2(v2);
	Vec4 expectedVec2(1, 2, 0, 0);
	Assert<Vec4, Vec4, 4>(testVec2, expectedVec2, "Vec4::Vec4(Vec2&)");

	// Test Vec3 constructor
	Vec3 v3(1, 2, 3);
	Vec4 testVec4(v3);
	Vec4 expectedVec4(1, 2, 3, 0);
	Assert<Vec4, Vec4, 4>(testVec4, expectedVec4, "Vec4::Vec4(Vec3&)");

	// Test Vec3 constructor with W
	float w = 4;
	Vec3 v3_w(1, 2, 3);
	Vec4 testVec4_w(v3_w, w);
	Vec4 expectedVec4_w(1, 2, 3, 4);
	Assert<Vec4, Vec4, 4>(testVec4_w, expectedVec4_w, "Vec4::Vec4(Vec3&, w)");

	// Test Length
	Vec4 testLengthVec(1, 2, 3, 4);
	float testLength = testLengthVec.Length();
	float expectedLength = sqrtf(1 + 2 * 2 + 3 * 3 + 4 * 4);
	Assert(testLength, expectedLength, "Vec4::Length()");

	// Test Normalize
	Vec4 testNorm(1, 2, 3, 4);
	testNorm.Normalize();
	Vec4 expectedNorm(1 / expectedLength, 2 / expectedLength, 3 / expectedLength, 4 / expectedLength);
	Assert<Vec4, Vec4, 4>(testNorm, expectedNorm, "Vec4::Normalize()");

	// Test Dot
	Vec4 testDotVec(1, 2, 3, 4);
	Vec4 dotWithVec(5, 6, 7, 8);
	float testDot = testDotVec.Dot(dotWithVec);
	glm::vec4 expectedDotVec(1, 2, 3, 4);
	glm::vec4 expectedDotWith(5, 6, 7, 8);
	float expectedDot = glm::dot(expectedDotVec, expectedDotWith);
	Assert(testDot, expectedDot, "Vec4::Dot()");

	// Test Unit
	Vec4 initUnit(1, 2, 3, 4);
	Vec4 testUnit = Vec4::Unit(initUnit);
	initUnit.Normalize();
	Assert<Vec4, Vec4, 4>(testUnit, initUnit, "Vec4::Unit()");

	// Test operator=
	Vec4 initEQ(1, 2, 3, 4);
	Vec4 testEQ;

	testEQ = initEQ;
	Assert<Vec4, Vec4, 4>(testEQ, initEQ, "Vec4::operator=");

	// Test operator+
	Vec4 add0(1, 2, 3, 4);
	Vec4 add1(5, 6, 7, 8);
	Vec4 addResult = add0 + add1;
	Vec4 expectedAdd(6, 8, 10, 12);
	Assert<Vec4, Vec4, 4>(addResult, expectedAdd, "Vec4::operator+");

	// Test operator+=
	add0 += add1;
	Assert<Vec4, Vec4, 4>(add0, expectedAdd, "Vec4::operator+=");

	// Test operator-
	Vec4 sub0(5, 6, 7, 8);
	Vec4 sub1(1, 2, 3, 4);
	Vec4 subResult = sub0 - sub1;
	Vec4 subExpected(4, 4, 4, 4);
	Assert<Vec4, Vec4, 4>(subResult, subExpected, "Vec4::operator-");

	// Test operator-=
	sub0 -= sub1;
	Assert<Vec4, Vec4, 4>(sub0, subExpected, "Vec4::operator-=");

	// Test operator*
	Vec4 mul0(1, 2, 3, 4);
	float mulScale = 2;
	Vec4 mulResult = mul0 * mulScale;
	Vec4 mulExpected(2, 4, 6, 8);
	Assert<Vec4, Vec4, 4>(mulResult, mulExpected, "Vec4::operator*");

	// Test operator*=
	mul0 *= mulScale;
	Assert<Vec4, Vec4, 4>(mul0, mulExpected, "Vec4::operator*=");

	// Test operator/
	Vec4 div0(2, 4, 6, 8);
	float divScale = 2;
	Vec4 divResult = div0 / divScale;
	Vec4 divExpected(1, 2, 3, 4);
	Assert<Vec4, Vec4, 4>(divResult, divExpected, "Vec4::operator/");

	// Test operator/=
	div0 /= divScale;
	Assert<Vec4, Vec4, 4>(div0, divExpected, "Vec4::operator/=");
}