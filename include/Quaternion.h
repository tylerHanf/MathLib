#pragma once
#include "Vec3.h"
#include "Vec4.h"

class Mat4;

class Quaternion {
public:
	Quaternion(void);
	Quaternion(const float w, const float x, const float y, const float z);
	Quaternion(const Vec3& pos);
	Quaternion(const float theta, const Vec3& axis);
	Quaternion(const Quaternion& other);

	Quaternion Conjugate(void) const;
	Quaternion Inverse(void) const;
	float      Dot(const Quaternion& other);
	Vec3       Rotate(const Vec3& pos) const;
	float      Length(void) const;
	float      Length2(void) const;

	static Quaternion Unit(const Quaternion& quat);
	
	Quaternion  operator*(const Quaternion& other) const;
	Quaternion  operator*(const float scalar) const;
	Quaternion& operator*=(const Quaternion& other);
	Quaternion& operator*=(const float scalar);

	Quaternion  operator+(const Quaternion& other) const;
	Quaternion& operator+=(const Quaternion& other);
	float&      operator[](const int index);
	float       operator[](const int index) const;

	float Real(void) const;
	Vec3  Imaginary(void) const;

	float r;
	Vec3  i;
};
