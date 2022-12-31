#pragma once
#include <math.h>
#include <string>

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

	std::string to_string(bool brackets=true);

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
	const float& operator[](const int index) const;

	bool operator==(const Vec4& other) const;

	float x;
	float y;
	float z;
	float w;
};

inline std::string Vec4::to_string(bool brackets)
{
	if (brackets)
		return "(" + std::to_string(x) + ", " +
					 std::to_string(y) + ", " +
					 std::to_string(z) + ", " +
					 std::to_string(w) + ")";

	return std::to_string(x) + ", " +
		std::to_string(y) + ", " +
		std::to_string(z) + ", " +
		std::to_string(w);
}

inline float Vec4::Length() const {
	return sqrtf(x * x + y * y + z * z + w * w);
}

inline float Vec4::Dot(const Vec4& other) const {
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

inline Vec4& Vec4::operator=(const Vec4& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return *this;
}

inline Vec4 Vec4::operator+(const Vec4& other) const {
	Vec4 temp;
	temp.x = x + other.x;
	temp.y = y + other.y;
	temp.z = z + other.z;
	temp.w = w + other.w;
	return temp;
}

inline Vec4& Vec4::operator+=(const Vec4& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

inline Vec4 Vec4::operator-(const Vec4& other) const {
	Vec4 temp;
	temp.x = x - other.x;
	temp.y = y - other.y;
	temp.z = z - other.z;
	temp.w = w - other.w;
	return temp;
}

inline Vec4& Vec4::operator-=(const Vec4& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

inline Vec4 Vec4::operator*(const float scale) const {
	Vec4 temp;
	temp.x = x * scale;
	temp.y = y * scale;
	temp.z = z * scale;
	temp.w = w * scale;
	return temp;
}

inline Vec4& Vec4::operator*=(const float scale) {
	x *= scale;
	y *= scale;
	z *= scale;
	w *= scale;
	return *this;
}

inline Vec4 Vec4::operator/(const float scale) const {
	Vec4 temp;
	if (scale != 0.0f) {
		temp.x = x / scale;
		temp.y = y / scale;
		temp.z = z / scale;
		temp.w = w / scale;
	}
	else
		std::cout << "DIVISION BY 0" << std::endl;
	return temp;
}

inline Vec4& Vec4::operator/=(const float scale) {
	if (scale != 0.0f) {
		x /= scale;
		y /= scale;
		z /= scale;
		w /= scale;
	}
	else
		std::cout << "DIVISION BY 0" << std::endl;
	return *this;
}

inline float& Vec4::operator[](const int index) {
	if (index == 0)
		return x;
	if (index == 1)
		return y;
	if (index == 2)
		return z;
	return w;
}

inline const float& Vec4::operator[](const int index) const {
	if (index == 0)
		return x;
	if (index == 1)
		return y;
	if (index == 2)
		return z;
	return w;
}

inline bool Vec4::operator==(const Vec4& other) const {
	return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
}
