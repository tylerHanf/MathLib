/***************************************
	Defines basic 2-vector Math
****************************************/
#pragma once
#include <math.h>

class Vec3;
class Vec4;

class Vec2 {
public:
	Vec2(void);
	Vec2(const float x, const float y);
	Vec2(const Vec2& other);
	Vec2(const Vec3& other);
	Vec2(const Vec4& other);

	float Length(void) const;
	void  Normalize(void);
	float Dot(const Vec2& other) const;

	static Vec2 Unit(const Vec2& vector);

	Vec2& operator=(const Vec2& other);

	Vec2  operator+(const Vec2& other) const;
	Vec2& operator+=(const Vec2& other);

	Vec2  operator-(const Vec2& other) const;
	Vec2& operator-=(const Vec2& other);

	Vec2  operator*(const float scale) const;
	Vec2& operator*=(const float scale);

	Vec2  operator/(const float scale) const;
	Vec2& operator/=(const float scale);

	float& operator[](const int index);
	float  operator[](const int index) const;

	float vec[2];
};

inline float Vec2::Length() const {
	return sqrtf(vec[0] * vec[0] + vec[1] * vec[1]);
}

inline float Vec2::Dot(const Vec2& other) const {
	return vec[0] * other.vec[0] + vec[1] * other.vec[1];
}
