#pragma once
#include <math.h>

class Vec2;
class Vec4;

class Vec3 {
public:
	Vec3(void);
	Vec3(const float x, const float y, const float z);
	Vec3(const Vec3& other);
	Vec3(const Vec2& vec2);
	Vec3(const Vec4& vec4);

	float Length(void) const;
	void  Normalize(void);
	float Dot(const Vec3& other) const;
	Vec3  Cross(const Vec3& other) const;

	static Vec3 Unit(const Vec3& other);

	Vec3& operator=(const Vec3& other);

	Vec3  operator+(const Vec3& other) const;
	Vec3& operator+=(const Vec3& other);

	Vec3  operator-(const Vec3& other) const;
	Vec3& operator-=(const Vec3& other);

	Vec3  operator*(const float scale) const;
	Vec3& operator*=(const float scale);

	Vec3  operator/(const float scale) const;
	Vec3& operator/=(const float scale);

	float& operator[](const int index);
	float  operator[](const int index) const;

	float vec[3];
};

inline float Vec3::Length() const {
	return sqrtf(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

inline float Vec3::Dot(const Vec3& other) const {
	return vec[0] * other.vec[0] + vec[1] * other.vec[1] + vec[2] * other.vec[2];
}
