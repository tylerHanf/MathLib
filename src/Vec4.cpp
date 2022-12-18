#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include <math.h>

Vec4::Vec4() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

Vec4::Vec4(const float x, const float y, const float z, const float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vec4::Vec4(const Vec4& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

Vec4::Vec4(const Vec2& vec2) {
	x = vec2.x;
	y = vec2.y;
	z = 0.0f;
	w = 0.0f;
}

Vec4::Vec4(const Vec3& vec3) {
	x = vec3.x;
	y = vec3.y;
	z = vec3.z;
	w = 0.0f;
}

Vec4::Vec4(const Vec3& vec3, const float w) {
	x = vec3.x;
	y = vec3.y;
	z = vec3.z;
	this->w = w;
}

void Vec4::Normalize() {
	float length = Length();
	x /= length;
	y /= length;
	z /= length;
	w /= length;
}

Vec4 Vec4::Unit(const Vec4& other) {
	Vec4 temp;
	float length = other.Length();

	temp.x = other.x / length;
	temp.y = other.y / length;
	temp.z = other.z / length;
	temp.w = other.w / length;
	return temp;
}

