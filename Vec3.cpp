#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include <math.h>

Vec3::Vec3() {
	vec[0] = 0.0f;
	vec[1] = 0.0f;
	vec[2] = 0.0f;
}

Vec3::Vec3(const float x, const float y, const float z) {
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}

Vec3::Vec3(const Vec3& other) {
	vec[0] = other.vec[0];
	vec[1] = other.vec[1];
	vec[2] = other.vec[2];
}

Vec3::Vec3(const Vec2& vec2) {
	vec[0] = vec2[0];
	vec[1] = vec2[1];
	vec[2] = 0.0f;
}

Vec3::Vec3(const Vec4& vec4) {
	vec[0] = vec4[0];
	vec[1] = vec4[1];
	vec[2] = 0.0f;
}

void Vec3::Normalize() {
	float length = Length();
	vec[0] /= length;
	vec[1] /= length;
	vec[2] /= length;
}

Vec3 Vec3::Unit(const Vec3& other) {
	Vec3 temp;
	float length = other.Length();

	temp.vec[0] = other.vec[0] / length;
	temp.vec[1] = other.vec[1] / length;
	temp.vec[2] = other.vec[2] / length;
	return temp;
}

Vec3 Vec3::Cross(const Vec3& other) const {
	Vec3 temp;
	temp.vec[0] = (vec[1] * other.vec[2]) - (vec[2] * other.vec[1]);
	temp.vec[1] = (vec[2] * other.vec[0]) - (vec[0] * other.vec[2]);
	temp.vec[2] = (vec[0] * other.vec[1]) - (vec[1] * other.vec[0]);
	return temp;
}

Vec3& Vec3::operator=(const Vec3& other) {
	vec[0] = other.vec[0];
	vec[1] = other.vec[1];
	vec[2] = other.vec[2];
	return *this;
}

Vec3 Vec3::operator+(const Vec3& other) const {
	Vec3 temp;
	temp.vec[0] = vec[0] + other.vec[0];
	temp.vec[1] = vec[1] + other.vec[2];
	temp.vec[2] = vec[2] + other.vec[2];
	return temp;
}

Vec3& Vec3::operator+=(const Vec3& other) {
	vec[0] += other.vec[0];
	vec[1] += other.vec[1];
	vec[2] += other.vec[2];
	return *this;
}

Vec3 Vec3::operator-(const Vec3& other) const {
	Vec3 temp;
	temp.vec[0] = vec[0] - other.vec[0];
	temp.vec[1] = vec[1] - other.vec[1];
	temp.vec[2] = vec[2] - other.vec[2];
	return temp;
}

Vec3& Vec3::operator-=(const Vec3& other) {
	vec[0] -= other.vec[0];
	vec[1] -= other.vec[1];
	vec[2] -= other.vec[2];
	return *this;
}

Vec3 Vec3::operator*(const float scale) const {
	Vec3 temp;
	temp.vec[0] = vec[0] * scale;
	temp.vec[1] = vec[1] * scale;
	temp.vec[2] = vec[2] * scale;
	return temp;
}

Vec3& Vec3::operator*=(const float scale) {
	vec[0] *= scale;
	vec[1] *= scale;
	vec[2] *= scale;
	return *this;
}

Vec3 Vec3::operator/(const float scale) const {
	Vec3 temp;
	if (scale != 0.0f) {
		temp.vec[0] = vec[0] / scale;
		temp.vec[1] = vec[1] / scale;
		temp.vec[2] = vec[2] / scale;
	}
	return temp;
}

Vec3& Vec3::operator/=(const float scale) {
	if (scale != 0.0f) {
		vec[0] /= scale;
		vec[1] /= scale;
		vec[2] /= scale;
	}
	return *this;
}

float& Vec3::operator[](const int index) {
	return vec[index];
}

float Vec3::operator[](const int index) const {
	return vec[index];
}
