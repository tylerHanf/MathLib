#include "Mat3.h"

Mat3::Mat3() {
	M[0] = Vec3(1.0f, 0.0f, 0.0f);
	M[1] = Vec3(0.0f, 1.0f, 0.0f);
	M[2] = Vec3(0.0f, 0.0f, 1.0f);
}

Mat3::Mat3(const float x0, const float y0, const float z0,
	       const float x1, const float y1, const float z1,
	       const float x2, const float y2, const float z2) 
{
	M[0] = Vec3(x0, y0, z0);
	M[1] = Vec3(x1, y1, z1);
	M[2] = Vec3(x2, y2, z2);
}

Mat3::Mat3(Vec3& x, Vec3& y, Vec3& z) {
	M[0] = x;
	M[1] = y;
	M[2] = z;
}

Mat3::Mat3(const Mat3& other) {
	M[0] = other.M[0];
	M[1] = other.M[1];
	M[2] = other.M[2];
}

Vec3 Mat3::Row(const int index) const {
	return M[index];
}

Vec3 Mat3::Column(const int index) const {
	Vec3 temp;
	if (index == 0) {
		temp = Vec3(M[0][0], M[1][0], M[2][0]);
	}
	if (index == 1) {
		temp = Vec3(M[0][1], M[1][1], M[2][1]);
	}
	if (index == 2) {
		temp = Vec3(M[0][2], M[1][2], M[2][2]);
	}
	return temp;
}

void Mat3::Transpose() {
	float temp;
	temp = M[1][0];
	M[1][0] = M[0][1];
	M[0][1] = temp;

	temp = M[2][0];
	M[2][0] = M[0][2];
	M[0][2] = temp;

	temp = M[2][1];
	M[2][1] = M[1][2];
	M[1][2] = temp;
}

void Mat3::Invert() {
	Transpose();
}

Mat3 Mat3::GetInverse() const {
	return GetTranspose();
}

Mat3 Mat3::GetTranspose() const {
	Mat3 temp = *this;
	temp.Transpose();
	return temp;
}

Mat3 Mat3::ScaleMatrix(const float x, const float y, const float z) {
	Mat3 temp;
	temp.M[0][0] = x;
	temp.M[1][1] = y;
	temp.M[2][2] = z;
	return temp;
}

Mat3& Mat3::operator=(const Mat3& other) {
	M[0] = other.M[0];
	M[1] = other.M[1];
	M[2] = other.M[2];
	return *this;
}

Mat3 Mat3::operator+(const Mat3& other) const {
	Mat3 temp;
	temp.M[0] = M[0] + other.M[0];
	temp.M[1] = M[1] + other.M[1];
	temp.M[2] = M[2] + other.M[2];
	return temp;
}

Mat3& Mat3::operator+=(const Mat3& other) {
	M[0] += other.M[0];
	M[1] += other.M[1];
	M[2] += other.M[2];
	return *this;
}

Mat3 Mat3::operator-(const Mat3& other) const {
	Mat3 temp;
	temp.M[0] = M[0] - other.M[0];
	temp.M[1] = M[1] - other.M[1];
	temp.M[2] = M[2] - other.M[2];
	return temp;
}

Mat3& Mat3::operator-=(const Mat3& other) {
	M[0] -= other.M[0];
	M[1] -= other.M[1];
	M[2] -= other.M[2];
	return *this;
}

Mat3 Mat3::operator*(const Mat3& other) const {
	Mat3 temp;
	temp.M[0][0] = M[0][0] * other.M[0][0] + M[0][1] * other.M[1][0] + M[0][2] * other.M[2][0];
	temp.M[0][1] = M[0][0] * other.M[0][1] + M[0][1] * other.M[1][1] + M[0][2] * other.M[2][1];
	temp.M[0][2] = M[0][0] * other.M[0][2] + M[0][1] * other.M[1][2] + M[0][2] * other.M[2][2];

	temp.M[1][0] = M[0][0] * other.M[0][0] + M[0][1] * other.M[1][0] + M[0][2] * other.M[2][0];
	temp.M[1][1] = M[0][0] * other.M[0][1] + M[0][1] * other.M[1][1] + M[0][2] * other.M[2][1];
	temp.M[1][2] = M[0][0] * other.M[0][2] + M[0][1] * other.M[1][2] + M[0][2] * other.M[2][2];

	temp.M[2][0] = M[0][0] * other.M[0][0] + M[0][1] * other.M[1][0] + M[0][2] * other.M[2][0];
	temp.M[2][1] = M[0][0] * other.M[0][1] + M[0][1] * other.M[1][1] + M[0][2] * other.M[2][1];
	temp.M[2][2] = M[0][0] * other.M[0][2] + M[0][1] * other.M[1][2] + M[0][2] * other.M[2][2];
	return temp;
}

Mat3& Mat3::operator*=(const Mat3& other) {
	Mat3 temp;
	temp.M[0][0] = M[0][0] * other.M[0][0] + M[0][1] * other.M[1][0] + M[0][2] * other.M[2][0];
	temp.M[0][1] = M[0][0] * other.M[0][1] + M[0][1] * other.M[1][1] + M[0][2] * other.M[2][1];
	temp.M[0][2] = M[0][0] * other.M[0][2] + M[0][1] * other.M[1][2] + M[0][2] * other.M[2][2];

	temp.M[1][0] = M[0][0] * other.M[0][0] + M[0][1] * other.M[1][0] + M[0][2] * other.M[2][0];
	temp.M[1][1] = M[0][0] * other.M[0][1] + M[0][1] * other.M[1][1] + M[0][2] * other.M[2][1];
	temp.M[1][2] = M[0][0] * other.M[0][2] + M[0][1] * other.M[1][2] + M[0][2] * other.M[2][2];

	temp.M[2][0] = M[0][0] * other.M[0][0] + M[0][1] * other.M[1][0] + M[0][2] * other.M[2][0];
	temp.M[2][1] = M[0][0] * other.M[0][1] + M[0][1] * other.M[1][1] + M[0][2] * other.M[2][1];
	temp.M[2][2] = M[0][0] * other.M[0][2] + M[0][1] * other.M[1][2] + M[0][2] * other.M[2][2];
	*this = temp;
	return *this;
}

Vec3& Mat3::operator[](const int index) {
	return M[index];
}

Vec3 Mat3::operator[](const int index) const {
	return M[index];
}
