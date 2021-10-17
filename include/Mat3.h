#pragma once
#include "Vec3.h"
#include "Quaternion.h"

class Mat3 {
public:
	Mat3(void);
	Mat3(const float x0, const float y0, const float z0,
		 const float x1, const float y1, const float z1,
		 const float x2, const float y2, const float z2);
	Mat3(Vec3& x, Vec3& y, Vec3& z);
	Mat3(const Mat3& other);
	Mat3(const Quaternion& q);

	Vec3 Row(const int index) const;
	Vec3 Column(const int index) const;

	Mat3 GetInverse(void) const;
	Mat3 GetTranspose(void) const;

	float Determinant(void) const;
	void Invert(void);
	void Transpose(void);
	static Mat3 ScaleMatrix(const Vec3& scale);

	Mat3& operator=(const Mat3& other);
	Mat3  operator+(const Mat3& other) const;
	Mat3& operator+=(const Mat3& other);
	Mat3  operator-(const Mat3& other) const;
	Mat3& operator-=(const Mat3& other);
	Mat3  operator*(const Mat3& other) const;
	Mat3& operator*=(const Mat3& other);
	Mat3  operator*(const float& other) const;
	Mat3& operator*=(const float& other);
	Mat3  operator/(const float& other) const;
	Mat3& operator/=(const float& other);
	Vec3& operator[](const int index);
	Vec3  operator[](const int index) const;

	Vec3 M[3];

private:
	Mat3 Adjoint(void);
	void SetErrorMat(void);
};

inline float Mat3::Determinant() const {
	float detI = M[0][0] * ((M[1][1] * M[2][2]) - (M[1][2] * M[2][1]));
	float detJ = M[0][1] * ((M[1][0] * M[2][2]) - (M[1][2] * M[2][0]));
	float detK = M[0][2] * ((M[1][0] * M[2][1]) - (M[1][1] * M[2][0]));
	return detI - detJ + detK;
}
