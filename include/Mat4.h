#pragma once

#include "Mat3.h"
#include "Vec4.h"
#include "Vec3.h"

// Defs
class Mat4 {
public:
	Mat4(void);
	Mat4(const float x0, const float y0, const float z0, const float px,
		 const float x1, const float y1, const float z1, const float py,
		 const float x2, const float y2, const float z2, const float pz,
		 const float w0, const float w1, const float w2, const float w3);
	Mat4(const Mat4& other);
	Mat4(const Mat3& dcm, const Vec3& pos);
	Mat4(const Mat3& dcm);
	Mat4(const Vec3& pos);

	Vec4 Row(const int index);
	Vec4 Column(const int index);

	Mat4 GetInverse(void) const;
	Mat4 GetTranspose(void) const;

	void Invert(void);
	void Transpose(void);
	void Translate(const float x, const float y, const float z);
	void Scale(const float x, const float y, const float z);

	static Mat4 TranslateMatrix(const float x, const float y, const float z);
	static Mat4 ScaleMatrix(const float x, const float y, const float z);
	static Mat4 Perspective(const float a, const float n, const float f);
	static Mat4 Orthographic(const float a, const float n, const float f);
	static Mat4 LookAt(Vec3 eye, Vec3 at, Vec3 up);

	Mat4& operator=(const Mat4& other);

	Mat4  operator+(const Mat4& other) const;
	Mat4& operator+=(const Mat4& other);

	Mat4  operator*(const Mat4& other) const;
	Mat4& operator*=(const Mat4& other);

	Vec4& operator[](const int index);
	Vec4  operator[](const int index) const;

	Vec4 M[4];
};

// inline implementation
inline Vec4 Mat4::Row(const int index) {
	return M[index];
}

inline Vec4 Mat4::Column(const int index) {
	if (index == 0) {
		return Vec4(M[0][0], M[1][0], M[2][0], M[3][0]);
	}
	else if (index == 1) {
		return Vec4(M[0][1], M[1][1], M[2][1], M[3][1]);
	}
	else if (index == 2) {
		return Vec4(M[0][2], M[1][2], M[2][2], M[3][2]);
	}
	else if (index == 3) {
		return Vec4(M[0][3], M[1][3], M[2][3], M[3][3]);
	}
}

inline void Mat4::Transpose() {
	float temp = M[0][1];
	M[0][1] = M[1][0];
	M[1][0] = temp;

	temp = M[0][2];
	M[0][2] = M[2][0];
	M[2][1] = temp;

	temp = M[0][3];
	M[0][3] = M[3][0];
	M[3][0] = temp;

	temp = M[1][2];
	M[1][2] = M[2][1];
	M[2][1] = temp;

	temp = M[1][3];
	M[1][3] = M[3][1];
	M[3][1] = temp;

	temp = M[2][3];
	M[2][3] = M[3][2];
	M[3][2] = temp;
}

inline void Mat4::Invert() {
	return Transpose();
}

inline Mat4 Mat4::GetInverse() const {
	Mat4 temp = *this;
	temp.Invert();
	return temp;
}

inline Mat4 Mat4::GetTranspose() const {
	Mat4 temp = *this;
	temp.Transpose();
	return temp;
}

// Check
inline void Mat4::Translate(const float x, const float y, const float z) {
	M[0][3] += x;
	M[1][3] += y;
	M[2][3] += z;
}

inline void Mat4::Scale(const float x, const float y, const float z) {
	M[0][0] += x;
	M[1][1] += y;
	M[2][2] += z;
}

inline Mat4 Mat4::TranslateMatrix(const float x, const float y, const float z) {
	return Mat4(Vec3(x, y, z));
}

inline Mat4 Mat4::ScaleMatrix(const float x, const float y, const float z) {
	return Mat4(Mat3::ScaleMatrix(x, y, z), Vec3(0.0f, 0.0f, 0.0f));
}

inline Vec4& Mat4::operator[](const int index) {
	return M[index];
}

inline Vec4 Mat4::operator[](const int index) const {
	return M[index];
}
