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

Quaternion::Quaternion(const Vec3& pos) {
	r = 0.0;
	i[0] = pos[0];
	i[1] = pos[1];
	i[2] = pos[2];
}

Quaternion::Quaternion(const float theta, const Vec3& axis) {
	r = cosf(theta/2);
	i[0] = axis[0] * sinf(theta / 2);
	i[1] = axis[1] * sinf(theta / 2);
	i[2] = axis[2] * sinf(theta / 2);
}

Quaternion Quaternion::Conjugate(void) const {
	return Quaternion(r, -i[0], -i[1], -i[2]);
}

float Quaternion::Dot(const Quaternion& other) {
	return (r * other.r) + 
		   (i[0] * other.i[0]) + 
		   (i[1] * other.i[1]) + 
		   (i[2] * other.i[2]);
}

float Quaternion::Length(void) const {
	return sqrtf((r * r) + (i[0] * i[0]) +
				 (i[1] * i[1]) + (i[2] * i[2]));
}

float Quaternion::Length2(void) const {
	return (r * r) + 
		   (i[0] * i[0]) +
		   (i[1] * i[1]) + 
		   (i[2] * i[2]);
}

Quaternion Quaternion::Inverse(void) const {
	float scalar = 1 / Length2();
	Quaternion conj(r, -i[0], -i[1], -i[2]);
	return conj * scalar;
}

Vec3 Quaternion::Rotate(const Vec3& pos) const {
	Quaternion p = (pos);
	Quaternion result = *this * p * (*this).Inverse();
	return Vec3(result[1], result[2], result[3]);
}

Quaternion Quaternion::Unit(const Quaternion& quat) {
	return quat * (1 / quat.Length());
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

float& Quaternion::operator[](const int index) {
	if (index == 0)
		return r;
	return i[index - 1];
}

float Quaternion::operator[](const int index) const {
	if (index == 0)
		return r;
	return i[index - 1];
}

float Quaternion::Real(void) const {
	return r;
}

Vec3 Quaternion::Imaginary(void) const {
	return i;
}
