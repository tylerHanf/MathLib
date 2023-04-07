#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"
#include <math.h>

Vec3::Vec3() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vec3::Vec3(const float x, const float y, const float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3::Vec3(const Vec3& other) {
	x = other.x;
	y = other.y;
	z = other.z;
}

Vec3::Vec3(const Vec2& other) {
	x = other.x;
	y = other.y;
	z = 0.0f;
}

Vec3::Vec3(const Vec4& vec4) {
	x = vec4.x;
	y = vec4.y;
	z = vec4.z;
}

Vec3::Vec3(const Mat4& mat4)
{
	*this = mat4[3];
}

void Vec3::Normalize() {
	float length = Length();
	x /= length;
	y /= length;
	z /= length;
}

Vec3 Vec3::Unit(const Vec3& other) {
	Vec3 temp;
	float length = other.Length();

	temp.x = other.x / length;
	temp.y = other.y / length;
	temp.z = other.z / length;
	return temp;
}

Vec3 Vec3::Cross(const Vec3& other) const {
	Vec3 temp;
	temp.x = (y * other.z) - (z * other.y);
	temp.y = (z * other.x) - (x * other.z);
	temp.z = (x * other.y) - (y * other.x);
	return temp;
}
