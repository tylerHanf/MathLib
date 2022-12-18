/***************************************
	Defines basic 2-vector Math
****************************************/
#pragma once
#include <math.h>
#include <string>

class Vec3;
class Vec4;

class Vec2 {
public:
	Vec2(void);
	Vec2(const float x, const float y);
	Vec2(const Vec2& other);
	Vec2(const Vec3& other);
	Vec2(const Vec4& other);

	std::string to_string(bool brackets=true);

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

	bool operator==(const Vec2& other) const;

	float x;
	float y;
};

inline std::string Vec2::to_string(bool brackets)
{
	if (brackets)
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	return std::to_string(x) + ", " + std::to_string(y);
}

inline float Vec2::Length() const {
	return sqrtf(x * x + y * y);
}

inline float Vec2::Dot(const Vec2& other) const {
	return x * other.x + y * other.y;
}

inline Vec2& Vec2::operator=(const Vec2& other) {
	x = other.x;
	y = other.y;
	return *this;
}

inline Vec2 Vec2::operator+(const Vec2& other) const {
	Vec2 temp;
	temp.x = x + other.x;
	temp.y = y + other.y;
	return temp;
}

inline Vec2& Vec2::operator+=(const Vec2& other) {
	x = x + other.x;
	y = y + other.y;
	return *this;
}

inline Vec2 Vec2::operator-(const Vec2& other) const {
	Vec2 temp;
	temp.x = x - other.x;
	temp.y = y - other.y;
	return temp;
}

inline Vec2& Vec2::operator-=(const Vec2& other) {
	x = x - other.x;
	y = y - other.y;
	return *this;
}

inline Vec2 Vec2::operator*(const float scale) const {
	Vec2 temp;
	temp.x = x * scale;
	temp.y = y * scale;
	return temp;
}

inline Vec2& Vec2::operator*=(const float scale) {
	x *= scale;
	y *= scale;
	return *this;
}

inline Vec2 Vec2::operator/(const float scale) const {
	Vec2 temp;
	temp.x = x / scale;
	temp.y = y / scale;
	return temp;
}

inline Vec2& Vec2::operator/=(const float scale) {
	x /= scale;
	y /= scale;
	return *this;
}

inline float& Vec2::operator[](const int index) {
	return index ? y : x;
}

inline float Vec2::operator[](const int index) const {
	return index ? y : x;
}

inline bool Vec2::operator==(const Vec2& other) const
{
	return (x == other.x) && (y == other.y);
}
