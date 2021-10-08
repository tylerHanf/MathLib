#include "TestUtils.h"
#include "Mat3_Test.h"
#include "Mat3.h"
#include "glm/glm/geometric.hpp"
#include "glm/glm/mat3x3.hpp"

void TestMat3(void) {
	Mat3 arg0(1, 2, 3, 4, 5, 6, 7, 8, 9);
	Mat3 arg1(10, 11, 12, 13, 14, 15, 16, 17, 18);

	// Test empty constructor
	Mat3 test_empty;
	Mat3 expected_empty(1.0, 0.0, 0.0,
						0.0, 1.0, 0.0,
						0.0, 0.0, 1.0);
	Assert<Mat3, Mat3, 3, 3>(test_empty, expected_empty, "Mat3::Mat3()");

	// Test basic constructor
	Mat3 test_basic(1, 2, 3,
					4, 5, 6,
					7, 8, 9);
	Mat3 expected_basic;
	expected_basic[0] = Vec3(1, 2, 3);
	expected_basic[1] = Vec3(4, 5, 6);
	expected_basic[2] = Vec3(7, 8, 9);
	Assert<Mat3, Mat3, 3, 3>(test_basic, expected_basic, "Mat3::Mat3(x,y,z...)");

	// Test Vec3 constructor
	Vec3 test_Vec3_0(1, 2, 3);
	Vec3 test_Vec3_1(4, 5, 6);
	Vec3 test_Vec3_2(7, 8, 9);
	Mat3 test_vec3(test_Vec3_0, test_Vec3_1, test_Vec3_2);
	Assert<Mat3, Mat3, 3, 3>(test_vec3, arg0, "Mat3::Mat3(Vec3...)");

	// Test copy constructor
	Mat3 test_copy(arg0);
	Assert<Mat3, Mat3, 3, 3>(test_copy, arg0, "Mat3::Mat3(Mat3&)");

	// Test row
	Vec3 row_0 = arg0.Row(0);
	Vec3 row_0_expected(1, 2, 3);
	Assert<Vec3, Vec3, 3>(row_0, row_0_expected, "Mat3::Row(0)");
	Vec3 row_1 = arg0.Row(1);
	Vec3 row_1_expected(4, 5, 6);
	Assert<Vec3, Vec3, 3>(row_1, row_1_expected, "Mat3::Row(1)");
	Vec3 row_2 = arg0.Row(2);
	Vec3 row_2_expected(7, 8, 9);
	Assert<Vec3, Vec3, 3>(row_2, row_2_expected, "Mat3::Row(2)");
	
	// Test column
	Vec3 col_0 = arg0.Column(0);
	Vec3 col_0_expected(1, 4, 7);
	Assert<Vec3, Vec3, 3>(col_0, col_0_expected, "Mat3::Column(0)");
	Vec3 col_1 = arg0.Column(1);
	Vec3 col_1_expected(2, 5, 8);
	Assert<Vec3, Vec3, 3>(col_1, col_1_expected, "Mat3::Column(1)");
	Vec3 col_2 = arg0.Column(2);
	Vec3 col_2_expected(3, 6, 9);
	Assert<Vec3, Vec3, 3>(col_2, col_2_expected, "Mat3::Column(2)");

	// Test GetInverse()
	Mat3 test_inverse = arg0.GetInverse();
	glm::mat3 expected_inverse_init(1, 2, 3,
							        4, 5, 6,
							        7, 8, 9);
	glm::mat3 expected_inverse = glm::inverse(expected_inverse_init);
	Assert<Mat3, glm::mat3, 3, 3>(test_inverse, expected_inverse, "Mat3::GetInverse()");

	// Test GetTranspose()
	Mat3 test_transpose = arg0.GetTranspose();
	Mat3 expected_transpose(1, 4, 7,
							2, 5, 8,
							3, 6, 9);
	Assert<Mat3, Mat3, 3, 3>(test_transpose, expected_transpose, "Mat3::GetTranspose()");

	// Test Invert()
	Mat3 test_inverse_init = arg0;
	test_inverse_init.Invert();
	Assert<Mat3, Mat3, 3, 3>(test_inverse_init, expected_transpose, "Mat3::Invert()");

	// Test Transpose()
	test_transpose.Transpose();
	Assert<Mat3, Mat3, 3, 3>(test_transpose, expected_transpose, "Mat3::Transpose()");

	// Test ScaleMatrix()
	Mat3 test_scale = Mat3::ScaleMatrix(1, 2, 3);
	Mat3 expected_scale(1, 0, 0,
						0, 2, 0,
						0, 0, 3);
	Assert<Mat3, Mat3, 3, 3>(test_scale, expected_scale, "Mat3::ScaleMatrix(1, 2, 3)");

	// Test operator=
	Mat3 test_assignment = arg0;
	Assert<Mat3, Mat3, 3, 3>(test_assignment, arg0, "Mat3::operator=");

	// Test operator+
	Mat3 test_plus_result = arg0 + arg1;
	Mat3 test_plus_expected(11, 13, 15,
		                    17, 19, 21,
		                    23, 25, 27);
	Assert<Mat3, Mat3, 3, 3>(test_plus_result, test_plus_expected, "Mat3::operator+");

	// Test operator +=
	Mat3 test_plus_0 = arg0;
	test_plus_0 += arg1;
	Assert<Mat3, Mat3, 3, 3>(test_plus_0, test_plus_expected, "Mat3::operator+=");

	// Test operator-
	Mat3 test_sub_0 = test_plus_expected;
	Mat3 test_sub_result = test_sub_0 - arg1;
	Assert<Mat3, Mat3, 3, 3>(test_sub_result, arg0, "Mat3::operator-");

	// Test operator-=
	test_sub_0 -= arg1;
	Assert<Mat3, Mat3, 3, 3>(test_sub_0, arg0, "Mat3::operator-=");

	// Test operator*
	Mat3 test_mul = arg0 * arg1;
	glm::mat3 test_mul0(1, 2, 3, 4, 5, 6, 7, 8, 9);
	glm::mat3 test_mul1(10, 11, 12, 13, 14, 15, 16, 17, 18);
	glm::mat3 test_mul_expected = test_mul0 * test_mul1;
	Assert<Mat3, glm::mat3, 3, 3>(test_mul, test_mul_expected, "Mat3::operator*");

	// Test operator*=
	Mat3 test_mul_eq = arg0;
	test_mul_eq *= arg1;
	Assert<Mat3, glm::mat3, 3, 3>(test_mul_eq, test_mul_expected, "mat3::operator*=");
}