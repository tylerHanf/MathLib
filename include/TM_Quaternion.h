#pragma once
#include "Vec3.h"
#include "Vec4.h"
#include <string>

class Mat4;

class Quaternion {
public:
	Quaternion(void);
	Quaternion(const float r, const float x, const float y, const float z);
	Quaternion(const Vec3& pos);
	Quaternion(const float theta, const Vec3& axis);
	Quaternion(const Quaternion& other);

	std::string to_string(void);

	Quaternion Conjugate(void) const;
	Quaternion Inverse(void) const;
	float      Dot(const Quaternion& other);
	Vec3       Rotate(const Vec3& pos) const;
	float      Length(void) const;
	float      Length2(void) const;
	void       Normalize(void);

	static Quaternion Unit(const Quaternion& quat);
	
	Quaternion  operator*(const Quaternion& other) const;
	Quaternion  operator*(const float scalar) const;
	Quaternion& operator*=(const Quaternion& other);
	Quaternion& operator*=(const float scalar);

	Quaternion  operator+(const Quaternion& other) const;
	Quaternion& operator+=(const Quaternion& other);

	float&      operator[](const int index);
	float       operator[](const int index) const;

	bool        operator==(const Quaternion& other) const;

	float Real(void) const;
	Vec3  Imaginary(void) const;

	float r;
	float x;
	float y;
	float z;
};

inline std::string Quaternion::to_string(void)
{
	return "(" + std::to_string(r) + ", " +
		         std::to_string(x) + ", " +
		         std::to_string(y) + ", " +
		         std::to_string(z) + ")";
}

inline void Quaternion::Normalize(void)
{
	*this *= (1 / Length());
}

inline Quaternion Quaternion::Unit(const Quaternion& quat) {
	return quat * (1 / quat.Length());
}

inline Quaternion Quaternion::Conjugate(void) const {
	return Quaternion(r, -x, -y, -z);
}

inline Quaternion Quaternion::operator*(const Quaternion& other) const {
	float r_new = (r * other.r) - 
		          (x * other.x) - 
		          (y * other.y) - 
		          (z * other.z);

	float x_new = (y * other.z) -
		          (z * other.y) +
			      (x * other.r) +
			      (r * other.x);

	float y_new = (z * other.x) -
			      (x * other.z) +
			      (y * other.r) +
			      (r * other.y);

	float z_new = (x * other.y) -
			      (y * other.x) +
			      (z * other.r) +
			      (r * other.z);

	return Quaternion(r_new, x_new, y_new, z_new);
}

inline Quaternion Quaternion::operator*(const float scalar) const {
	float r_new = r * scalar;
	float x_new = x * scalar;
	float y_new = y * scalar;
	float z_new = z * scalar;

	return Quaternion(r_new, x_new, y_new, z_new);
}

inline Quaternion& Quaternion::operator*=(const Quaternion& other) {
	float r_new = (r * other. r) -
		          (x * other.x) -
		          (y * other.y) - 
		          (z * other.z);

	float x_new = (y * other.z) -
			      (z * other.y) +
			      (x * other.r) +
			      (r * other.x);

	float y_new = (z * other.x) -
			      (x * other.z) +
			      (y * other.r) +
			      (r * other.y);

	float z_new = (x * other.y) -
			      (y * other.x) +
			      (z * other.r) +
			      (r * other.z);

	r = r_new; x = x_new; y = y_new; z = z_new;

	return *this;
}

inline Quaternion& Quaternion::operator*=(const float scalar) {
	r *= scalar;
	x *= scalar;
	y *= scalar;
	z *= scalar;
	
	return *this;
}

inline Quaternion Quaternion::operator+(const Quaternion& other) const {
	float r_new = r + other.r;
	float x_new = x + other.x;
	float y_new = y + other.y;
	float z_new = z + other.z;
	return Quaternion(r_new, x_new, y_new, z_new);
}

inline Quaternion& Quaternion::operator+=(const Quaternion& other) {
	r += other.r;
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

inline float& Quaternion::operator[](const int index) {
	if (index == 0)
		return r;
	if (index == 1)
		return x;
	if (index == 2)
		return y;
	return z;
}

inline float Quaternion::operator[](const int index) const {
	if (index == 0)
		return r;
	if (index == 1)
		return x;
	if (index == 2)
		return y;
	return z;
}

inline float Quaternion::Real(void) const {
	return r;
}

inline Vec3 Quaternion::Imaginary(void) const {
	return Vec3(x, y, z);
}

inline bool Quaternion::operator==(const Quaternion& other) const {
	return (r == other.r) && (x == other.x) && (y == other.y) && (z == other.z);
}
