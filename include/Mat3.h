#pragma once
#include "Vec3.h"

class Mat3 {
public:
	Mat3(void);
	Mat3(const float x0, const float y0, const float z0,
		 const float x1, const float y1, const float z1,
		 const float x2, const float y2, const float z2);
	Mat3(Vec3& x, Vec3& y, Vec3& z);
	Mat3(const Mat3& other);

	Vec3 Row(const int index) const;
	Vec3 Column(const int index) const;

	Mat3 GetInverse(void) const;
	Mat3 GetTranspose(void) const;

	void Invert(void);
	void Transpose(void);
	// let quats handle this?
	//void  Rotate(const float x, const float y, const float z);

	static Mat3 ScaleMatrix(const float x, const float y, const float z);

	Mat3& operator=(const Mat3& other);
	Mat3  operator+(const Mat3& other) const;
	Mat3& operator+=(const Mat3& other);
	Mat3  operator-(const Mat3& other) const;
	Mat3& operator-=(const Mat3& other);
	Mat3  operator*(const Mat3& other) const;
	Mat3& operator*=(const Mat3& other);
	Vec3& operator[](const int index);
	Vec3  operator[](const int index) const;

	Vec3 M[3];
};
