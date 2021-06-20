#include "Quaternion.h"
#include <math.h>

Quaternion::Quaternion(void) {
	r = 1.0;
	i[0] = 0.0;
	i[1] = 0.0;
	i[2] = 0.0;
}

Quaternion::Quaternion(const float w, const float x, const float y, const float z) {
	r = w;
	i[0] = x;
	i[1] = y;
	i[2] = z;
}

Quaternion::Quaternion(const Quaternion& other) {
	r = other.r;
	i[0] = other.i[0];
	i[1] = other.i[1];
	i[2] = other.i[2];
}

Quaternion Quaternion::Conjugate(void) const {
	return Quaternion(r, -i[0], -i[1], -i[2]);
}

Quaternion::Quaternion(const Vec3& pos) {
	r = 0.0;
	i[0] = pos[0];
	i[1] = pos[1];
	i[2] = pos[2];
}

Quaternion::Quaternion(const float theta, const Vec3& axis) {
	r = theta;
	i[0] = axis[0];
	i[1] = axis[1];
	i[2] = axis[2];
}

float Quaternion::Norm(void) const {
	return sqrtf((r * r) + 
		         (i[0] * i[0]) +
				 (i[1] * i[1]) + 
		         (i[2] * i[2]));
}

Quaternion Quaternion::Cross(const Quaternion& other) {
	Quaternion temp = Quaternion();
	
	return temp;
}

float Quaternion::Dot(const Quaternion& other) {
	return (r * other.r) + 
		   (i[0] * other.i[0]) + 
		   (i[1] * other.i[1]) + 
		   (i[2] * other.i[2]);
}

float Quaternion::Length(void) {
	return sqrtf((r * r) + (i[0] * i[0]) +
				 (i[1] * i[1]) + (i[2] * i[2]));
}

float Quaternion::Norm2(void) const {
	return (r * r) + 
		   (i[0] * i[0]) +
		   (i[1] * i[1]) + 
		   (i[2] * i[2]);
}

Quaternion Quaternion::Inverse(void) const {
	float scalar = 1 / Norm2();
	return *this * scalar;
}

Mat4 Quaternion::ToMat4(void) const {
	Mat3 temp = Mat3();
	float x2 = i[0] * i[0];
	float y2 = i[1] * i[1];
	float z2 = i[2] * i[2];

	temp[0][0] = 1 - 2 * y2 - 2 * z2; 
	temp[0][1] = 2 * i[0] * i[1] - 2 * r * i[2];
	temp[0][2] = 2 * i[0] * i[2] + 2 * r * i[1];

	temp[1][0] = 2 * i[0] * i[1] + 2 * r * i[2];
	temp[1][1] = 1 - 2 * x2 - 2 * z2;
	temp[1][2] = 2 * i[1] * i[2] - 2 * r * i[0];

	temp[2][0] = 2 * i[0] * i[2] - 2 * r * i[1];
	temp[2][1] = 2 * i[1] * i[2] + 2 * r * i[0];
	temp[2][2] = 1 - 2 * x2 - 2 * y2;
	
	return Mat4(temp);
}

Mat3 Quaternion::ToMat3(void) const {
	Mat3 temp = Mat3();
	float x2 = i[0] * i[0];
	float y2 = i[1] * i[1];
	float z2 = i[2] * i[2];

	temp[0][0] = 1 - 2 * y2 - 2 * z2; 
	temp[0][1] = 2 * i[0] * i[1] - 2 * r * i[2];
	temp[0][2] = 2 * i[0] * i[2] + 2 * r * i[1];

	temp[1][0] = 2 * i[0] * i[1] + 2 * r * i[2];
	temp[1][1] = 1 - 2 * x2 - 2 * z2;
	temp[1][2] = 2 * i[1] * i[2] - 2 * r * i[0];

	temp[2][0] = 2 * i[0] * i[2] - 2 * r * i[1];
	temp[2][1] = 2 * i[1] * i[2] + 2 * r * i[0];
	temp[2][2] = 1 - 2 * x2 - 2 * y2;
	
	return temp;
}

Quaternion Quaternion::Rotate(const Quaternion& p, const Vec3 axis, float theta) {
	Quaternion q = Quaternion(theta, axis);
	Quaternion q_inverse = q.Inverse();

	return q * p * q_inverse;
}

Quaternion Quaternion::Unit(const Quaternion& quat) {
	return quat * (1 / quat.Norm());
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
	float w = (r * other.r) - 
		      (i[0] * other.i[0]) - 
		      (i[1] * other.i[1]) - 
		      (i[2] * other.i[2]);

	float x = (i[1] * other.i[2]) -
		      (i[2] * other.i[1]) +
			  (i[0] * other.r) +
			  (r * other.i[0]);

	float y = (i[2] * other.i[0]) -
			  (i[0] * other.i[2]) +
			  (i[1] * other.r) +
			  (r * other.i[1]);

	float z = (i[0] * other.i[1]) -
			  (i[1] * other.i[0]) +
			  (i[2] * other.r) +
			  (r * other.i[2]);

	return Quaternion(w, x, y, z);
}

Quaternion Quaternion::operator*(const float scalar) const {
	float w = r * scalar;
	float x = i[0] * scalar;
	float y = i[1] * scalar;
	float z = i[2] * scalar;

	return Quaternion(w, x, y, z);
}

Quaternion& Quaternion::operator*=(const Quaternion& other) {
	float w = (r * other. r) -
		      (i[0] * other.i[0]) -
		      (i[1] * other.i[1]) - 
		      (i[2] * other.i[2]);

	float x = (i[1] * other.i[2]) -
			  (i[2] * other.i[1]) +
			  (i[0] * other.r) +
			  (r * other.i[0]);

	float y = (i[2] * other.i[0]) -
			  (i[0] * other.i[2]) +
			  (i[1] * other.r) +
			  (r * other.i[1]);

	float z = (i[0] * other.i[1]) -
			  (i[1] * other.i[0]) +
			  (i[2] * other.r) +
			  (r * other.i[2]);

	r = w; i[0] = x; i[1] = y; i[2] = z;

	return *this;
}

Quaternion& Quaternion::operator*=(const float scalar) {
	r *= scalar;
	i[0] *= scalar;
	i[1] *= scalar;
	i[2] *= scalar;
	
	return *this;
}

Quaternion Quaternion::operator+(const Quaternion& other) const {
	float w = r + other.r;
	float x = i[0] + other.i[0];
	float y = i[1] + other.i[1];
	float z = i[2] + other.i[2];
	return Quaternion(w, x, y, z);
}

Quaternion& Quaternion::operator+=(const Quaternion& other) {
	r += other.r;
	i[0] += other.i[0];
	i[1] += other.i[1];
	i[2] += other.i[2];
	return *this;
}

float Quaternion::Real(void) const {
	return r;
}

Vec3 Quaternion::Imaginary(void) const {
	return i;
}
