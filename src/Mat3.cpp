#include "Mat3.h"
#include <math.h>
#include "Logger.h"

Mat3::Mat3() {
	M[0] = Vec3(1.0f, 0.0f, 0.0f);
	M[1] = Vec3(0.0f, 1.0f, 0.0f);
	M[2] = Vec3(0.0f, 0.0f, 1.0f);
}

Mat3::Mat3(const float x0, const float x1, const float x2,
	       const float y0, const float y1, const float y2,
	       const float z0, const float z1, const float z2) 
{
	M[0] = Vec3(x0, x1, x2);
	M[1] = Vec3(y0, y1, y2);
	M[2] = Vec3(z0, z1, z2);
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

Mat3::Mat3(const Quaternion& q) {
	Vec3 i = q.Imaginary();
	float r = q.r;
	float x2 = i.x * i.x;
	float y2 = i.y * i.y;
	float z2 = i.z * i.z;

	M[0].x = 1 - 2 * y2 - 2 * z2;
	M[0].y = 2 * i.x * i.y + 2 * r * i.z;
	M[0].z = 2 * i.x * i.z - 2 * r * i.y;

	M[1].x = 2 * i.x * i.y - 2 * r * i.z;
	M[1].y = 1 - 2 * x2 - 2 * z2;
	M[1].z = 2 * i.y * i.z + 2 * r * i.x;

	M[2].x = 2 * i.x * i.z + 2 * r * i.y;
	M[2].y = 2 * i.y * i.z - 2 * r * i.x;
	M[2].z = 1 - 2 * x2 - 2 * y2;
}

Vec3 Mat3::Row(const int index) const {
	return M[index];
}

Vec3 Mat3::Column(const int index) const {
	return Vec3(M[0][index], M[1][index], M[2][index]);
}

void Mat3::Transpose() {
	float temp;
	temp = M[1].x;
	M[1].x = M[0].y;
	M[0].y = temp;

	temp = M[2].x;
	M[2].x = M[0].z;
	M[0].z = temp;

	temp = M[2].y;
	M[2].y = M[1].z;
	M[1].z = temp;
}

Mat3 Mat3::Adjoint() {
	Mat3 adj;
	adj[0].x = (M[1].y * M[2].z) - (M[1].z * M[2].y);
	adj[0].y = -1 * ((M[1].x * M[2].z) - (M[1].z * M[2].x));
	adj[0].z = (M[1].x * M[2].y) - (M[1].y * M[2].x);

	adj[1].x = -1 * ((M[0].y * M[2].z) - (M[0].z * M[2].y));
	adj[1].y = (M[0].x * M[2].z) - (M[0].z * M[2].x);
	adj[1].z = -1 * ((M[0].x * M[2].y) - (M[0].y * M[2].x));

	adj[2].x = (M[0].y * M[1].z) - (M[0].z * M[1].y);
	adj[2].y = -1 * ((M[0].x * M[1].z) - (M[0].z * M[1].x));
	adj[2].z = (M[0].x * M[1].y) - (M[0].y * M[1].x);
	return adj;
}

// Uses https://www.geometrictools.com/Documentation/LaplaceExpansionTheorem.pdf
void Mat3::Invert() {
	float det = Determinant();
	if (det == 0) {
		Logger::Log("Mat3::Invert Invalid Invert -> Determinant is 0");
		SetErrorMat();
	}
	else {
		*this = Adjoint();
		*this /= det;
	}
}

Mat3 Mat3::GetInverse() const {
	Mat3 temp(*this);
	temp.Invert();
	return temp;
}

Mat3 Mat3::GetTranspose() const {
	Mat3 temp = *this;
	temp.Transpose();
	return temp;
}

Mat3 Mat3::ScaleMatrix(const Vec3& scale) {
	Mat3 temp;
	temp.M[0].x = scale.x;
	temp.M[1].y = scale.y;
	temp.M[2].z = scale.z;
	return temp;
}

void Mat3::SetErrorMat(void) {
	M[0] = Vec3(-INFINITY, INFINITY, -INFINITY);
	M[1] = Vec3(INFINITY, -INFINITY, INFINITY);
	M[2] = Vec3(-INFINITY, INFINITY, -INFINITY);
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
	temp.M[0].x = M[0].x * other.M[0].x + M[0].y * other.M[1].x + M[0].z * other.M[2].x;
	temp.M[0].y = M[1].x * other.M[0].x + M[1].y * other.M[1].x + M[1].z * other.M[2].x;
	temp.M[0].z = M[2].x * other.M[0].x + M[2].y * other.M[1].x + M[2].z * other.M[2].x;

	temp.M[1].x = M[0].x * other.M[0].y + M[0].y * other.M[1].y + M[0].z * other.M[2].y;
	temp.M[1].y = M[1].x * other.M[0].y + M[1].y * other.M[1].y + M[1].z * other.M[2].y;
	temp.M[1].z = M[2].x * other.M[0].y + M[2].y * other.M[1].y + M[2].z * other.M[2].y;

	temp.M[2].x = M[0].x * other.M[0].z + M[0].y * other.M[1].z + M[0].z * other.M[2].z;
	temp.M[2].y = M[1].x * other.M[0].z + M[1].y * other.M[1].z + M[1].z * other.M[2].z;
	temp.M[2].z = M[2].x * other.M[0].z + M[2].y * other.M[1].z + M[2].z * other.M[2].z;
	return temp;
}

Mat3& Mat3::operator*=(const Mat3& other) {
	Mat3 temp;
	temp.M[0].x = M[0].x * other.M[0].x + M[0].y * other.M[1].x + M[0].z * other.M[2].x;
	temp.M[0].y = M[1].x * other.M[0].x + M[1].y * other.M[1].x + M[1].z * other.M[2].x;
	temp.M[0].z = M[2].x * other.M[0].x + M[2].y * other.M[1].x + M[2].z * other.M[2].x;

	temp.M[1].x = M[0].x * other.M[0].y + M[0].y * other.M[1].y + M[0].z * other.M[2].y;
	temp.M[1].y = M[1].x * other.M[0].y + M[1].y * other.M[1].y + M[1].z * other.M[2].y;
	temp.M[1].z = M[2].x * other.M[0].y + M[2].y * other.M[1].y + M[2].z * other.M[2].y;

	temp.M[2].x = M[0].x * other.M[0].z + M[0].y * other.M[1].z + M[0].z * other.M[2].z;
	temp.M[2].y = M[1].x * other.M[0].z + M[1].y * other.M[1].z + M[1].z * other.M[2].z;
	temp.M[2].z = M[2].x * other.M[0].z + M[2].y * other.M[1].z + M[2].z * other.M[2].z;
	*this = temp;
	return *this;
}

Mat3 Mat3::operator*(const float& scale) const {
	Mat3 temp;
	temp[0] = M[0] * scale;
	temp[1] = M[1] * scale;
	temp[2] = M[2] * scale;
	return temp;
}

Mat3& Mat3::operator*=(const float& scale) {
	M[0] *= scale;
	M[1] *= scale;
	M[2] *= scale;
	return *this;
}

Mat3 Mat3::operator/(const float& scale) const {
	Mat3 temp;
	temp[0] = M[0] / scale;
	temp[1] = M[1] / scale;
	temp[2] = M[2] / scale;
	return temp;
}

Mat3& Mat3::operator/=(const float& scale) {
	M[0] /= scale;
	M[1] /= scale;
	M[2] /= scale;
	return *this;
}

Vec3& Mat3::operator[](const int index) {
	return M[index];
}

Vec3 Mat3::operator[](const int index) const {
	return M[index];
}
