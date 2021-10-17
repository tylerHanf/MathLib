#include "TestUtils.h"
#include "Mat4_Test.h"
#include "Mat4.h"
#include "glm/glm/mat4x4.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/matrix_access.hpp"
#include "glm/glm/gtc/quaternion.hpp"

void TestMat4() {
	Mat4 arg0(1, 0, 0, 0,
			  0, 1, 0, 0,
			  0, 0, 1, 0,
			  0, 0, 0, 1);

	Mat4 arg1( 1,  2,  3,  4,
			   5,  6,  7,  8,
			   9, 10, 11, 12,
			  13, 14, 15,  1);

	glm::mat4 arg0_glm(1, 0, 0, 0,
			           0, 1, 0, 0,
			           0, 0, 1, 0,
			           0, 0, 0, 1);

	glm::mat4 arg1_glm( 1,  2,  3,  4,
					    5,  6,  7,  8,
						9, 10, 11, 12,
					   13, 14, 15,  1);

	// Test empty constructor
	Mat4 test_empty;
	Assert<Mat4, Mat4, 4, 4>(test_empty, arg0, "Mat4::Mat4()");

	// Test basic constructor
	Mat4 test_basic( 1,  2,  3,  4,
					 5,  6,  7,  8,
					 9, 10, 11, 12,
				    13, 14, 15,  1);
	Assert<Mat4, glm::mat4, 4, 4>(test_basic, arg1_glm, "Mat4::Mat4(x, y, z...)");

	// Test Vec3 constructor
	Mat4 test_vec3(Vec3(1, 2, 3));
	Mat4 expected_vec3;
	expected_vec3[3] = Vec4(1, 2, 3, 1);
	Assert<Mat4, Mat4, 4, 4>(test_vec3, expected_vec3, "Mat4::Mat4(vec3)");

	// Test Vec4 constructor
	Mat4 test_vec4(Vec4(1, 2, 3, 1));
	Mat4 expected_vec4;
	expected_vec4[3][0] = 1;
	expected_vec4[3][1] = 2;
	expected_vec4[3][2] = 3;
	expected_vec4[3][3] = 1;

	Assert<Mat4, Mat4, 4, 4>(test_vec4, expected_vec4, "Mat4::Mat4(vec4)");

	// Test Quaternion constructor
	Mat4 testQuat(Quaternion(1, 2, 3, 4));
	glm::mat4 expectedQuat(glm::quat(1, 2, 3, 4));
	Assert<Mat4, glm::mat4, 4, 4>(testQuat, expectedQuat, "Mat4::Mat4(Quaternion&)");

	// Test copy constructor
	Mat4 test_copy(arg0);
	Assert<Mat4, Mat4, 4, 4>(test_copy, arg0, "Mat4::Mat4(Mat4&");

	// Test row
	Vec4 row_0 = arg1.Row(0);
	Vec4 row_0_expected(1, 5, 9, 13);
	Assert<Vec4, Vec4, 4>(row_0, row_0_expected, "Mat4::Row(0)");

	Vec4 row_1 = arg1.Row(1);
	Vec4 row_1_expected(2, 6, 10, 14);
	Assert<Vec4, Vec4, 4>(row_1, row_1_expected, "Mat4::Row(1)");

	Vec4 row_2 = arg1.Row(2);
	Vec4 row_2_expected(3, 7, 11, 15);
	Assert<Vec4, Vec4, 4>(row_2, row_2_expected, "Mat4::Row(2)");

	Vec4 row_3 = arg1.Row(3);
	Vec4 row_3_expected(4, 8, 12, 1);
	Assert<Vec4, Vec4, 4>(row_3, row_3_expected, "Mat4::Row(3)");

	// Test Column
	Vec4 col_0 = arg1.Column(0);
	Vec4 col_0_expected(1, 2, 3, 4);
	Assert<Vec4, Vec4, 4>(col_0, col_0_expected, "Mat4::Col(0)");

	Vec4 col_1 = arg1.Column(1);
	Vec4 col_1_expected(5, 6, 7, 8);
	Assert<Vec4, Vec4, 4>(col_1, col_1_expected, "Mat4::Col(1)");

	Vec4 col_2 = arg1.Column(2);
	Vec4 col_2_expected(9, 10, 11, 12);
	Assert<Vec4, Vec4, 4>(col_2, col_2_expected, "Mat4::Col(2)");

	Vec4 col_3 = arg1.Column(3);
	Vec4 col_3_expected(13, 14, 15, 1);
	Assert<Vec4, Vec4, 4>(col_3, col_3_expected, "Mat4::Col(3)");

	// Test Inverse()
	// Invalid test
	Mat4 inverse_test_invalid = arg1;
	inverse_test_invalid.Invert();
	glm::mat4 testInverse_invalid = glm::inverse(arg1_glm);
	Assert<Mat4, glm::mat4, 4, 4>(inverse_test_invalid, testInverse_invalid, "Mat4::Inverse(invalid)");

	Mat4 inverse_test_valid = arg0;
	inverse_test_valid.Invert();
	glm::mat4 testInverse_valid = glm::inverse(arg0_glm);
	Assert<Mat4, glm::mat4, 4, 4>(inverse_test_valid, testInverse_valid, "Mat4::Inverse()");

	// Test GetInverse()
	// Invalid
	Mat4 getInverse_test_invalid = arg1.GetInverse();
	glm::mat4 testGetInverse_invalid = glm::inverse(arg1_glm);
	Assert<Mat4, glm::mat4, 4, 4>(getInverse_test_invalid, testGetInverse_invalid, "Mat4::Inverse(invalid)");

	Mat4 getInverse_test_valid = arg0.GetInverse();
	glm::mat4 testGetInverse_valid = glm::inverse(arg0_glm);
	Assert<Mat4, glm::mat4, 4, 4>(getInverse_test_valid, testGetInverse_valid, "Mat4::Inverse()");

	// Test Transpose()
	Mat4 testTranspose = arg0;
	testTranspose.Transpose();
	glm::mat4 expectedTranspose = glm::transpose(arg0_glm);
	Assert<Mat4, glm::mat4, 4, 4>(testTranspose, expectedTranspose, "Mat4::Transpose()");

	// Test GetTranspose()
	Mat4 testGetTranspose = arg0.GetTranspose();
	glm::mat4 expectedGetTranspose = glm::transpose(arg0_glm);
	Assert<Mat4, glm::mat4, 4, 4>(testGetTranspose, expectedGetTranspose, "Mat4::GetTranspose()");

	// Test Scale()
	Mat4 testScale = arg1;
	testScale.Scale(Vec3(1, 2, 3));
	glm::mat4 expectedScale = glm::scale(arg1_glm, glm::vec3(1, 2, 3));
	Assert<Mat4, glm::mat4, 4, 4>(testScale, expectedScale, "Mat4::Scale()");

	// Test ScaleMatrix()
	Mat4 testScaleMatrix = Mat4::ScaleMatrix(Vec3(1, 2, 3));
	glm::mat4 expectedScaleMatrix = glm::scale(glm::identity<glm::mat4>(), glm::vec3(1, 2, 3));
	Assert<Mat4, glm::mat4, 4, 4>(testScaleMatrix, expectedScaleMatrix, "Mat4::ScaleMatrix()");

	// Test Translate()
	Mat4 testTranslate = arg0;
	testTranslate.Translate(Vec3(1, 2, 3));
	glm::mat4 expectedTranslate = glm::translate(arg0_glm, glm::vec3(1, 2, 3));
	Assert<Mat4, glm::mat4, 4, 4>(testTranslate, expectedTranslate, "Mat4::Translate()");

	// Test TranslateMatrix()
	Mat4 testTranslateMatrix = Mat4::TranslateMatrix(Vec3(1, 2, 3));
	Assert<Mat4, glm::mat4, 4, 4>(testTranslateMatrix, expectedTranslate, "Mat4::TranslateMatrix()");

	// Test Perspective()
	Mat4 testPerspective = Mat4::Perspective(1920.f / 1080.f, 30., 0.1f, 40.f);
	glm::mat4 expectedPerspective = glm::perspective(30.f, 1920.0f / 1080.0f, 0.1f, 40.0f);
	Assert<Mat4, glm::mat4, 4, 4>(testPerspective, expectedPerspective, "Mat4::Perspective()");

	// Test Orthographic()
	Mat4 testOrthographic = Mat4::Orthographic(1920.f / 1080.f, 30., 0.1f, 40.f);
	float c = 1.0 / tanf(30. / 2.0);
	float r = 0.1f / c;
	float l = -r;
	float t = (1920.0f / 1080.0f) * 0.1f / c;
	float b = -t;
	glm::mat4 expectedOrthographic = glm::ortho(l, r, b, t, 0.1f, 40.f);
	Assert<Mat4, glm::mat4, 4, 4>(testOrthographic, expectedOrthographic, "Mat4::Orthographic()");

	// Test LookAt()
	Mat4 testLookAt = Mat4::LookAt(Vec3(0, 0, 0), Vec3(1, 1, 1), Vec3(0, 1, 0));
	glm::mat4 expectedLookAt = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 1, 0));
	Assert<Mat4, glm::mat4, 4, 4>(testLookAt, expectedLookAt, "Mat4::LookAt()");

	// Test operator=
	Mat4 testArg1EQ = arg1;
	Assert<Mat4, Mat4, 4, 4>(testArg1EQ, arg1, "Mat4::operator=");

	// Test operator+
	Mat4 testArg0Plus = arg0 + arg0;
	Mat4 expectedArg0Plus = arg0 * 2;
	Assert<Mat4, Mat4, 4, 4>(testArg0Plus, expectedArg0Plus, "Mat4::operator+");

	// Test operator+=
	Mat4 testArg0PlusEQ = arg0;
	testArg0PlusEQ += arg0;
	Assert<Mat4, Mat4, 4, 4>(testArg0PlusEQ, expectedArg0Plus, "Mat4::operator+=");

	// Test operator* Mat4& other
	Mat4 testArg1Mul = arg1 * arg1;
	glm::mat4 expectedArg1Mul = arg1_glm * arg1_glm;
	Assert<Mat4, glm::mat4, 4, 4>(testArg1Mul, expectedArg1Mul, "Mat4::operator*(const Mat4& other)");

	// Test operator*= Mat4& other
	Mat4 testArg1MulEQ = arg1;
	testArg1MulEQ *= arg1;
	Assert<Mat4, glm::mat4, 4, 4>(testArg1MulEQ, expectedArg1Mul, "Mat4::operator*=(const Mat4& other)");

	// Test operator* float& scale
	Mat4 testArg1Mul_float = arg1 * 2;
	Mat4 expectedArg1Mul_float = arg1 + arg1;
	Assert<Mat4, Mat4, 4, 4>(testArg1Mul_float, expectedArg1Mul_float, "Mat4::operator*(float& scale)");

	// Test operator*= float& scale
	Mat4 testArg1MulEQ_float = arg1;
	testArg1MulEQ_float *= 2;
	Assert<Mat4, Mat4, 4, 4>(testArg1MulEQ_float, expectedArg1Mul_float, "Mat4::operator*=(float& scale)");

	// Test operator/ float& scale 
	Mat4 testArg1Div_float = arg1 / 2;
	Mat4 expectedArg1Div_float = arg1;
	for (int i = 0; i < 4; ++i) { expectedArg1Div_float[i] /= 2;  }
	Assert<Mat4, Mat4, 4, 4>(testArg1Div_float, expectedArg1Div_float, "Mat4::operator/");

	// Test operator/= float& scale
	Mat4 testArg1DivEQ_float = arg1;
	testArg1DivEQ_float /= 2;
	Assert<Mat4, Mat4, 4, 4>(testArg1DivEQ_float, expectedArg1Div_float, "Mat4::operator/=");
}