#pragma once

#include "Mat3.h"
#include "Vec4.h"
#include "Vec3.h"
#include "Quaternion.h"

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
	Mat4(const Quaternion& q);

	Vec4 Row(const int index);
	Vec4 Column(const int index);

	Mat4 GetInverse(void) const;
	Mat4 GetTranspose(void) const;

	void Invert(void);
	void Transpose(void);
	void Translate(const Vec3& pos);
	void Scale(const Vec3& pos);
	float Determinant(void);

	static Mat4 TranslateMatrix(const Vec3& pos);
	static Mat4 ScaleMatrix(const Vec3& scale);
	static Mat4 Perspective(const float aspect, 
		                    const float vertFOV, 
		                    const float nearPlane, 
		                    const float farPlane);

	static Mat4 Orthographic(const float aspect,
		                     const float vertFOV,
		                     const float nearPlane,
		                     const float farPlane);

	static Mat4 LookAt(Vec3 eye, Vec3 at, Vec3 up);

	Mat4& operator=(const Mat4& other);

	Mat4  operator+(const Mat4& other) const;
	Mat4& operator+=(const Mat4& other);

	Mat4  operator*(const Mat4& other) const;
	Mat4& operator*=(const Mat4& other);
	Mat4  operator*(const float& scale) const;
	Mat4& operator*=(const float& scale);
	Mat4  operator/(const float& scale) const;
	Mat4& operator/=(const float& scale);

	Vec4& operator[](const int index);
	Vec4  operator[](const int index) const;

	Vec4 M[4];

private:
	void SetErrorMat(void);
};

// inline implementation
inline Vec4 Mat4::Row(const int index) {
	return Vec4(M[0][index], M[1][index], M[2][index], M[3][index]);
}

inline Vec4 Mat4::Column(const int index) {
	return M[index];
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
inline void Mat4::Translate(const Vec3& pos) {
	M[3][0] += pos[0];
	M[3][1] += pos[1];
	M[3][2] += pos[2];
}

inline void Mat4::Scale(const Vec3& scale) {
	M[0] *= scale[0];
	M[1] *= scale[1];
	M[2] *= scale[2];
}

inline Mat4 Mat4::TranslateMatrix(const Vec3& val) {
	return Mat4(val);
}

inline Mat4 Mat4::ScaleMatrix(const Vec3& scale) {
	Mat4 temp;
	temp[0][0] = scale[0];
	temp[1][1] = scale[1];
	temp[2][2] = scale[2];
	return temp;
}

inline Vec4& Mat4::operator[](const int index) {
	return M[index];
}

inline Vec4 Mat4::operator[](const int index) const {
	return M[index];
}
