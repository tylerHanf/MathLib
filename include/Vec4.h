#pragma once
#include <math.h>

class Vec2;
class Vec3;

class Vec4 {
public:
	Vec4(void);
	Vec4(const float x, const float y, const float z, const float w);
	Vec4(const Vec4& other);
	Vec4(const Vec2& vec2);
	Vec4(const Vec3& vec3);
	Vec4(const Vec3& vec3, const float w);

	float Length(void) const;
	void  Normalize(void);
	float Dot(const Vec4& other) const;

	static Vec4 Unit(const Vec4& other);

	Vec4& operator=(const Vec4& other);

	Vec4  operator+(const Vec4& other) const;
	Vec4& operator+=(const Vec4& other);

	Vec4  operator-(const Vec4& other) const;
	Vec4& operator-=(const Vec4& other);

	Vec4  operator*(const float scale) const;
	Vec4& operator*=(const float scale);

	Vec4  operator/(const float scale) const;
	Vec4& operator/=(const float scale);

	float& operator[](const int index);
	float  operator[](const int index) const;

	float vec[4];
};

inline float Vec4::Length() const {
	return sqrtf(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2] + vec[3] * vec[3]);
}

inline float Vec4::Dot(const Vec4& other) const {
	return vec[0] * other.vec[0] + vec[1] * other.vec[1] + vec[2] * other.vec[2] + vec[3] * other.vec[3];
}
