#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include <math.h>

Vec4::Vec4() {
	vec[0] = 0.0f;
	vec[1] = 0.0f;
	vec[2] = 0.0f;
	vec[3] = 0.0f;
}

Vec4::Vec4(const float x, const float y, const float z, const float w) {
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	vec[3] = w;
}

Vec4::Vec4(const Vec4& other) {
	vec[0] = other.vec[0];
	vec[1] = other.vec[1];
	vec[2] = other.vec[2];
	vec[3] = other.vec[3];
}

Vec4::Vec4(const Vec2& vec2) {
	vec[0] = vec2.vec[0];
	vec[1] = vec2.vec[1];
	vec[2] = 0.0f;
	vec[3] = 0.0f;
}

Vec4::Vec4(const Vec3& vec3) {
	vec[0] = vec3.vec[0];
	vec[1] = vec3.vec[1];
	vec[2] = vec3.vec[2];
	vec[3] = 0.0f;
}

Vec4::Vec4(const Vec3& vec3, const float w) {
	vec[0] = vec3.vec[0];
	vec[1] = vec3.vec[1];
	vec[2] = vec3.vec[2];
	vec[3] = w;
}

void Vec4::Normalize() {
	float length = Length();
	vec[0] /= length;
	vec[1] /= length;
	vec[2] /= length;
	vec[3] /= length;
}

Vec4 Vec4::Unit(const Vec4& other) {
	Vec4 temp;
	float length = other.Length();

	temp.vec[0] = other.vec[0] / length;
	temp.vec[1] = other.vec[1] / length;
	temp.vec[2] = other.vec[2] / length;
	temp.vec[3] = other.vec[3] / length;
	return temp;
}

Vec4& Vec4::operator=(const Vec4& other) {
	vec[0] = other.vec[0];
	vec[1] = other.vec[1];
	vec[2] = other.vec[2];
	vec[3] = other.vec[3];
	return *this;
}

Vec4 Vec4::operator+(const Vec4& other) const {
	Vec4 temp;
	temp.vec[0] = vec[0] + other.vec[0];
	temp.vec[1] = vec[1] + other.vec[1];
	temp.vec[2] = vec[2] + other.vec[2];
	temp.vec[3] = vec[3] + other.vec[3];
	return temp;
}

Vec4& Vec4::operator+=(const Vec4& other) {
	vec[0] += other.vec[0];
	vec[1] += other.vec[1];
	vec[2] += other.vec[2];
	vec[3] += other.vec[3];
	return *this;
}

Vec4 Vec4::operator-(const Vec4& other) const {
	Vec4 temp;
	temp.vec[0] = vec[0] - other.vec[0];
	temp.vec[1] = vec[1] - other.vec[1];
	temp.vec[2] = vec[2] - other.vec[2];
	temp.vec[3] = vec[3] - other.vec[3];
	return temp;
}

Vec4& Vec4::operator-=(const Vec4& other) {
	vec[0] -= other.vec[0];
	vec[1] -= other.vec[1];
	vec[2] -= other.vec[2];
	vec[3] -= other.vec[3];
	return *this;
}

Vec4 Vec4::operator*(const float scale) const {
	Vec4 temp;
	temp.vec[0] = vec[0] * scale;
	temp.vec[1] = vec[1] * scale;
	temp.vec[2] = vec[2] * scale;
	temp.vec[3] = vec[3] * scale;
	return temp;
}

Vec4& Vec4::operator*=(const float scale) {
	vec[0] *= scale;
	vec[1] *= scale;
	vec[2] *= scale;
	return *this;
}

Vec4 Vec4::operator/(const float scale) const {
	Vec4 temp;
	if (scale != 0.0f) {
		temp.vec[0] = vec[0] / scale;
		temp.vec[1] = vec[1] / scale;
		temp.vec[2] = vec[2] / scale;
		temp.vec[3] = vec[3] / scale;
	}
	return temp;
}

Vec4& Vec4::operator/=(const float scale) {
	if (scale != 0.0f) {
		vec[0] /= scale;
		vec[1] /= scale;
		vec[2] /= scale;
		vec[3] /= scale;
	}
	return *this;
}

float& Vec4::operator[](const int index) {
	return vec[index];
}

float Vec4::operator[](const int index) const {
	return vec[index];
}
