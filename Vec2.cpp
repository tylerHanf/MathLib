/*********************************************
	Implements basic 2-vector Math
**********************************************/
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include <math.h>

Vec2::Vec2() {
	vec[0] = 0.0f;
	vec[1] = 0.0f;
}

Vec2::Vec2(const float x, const float y) {
	vec[0] = x;
	vec[1] = y;
}

Vec2::Vec2(const Vec2& other) {
	vec[0] = other.vec[0];
	vec[1] = other.vec[1];
}

Vec2::Vec2(const Vec3& vec3) {
	vec[0] = vec3[0];
	vec[1] = vec3[1];
}

Vec2::Vec2(const Vec4& vec4) {
	vec[0] = vec4[0];
	vec[1] = vec4[1];
}

void Vec2::Normalize() {
	float len = Length();
	vec[0] /= len;
	vec[1] /= len;
}

Vec2 Vec2::Unit(const Vec2& vector) {
	Vec2 temp;
	float length = vector.Length();
	temp.vec[0] = vector.vec[0] / length;
	temp.vec[1] = vector.vec[1] / length;
	return temp;
}


Vec2& Vec2::operator=(const Vec2& other) {
	vec[0] = other.vec[0];
	vec[1] = other.vec[1];
	return *this;
}

Vec2 Vec2::operator+(const Vec2& other) const {
	Vec2 temp;
	temp.vec[0] = vec[0] + other.vec[0];
	temp.vec[1] = vec[1] + other.vec[1];
	return temp;
}

Vec2& Vec2::operator+=(const Vec2& other) {
	vec[0] = vec[0] + other.vec[0];
	vec[1] = vec[1] + other.vec[1];
	return *this;
}

Vec2 Vec2::operator-(const Vec2& other) const {
	Vec2 temp;
	temp.vec[0] = vec[0] - other.vec[0];
	temp.vec[1] = vec[1] - other.vec[1];
	return temp;
}

Vec2& Vec2::operator-=(const Vec2& other) {
	vec[0] = vec[0] - other.vec[0];
	vec[1] = vec[1] - other.vec[1];
	return *this;
}

Vec2 Vec2::operator*(const float scale) const {
	Vec2 temp;
	temp.vec[0] *= scale;
	temp.vec[1] *= scale;
	return temp;
}

Vec2& Vec2::operator*=(const float scale) {
	vec[0] *= scale;
	vec[1] *= scale;
	return *this;
}

Vec2 Vec2::operator/(const float scale) const {
	Vec2 temp;
	if (scale != 0.0f) {
		temp.vec[0] /= scale;
		temp.vec[1] /= scale;
	}
	return temp;
}

Vec2& Vec2::operator/=(const float scale) {
	if (scale != 0.0f) {
		vec[0] /= scale;
		vec[1] /= scale;
	}
	return *this;
}

float& Vec2::operator[](const int index) {
	return vec[index];
}

float Vec2::operator[](const int index) const {
	return vec[index];
}
