#include <iostream>
#include <string>
#include "TestUtils.h"
#include "glm/glm/vec2.hpp"
#include "glm/glm/geometric.hpp"
#include "Vec2_Test.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

void TestVec2(void) {
	// Test empty constructor
	Vec2 emptyConstructor;
	glm::vec2 emptyConstructor_expected;
	Assert<Vec2, glm::vec2, 2>(emptyConstructor, emptyConstructor_expected, "Vec2()");

	// Test x,y constructor
	Vec2 XYconstructor(1.,1.);
	glm::vec2 x_y_expected(1., 1.);
	Assert<Vec2, glm::vec2, 2>(XYconstructor, x_y_expected, "Vec2(x, y)");

	// Test copy constructor
	Vec2 orig(3, 4);
	Vec2 copy(orig);
	Assert<Vec2, Vec2, 2>(orig, copy, "Vec2(Vec2&)");

	// Test from Vec3 constructor
	Vec3 v3(1, 2, 3);
	Vec2 fromV3(v3);
	Vec2 vec3_expected(1, 2);
	Assert<Vec2, Vec2, 2>(fromV3, vec3_expected, "Vec2(Vec3&)");

	// Test from Vec4 constructor
	Vec4 v4(3, 4, 3, 4);
	Vec2 fromV4(v4);
	Vec2 vec4_expected(3, 4);
	Assert<Vec2, Vec2, 2>(fromV4, vec4_expected, "Vec2(Vec4&)");

	// Test Length
	Vec2 testLength_vec(1, 1);
	float test_length = testLength_vec.Length();
	float length = sqrtf(2);
	Assert(test_length, length, "Vec2::Length()");

	// Test Dot
	Vec2 testDot0(2, 2);
	Vec2 testDot1(3, 3);
	float testResult = testDot0.Dot(testDot1);
	glm::vec2 expectedDot0(2, 2);
	glm::vec2 expectedDot1(3, 3);
	float expectedResult = glm::dot(expectedDot0, expectedDot1);
	Assert(testResult, expectedResult, "Vec2::Dot()");

	// Test Normalize
	float l = sqrtf(1 + 4);
	Vec2 unNormal(1, 2);
	unNormal.Normalize();
	Vec2 normal(1 / l, 2 / l);
	Assert<Vec2, Vec2, 2>(unNormal, normal, "Vec2::Normalize(1,2)");

	// Test Unit
	Vec2 nonUnit(1, 2);
	Vec2 attemptedUnit = Vec2::Unit(nonUnit);
	float unitResult = attemptedUnit.Length();
	nonUnit.Normalize();
	float unitExpected = nonUnit.Length();
	Assert(unitResult, unitExpected, "Vec2::Unit(Vec2(1,2))");

	// Test operator= 
	Vec2 first(1, 1);
	Vec2 copied;
	copied = first;
	Assert<Vec2, Vec2, 2>(first, copied, "Vec2::operator=");

	// Test operator+
	Vec2 a(1, 1);
	Vec2 b(2, 2);
	Vec2 aPlusB = a + b;
	Vec2 expected_plus(3, 3);
	Assert<Vec2, Vec2, 2>(aPlusB, expected_plus, "Vec2::operator+");

	// Test operator+=
	a += b;
	Assert<Vec2, Vec2, 2>(a, aPlusB, "Vec2::operator+=");

	// Test operator-
	Vec2 subFrom(3, 3);
	Vec2 subBy(1, 1);
	Vec2 subResult = subFrom - subBy;
	Vec2 sub_expected(2, 2);
	Assert<Vec2, Vec2, 2>(subResult, sub_expected, "Vec2::operator-");

	// Test operator-=
	subFrom -= subBy;
	Assert<Vec2, Vec2, 2>(subFrom, subResult, "Vec2::operator-=");

	// Test operator*
	Vec2 mul(2, 2);
	float mulBy = 3;
	Vec2 mulResult = mul * 3;
	Vec2 mulExpected(6, 6);
	Assert<Vec2, Vec2, 2>(mulResult, mulExpected, "Vec2::operator*");

	// Test operator*=
	mul *= mulBy;
	Assert<Vec2, Vec2, 2>(mul, mulResult, "Vec2::operator*=");

	// Test operator/
	Vec2 div(4, 4);
	float divBy = 2;
	Vec2 divResult = div / divBy;
	Vec2 divExpected(2, 2);
	Assert<Vec2, Vec2, 2>(divResult, divExpected, "Vec2::operator/");

	// Test operator/=
	div /= divBy;
	Assert<Vec2, Vec2, 2>(div, divResult, "Vec2::operator/=");
}
