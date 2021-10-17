#include "Quaternion_Test.h"
#include "Quaternion.h"
#include "TestUtils.h"
#include "glm/glm/gtx/quaternion.hpp"

void TestQuaternion(void) {
	Quaternion arg0(1, 2, 3, 4);
	glm::quat arg0_glm(1, 2, 3, 4);

	// Test Empty Constructor
	Quaternion testEmptyQuat;
	Quaternion expectedEmptyQuat(1, 0, 0, 0);
	Assert<Quaternion, Quaternion, 4>(testEmptyQuat, expectedEmptyQuat, "Quaternion::Quaternion()");

	// Test w,x,y,z constructor
	Quaternion testBasic(1, 2, 3, 4);
	Quaternion expectedBasic;
	expectedBasic[0] = 1;
	expectedBasic[1] = 2;
	expectedBasic[2] = 3;
	expectedBasic[3] = 4;
	Assert<Quaternion, Quaternion, 4>(testBasic, expectedBasic, "Quaternion::Quaterion(w, x, y, z)");

	// Test Vec3 constructor
	Quaternion testVec3Pos(Vec3(1, 2, 3));
	Quaternion expectedVec3(0, 1, 2, 3);
	Assert<Quaternion, Quaternion, 4>(testVec3Pos, expectedVec3, "Quaternion::Quaternion(Vec3&)");

	// Test Copy Constructor
	Quaternion testCopyCons(arg0);
	Assert<Quaternion, Quaternion, 4>(testCopyCons, arg0, "Quaternion::Quaternion(Quaternion&)");

	// Test Theta, Vec3 Constructor
	Quaternion testThetaVec3(0.5, Vec3(1, 0, 0));
	Quaternion expectedThetaVec3(cosf(0.5 / 2), sinf(0.5 / 2), 0, 0);
	Assert<Quaternion, Quaternion, 4>(testThetaVec3, expectedThetaVec3, "Quaternion::Quaternion(float, Vec3&)");

	// Test Conjugate
	Quaternion testConjugate = arg0.Conjugate();
	glm::quat expectedConjugate = glm::conjugate(arg0_glm);
	Assert<Quaternion, glm::quat, 4>(testConjugate, expectedConjugate, "Quaternion::Conjugate()");

	// Test Dot
	float testDot = arg0.Dot(Quaternion(5, 6, 7, 8));
	float expectedDot = glm::dot(arg0_glm, glm::quat(5, 6, 7, 8));
	Assert(testDot, expectedDot, "Quaternion::Dot()");

	// Test Length
	float testLength = arg0.Length();
	float expectedLength = glm::length(arg0_glm);
	Assert(testLength, expectedLength, "Quaternion::Length()");

	// Test Length2
	float testLength2 = arg0.Length2();
	float expectedLength2 = glm::length2(arg0_glm);
	Assert(testLength2, expectedLength2, "Quaternion::Length2()");

	// Test Inverse
	Quaternion testInverse = arg0.Inverse();
	glm::quat expectedInverse = glm::inverse(arg0_glm);
	Assert<Quaternion, glm::quat, 4>(testInverse, expectedInverse, "Quaternion::Inverse()");

	// Test Rotate
	Quaternion rotateBy(0.5, Vec3(1, 0, 0));
	Vec3 testRotate = rotateBy.Rotate(Vec3(1, 0, 0));
	glm::quat expectedRotateBy(0.5, glm::vec3(1, 0, 0));
	glm::vec3 expectedRotate = glm::rotate(expectedRotateBy, glm::vec3(1, 0, 0));
	Assert<Vec3, glm::vec3, 3>(testRotate, expectedRotate, "Quaternion::Rotate()");

	// Test Unit
	Quaternion testUnit = Quaternion::Unit(arg0);
	glm::quat expectedUnit = glm::normalize(arg0_glm);
	Assert<Quaternion, glm::quat, 4>(testUnit, expectedUnit, "Quaternion::Unit()");

	// Test operator*
	Quaternion testMul = arg0 * Quaternion(5, 6, 7, 8);
	glm::quat expectedMul = arg0_glm * glm::quat(5, 6, 7, 8);
	Assert<Quaternion, glm::quat, 4>(testMul, expectedMul, "Quaternion::operator*");

	// Test operator* scale
	Quaternion testMulScale = arg0 * 2;
	Quaternion expectedMulScale(2, 4, 6, 8);
	Assert<Quaternion, Quaternion, 4>(testMulScale, expectedMulScale, "Quaternion::operator*");

	// Test operator*= 
	Quaternion testMulEq = arg0;
	testMulEq *= arg0;
	Quaternion expectedTestMulEq = arg0 * arg0;
	Assert<Quaternion, Quaternion, 4>(testMulEq, expectedTestMulEq, "Quaternion::operator*=");

	// Test operator*= scale
	Quaternion testMulScaleEq = arg0;
	testMulScaleEq *= 2;
	Quaternion expectedMulScaleEq = arg0 * 2;
	Assert<Quaternion, Quaternion, 4>(testMulScaleEq, expectedMulScaleEq, "Quaternion::operator*=");

	// Test operator+
	Quaternion testAdd = arg0 + arg0;
	Quaternion expectedAdd = arg0 * 2;
	Assert<Quaternion, Quaternion, 4>(testAdd, expectedAdd, "Quaternion::operator+");

	// Test operator+=
	Quaternion testAddEq = arg0;
	testAddEq += arg0;
	Assert<Quaternion, Quaternion, 4>(testAddEq, expectedAdd, "Quaternion::operator+=");
}