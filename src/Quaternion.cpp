#include "Quaternion.h"
#include <math.h>

Quaternion::Quaternion(void) {
	r = 1.0;
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Quaternion::Quaternion(const float r, const float x, const float y, const float z) {
	this->r = r;
	this->x = x;
	this->y = y;
	this->z = z;
}

Quaternion::Quaternion(const Quaternion& other) {
	r = other.r;
	x = other.x;
	y = other.y;
	z = other.z;
}

Quaternion::Quaternion(const Vec3& pos) {
	r = 0.0;
	x = pos.x;
	y = pos.y;
	z = pos.z;
}

Quaternion::Quaternion(const float theta, const Vec3& axis) {
	r = cosf(theta/2);
	x = axis.x * sinf(theta / 2);
	y = axis.y * sinf(theta / 2);
	z = axis.z * sinf(theta / 2);
}

float Quaternion::Dot(const Quaternion& other) {
	return (r * other.r) + 
		   (x * other.x) + 
		   (y * other.y) + 
		   (z * other.z);
}

float Quaternion::Length(void) const {
	return sqrtf((r * r) + (x * x) +
				 (y * y) + (z * z));
}

float Quaternion::Length2(void) const {
	return (r * r) + 
		   (x * x) +
		   (y * y) + 
		   (z * z);
}

Quaternion Quaternion::Inverse(void) const {
	float scalar = 1 / Length2();
	Quaternion conj(r, -x, -y, -z);
	return conj * scalar;
}

Vec3 Quaternion::Rotate(const Vec3& pos) const {
	Quaternion p = (pos);
	Quaternion result = *this * p * (*this).Inverse();
	return Vec3(result.x, result.y, result.z);
}
