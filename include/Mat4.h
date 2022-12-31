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

	std::string to_string(void);

	Vec4 Row(const int index);
	Vec4 Column(const int index);

	Mat4 GetInverse(void) const;
	Mat4 GetTranspose(void) const;

	void Invert(void);
	void Transpose(void);
	void Translate(const Vec3& pos);
	void Scale(const Vec3& pos);
	float Determinant(void);

	float* Ptr(void);
	const float* ConstPtr(void) const;

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
	const Vec4&  operator[](const int index) const;

	Vec4 M[4];

private:
	void SetErrorMat(void);
};

inline float* Mat4::Ptr(void)
{
	return &(M[0].x);
}

inline const float* Mat4::ConstPtr(void) const
{
	return &(M[0].x);
}

// inline implementation
inline std::string Mat4::to_string(void)
{
	std::string str;
	str = "(";
	str += M[0].to_string(false) + ",\n";
	str += M[1].to_string(false) + ",\n";
	str += M[2].to_string(false) + ",\n";
	str += M[3].to_string(false) + ")";

	return str;
}

inline Vec4 Mat4::Row(const int index) {
	return M[index];
}

inline Vec4 Mat4::Column(const int index) {
	return Vec4(M[0][index], M[1][index], M[2][index], M[3][index]);
}

inline void Mat4::Transpose() {
	float temp = M[0].y;
	M[0].y = M[1].x;
	M[1].x = temp;

	temp = M[0].z;
	M[0].z = M[2].x;
	M[2].y = temp;

	temp = M[0].w;
	M[0].w = M[3].x;
	M[3].x = temp;

	temp = M[1].z;
	M[1].z = M[2].y;
	M[2].y = temp;

	temp = M[1].w;
	M[1].w = M[3].y;
	M[3].y = temp;

	temp = M[2].w;
	M[2].w = M[3].z;
	M[3].z = temp;
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
	M[3].x += pos.x;
	M[3].y += pos.y;
	M[3].z += pos.z;
}

inline void Mat4::Scale(const Vec3& scale) {
	M[0] *= scale.x;
	M[1] *= scale.y;
	M[2] *= scale.z;
}

inline Mat4 Mat4::TranslateMatrix(const Vec3& val) {
	return Mat4(val);
}

inline Mat4 Mat4::ScaleMatrix(const Vec3& scale) {
	Mat4 temp;
	temp[0].x = scale.x;
	temp[1].y = scale.y;
	temp[2].z = scale.z;
	return temp;
}

inline Vec4& Mat4::operator[](const int index) {
	return M[index];
}

inline const Vec4& Mat4::operator[](const int index) const {
	return M[index];
}
