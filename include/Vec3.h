#pragma once
#include <math.h>
#include <iostream>
#include <string>

class Vec2;
class Vec4;

class Vec3 {
public:
	Vec3(void);
	Vec3(const float x, const float y, const float z);
	Vec3(const Vec3& other);
	Vec3(const Vec2& vec2);
	Vec3(const Vec4& vec4);

	std::string to_string(bool brackets=true);

	bool IsLeftOf(const Vec3& other) const;

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
	const float& operator[](const int index) const;

	bool operator==(const Vec3& other) const;

	float x;
	float y;
	float z;
};

inline std::string Vec3::to_string(bool brackets)
{
	if (brackets)
		return "(" + std::to_string(x) + ", " + 
					 std::to_string(y) + ", " +
					 std::to_string(z) + ")";
	return std::to_string(x) + ", " +
		   std::to_string(y) + ", " +
		   std::to_string(z);
}

inline float Vec3::Length() const {
	return sqrtf(x * x + y * y + z * z);
}

inline float Vec3::Dot(const Vec3& other) const {
	return x * other.x + y * other.y + z * other.z;
}

inline bool Vec3::IsLeftOf(const Vec3& other) const
{
	return Cross(other).y > 0;
}

inline Vec3& Vec3::operator=(const Vec3& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

inline Vec3 Vec3::operator+(const Vec3& other) const {
	Vec3 temp;
	temp.x = x + other.x;
	temp.y = y + other.y;
	temp.z = z + other.z;
	return temp;
}

inline Vec3& Vec3::operator+=(const Vec3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

inline Vec3 Vec3::operator-(const Vec3& other) const {
	Vec3 temp;
	temp.x = x - other.x;
	temp.y = y - other.y;
	temp.z = z - other.z;
	return temp;
}

inline Vec3& Vec3::operator-=(const Vec3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

inline Vec3 Vec3::operator*(const float scale) const {
	Vec3 temp;
	temp.x = x * scale;
	temp.y = y * scale;
	temp.z = z * scale;
	return temp;
}

inline Vec3& Vec3::operator*=(const float scale) {
	x *= scale;
	y *= scale;
	z *= scale;
	return *this;
}

inline Vec3 Vec3::operator/(const float scale) const {
	Vec3 temp;
	if (scale != 0.0f) {
		temp.x = x / scale;
		temp.y = y / scale;
		temp.z = z / scale;
	}
	else
		std::cout << "DIVISION BY ZERO" << std::endl;
	return temp;
}

inline Vec3& Vec3::operator/=(const float scale) {
	if (scale != 0.0f) {
		x /= scale;
		y /= scale;
		z /= scale;
	}
	else
		std::cout << "DIVISION BY ZERO" << std::endl;
	return *this;
}

inline float& Vec3::operator[](const int index) {
	if (index == 0)
		return x;
	if (index == 1)
		return y;
	return z;
}

inline const float& Vec3::operator[](const int index) const {
	if (index == 0)
		return x;
	if (index == 1)
		return y;
	return z;
}

inline bool Vec3::operator==(const Vec3& other) const
{
	return (x == other.x) && (y == other.y) && (z == other.z);
}

