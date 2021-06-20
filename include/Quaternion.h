#pragma once
#include "Mat4.h"
#include "Vec3.h"

class Quaternion {
public:
	Quaternion(void);
	Quaternion(const float w, const float x, const float y, const float z);
	Quaternion(const Vec3& pos);
	Quaternion(const float theta, const Vec3& axis);
	Quaternion(const Quaternion& other);

	Quaternion Conjugate(void) const;
	Quaternion Inverse(void) const;
	Quaternion Cross(const Quaternion& other);
	float      Dot(const Quaternion& other);
	Quaternion Rotate(const Quaternion& p, const Vec3 axis, float theta);
	Mat4       ToMat4(void) const;
	Mat3       ToMat3(void) const;
	float      Length(void);
	float      Norm(void) const;
	float      Norm2(void) const;

	static Quaternion Unit(const Quaternion& quat);
	
	Quaternion  operator*(const Quaternion& other) const;
	Quaternion  operator*(const float scalar) const;
	Quaternion& operator*=(const Quaternion& other);
	Quaternion& operator*=(const float scalar);

	Quaternion  operator+(const Quaternion& other) const;
	Quaternion& operator+=(const Quaternion& other);

	float Real(void) const;
	Vec3  Imaginary(void) const;

	float r;
	Vec3  i;
};
