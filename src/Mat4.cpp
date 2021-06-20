#include "Mat4.h"
#include "Mat3.h"
#include <math.h>

Mat4::Mat4() {
	M[0] = Vec4(1.0f, 0.0f, 0.0f, 0.0f);
	M[1] = Vec4(0.0f, 1.0f, 0.0f, 0.0f);
	M[2] = Vec4(0.0f, 0.0f, 1.0f, 0.0f);
	M[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4::Mat4(const float x0, const float y0, const float z0, const float px,
	const float x1, const float y1, const float z1, const float py,
	const float x2, const float y2, const float z2, const float pz,
	const float w0, const float w1, const float w2, const float w3)
{
	M[0] = Vec4(x0, y0, z0, px);
	M[1] = Vec4(x1, y1, z1, py);
	M[2] = Vec4(x2, y2, z2, pz);
	M[3] = Vec4(w0, w1, w2, w3);
}

Mat4::Mat4(const Mat4& other) {
	M[0] = other.M[0];
	M[1] = other.M[1];
	M[2] = other.M[2];
	M[3] = other.M[3];
}

Mat4::Mat4(const Mat3& dcm, const Vec3& pos) {
	M[0] = Vec4(dcm.M[0], pos[0]);
	M[1] = Vec4(dcm.M[1], pos[1]);
	M[2] = Vec4(dcm.M[2], pos[2]);
	M[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4::Mat4(const Mat3& dcm) {
	M[0] = Vec4(dcm.M[0], 0.0);
	M[1] = Vec4(dcm.M[1], 0.0);
	M[2] = Vec4(dcm.M[2], 0.0);
	M[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4::Mat4(const Vec3& pos) {
	M[0] = Vec4(1.0f, 0.0f, 0.0f, pos[0]);
	M[1] = Vec4(0.0f, 1.0f, 0.0f, pos[1]);
	M[2] = Vec4(0.0f, 0.0f, 1.0f, pos[2]);
	M[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4 Mat4::Perspective(const float a, const float n, const float f) {
	float e = 1.0 / tanf(a / 2.0);
	float r = n / e;
	float l = -r;
	float t = a * n / e;
	float b = -t;

	Mat4 perspective = Mat4((2.0 * n / (r - l)),             0.0,  (r + l) / (r - l),                    0.0,
							                0.0, 2 * n / (t - b),  (t + b) / (t - b),                    0.0,
							                0.0,             0.0, -(f + n) / (f - n), -(2 * n * f) / (f - n),
							                0.0,             0.0,               -1.0,                    0.0);
	return perspective;
}

Mat4 Mat4::Orthographic(const float a, const float n, const float f) {
	float e = 1.0 / tanf(a / 2.0);
	float r = n / e;
	float l = -r;
	float t = a * n / e;
	float b = -t;

	Mat4 orthographic = Mat4(2.0 / (r - l),         0.0,          0.0, -(r + l) / (r - l),
		                               0.0, 2 / (t - b),          0.0, -(t + b) / (t - b),
		                               0.0,         0.0, -2 / (f - n), -(f + n) / (f - n),
		                               0.0,         0.0,          0.0,                1.0);
	return orthographic;
}

Mat4 Mat4::LookAt(Vec3 eye, Vec3 at, Vec3 up) {
	Vec3 zaxis = Vec3::Unit(at - eye);
	Vec3 xaxis = Vec3::Unit(zaxis.Cross(up));
	Vec3 yaxis = xaxis.Cross(zaxis);
	zaxis *= -1;

	Mat4 viewMat = Mat4(Mat3(xaxis, yaxis, zaxis),
		                Vec3(-xaxis.Dot(eye), -yaxis.Dot(eye), -zaxis.Dot(eye)));
	return viewMat;
}

Mat4& Mat4::operator=(const Mat4& other) {
	M[0] = other.M[0];
	M[1] = other.M[1];
	M[2] = other.M[2];
	M[3] = other.M[3];

	return *this;
}

Mat4 Mat4::operator+(const Mat4& other) const {
	Mat4 temp;
	temp.M[0] = M[0] + other.M[0];
	temp.M[1] = M[1] + other.M[1];
	temp.M[2] = M[2] + other.M[2];
	temp.M[3] = M[3] + other.M[3];

	return temp;
}

Mat4& Mat4::operator+=(const Mat4& other) {
	M[0] += other.M[0];
	M[1] += other.M[1];
	M[2] += other.M[2];
	M[3] += other.M[3];

	return *this;
}

Mat4 Mat4::operator*(const Mat4& other) const {
	Mat4 temp;
	temp[0][0] = M[0][0] * other[0][0] + M[0][1] * other[1][0] + M[0][2] * other[2][0] + M[0][3] * other[3][0];
	temp[0][1] = M[0][0] * other[0][1] + M[0][1] * other[1][1] + M[0][2] * other[2][1] + M[0][3] * other[3][1];
	temp[0][2] = M[0][0] * other[0][2] + M[0][1] * other[1][2] + M[0][2] * other[2][2] + M[0][3] * other[3][2];
	temp[0][3] = M[0][0] * other[0][3] + M[0][1] * other[1][3] + M[0][2] * other[2][3] + M[0][3] * other[3][3];

	temp[1][0] = M[1][0] * other[0][0] + M[1][1] * other[1][0] + M[1][2] * other[2][0] + M[1][3] * other[3][0];
	temp[1][1] = M[1][0] * other[0][1] + M[1][1] * other[1][1] + M[1][2] * other[2][1] + M[1][3] * other[3][1];
	temp[1][2] = M[1][0] * other[0][2] + M[1][1] * other[1][2] + M[1][2] * other[2][2] + M[1][3] * other[3][2];
	temp[1][3] = M[1][0] * other[0][3] + M[1][1] * other[1][3] + M[1][2] * other[2][3] + M[1][3] * other[3][3];

	temp[2][0] = M[2][0] * other[0][0] + M[2][1] * other[1][0] + M[2][2] * other[2][0] + M[2][3] * other[3][0];
	temp[2][1] = M[2][0] * other[0][1] + M[2][1] * other[1][1] + M[2][2] * other[2][1] + M[2][3] * other[3][1];
	temp[2][2] = M[2][0] * other[0][2] + M[2][1] * other[1][2] + M[2][2] * other[2][2] + M[2][3] * other[3][2];
	temp[2][3] = M[2][0] * other[0][3] + M[2][1] * other[1][3] + M[2][2] * other[2][3] + M[2][3] * other[3][3];

	temp[3][0] = M[3][0] * other[0][0] + M[3][1] * other[1][0] + M[3][2] * other[3][0] + M[3][3] * other[3][0];
	temp[3][1] = M[3][0] * other[0][1] + M[3][1] * other[1][1] + M[3][2] * other[3][1] + M[3][3] * other[3][1];
	temp[3][2] = M[3][0] * other[0][2] + M[3][1] * other[1][2] + M[3][2] * other[3][2] + M[3][3] * other[3][2];
	temp[3][3] = M[3][0] * other[0][3] + M[3][1] * other[1][3] + M[3][2] * other[3][3] + M[3][3] * other[3][3];
	return temp;
}

Mat4& Mat4::operator*=(const Mat4& other) {
	M[0][0] = M[0][0] * other[0][0] + M[0][1] * other[1][0] + M[0][2] * other[2][0] + M[0][3] * other[3][0];
	M[0][1] = M[0][0] * other[0][1] + M[0][1] * other[1][1] + M[0][2] * other[2][1] + M[0][3] * other[3][1];
	M[0][2] = M[0][0] * other[0][2] + M[0][1] * other[1][2] + M[0][2] * other[2][2] + M[0][3] * other[3][2];
	M[0][3] = M[0][0] * other[0][3] + M[0][1] * other[1][3] + M[0][2] * other[2][3] + M[0][3] * other[3][3];

	M[1][0] = M[1][0] * other[0][0] + M[1][1] * other[1][0] + M[1][2] * other[2][0] + M[1][3] * other[3][0];
	M[1][1] = M[1][0] * other[0][1] + M[1][1] * other[1][1] + M[1][2] * other[2][1] + M[1][3] * other[3][1];
	M[1][2] = M[1][0] * other[0][2] + M[1][1] * other[1][2] + M[1][2] * other[2][2] + M[1][3] * other[3][2];
	M[1][3] = M[1][0] * other[0][3] + M[1][1] * other[1][3] + M[1][2] * other[2][3] + M[1][3] * other[3][3];

	M[2][0] = M[2][0] * other[0][0] + M[2][1] * other[1][0] + M[2][2] * other[2][0] + M[2][3] * other[3][0];
	M[2][1] = M[2][0] * other[0][1] + M[2][1] * other[1][1] + M[2][2] * other[2][1] + M[2][3] * other[3][1];
	M[2][2] = M[2][0] * other[0][2] + M[2][1] * other[1][2] + M[2][2] * other[2][2] + M[2][3] * other[3][2];
	M[2][3] = M[2][0] * other[0][3] + M[2][1] * other[1][3] + M[2][2] * other[2][3] + M[2][3] * other[3][3];

	M[3][0] = M[3][0] * other[0][0] + M[3][1] * other[1][0] + M[3][2] * other[3][0] + M[3][3] * other[3][0];
	M[3][1] = M[3][0] * other[0][1] + M[3][1] * other[1][1] + M[3][2] * other[3][1] + M[3][3] * other[3][1];
	M[3][2] = M[3][0] * other[0][2] + M[3][1] * other[1][2] + M[3][2] * other[3][2] + M[3][3] * other[3][2];
	M[3][3] = M[3][0] * other[0][3] + M[3][1] * other[1][3] + M[3][2] * other[3][3] + M[3][3] * other[3][3];
	return *this;
}
