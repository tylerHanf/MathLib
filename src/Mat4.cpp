#include "Mat4.h"
#include "Mat3.h"
#include "Logger.h"
#include <math.h>

Mat4::Mat4() {
	M[0] = Vec4(1.0f, 0.0f, 0.0f, 0.0f);
	M[1] = Vec4(0.0f, 1.0f, 0.0f, 0.0f);
	M[2] = Vec4(0.0f, 0.0f, 1.0f, 0.0f);
	M[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4::Mat4(const float x0, const float x1, const float x2, const float w0,
	       const float y0, const float y1, const float y2, const float w1,
	       const float z0, const float z1, const float z2, const float w2,
	       const float px, const float py, const float pz, const float w3)
{
	M[0] = Vec4(x0, x1, x2, w0);
	M[1] = Vec4(y0, y1, y2, w1);
	M[2] = Vec4(z0, z1, z2, w2);
	M[3] = Vec4(px, py, pz, w3);
}

Mat4::Mat4(const Mat4& other) {
	M[0] = other.M[0];
	M[1] = other.M[1];
	M[2] = other.M[2];
	M[3] = other.M[3];
}

Mat4::Mat4(const Mat3& dcm, const Vec3& pos) {
	M[0] = Vec4(dcm.M[0], 0.0f);
	M[1] = Vec4(dcm.M[1], 0.0f);
	M[2] = Vec4(dcm.M[2], 0.0f);
	M[3] = Vec4(pos[0], pos[1], pos[2], 1.0f);
}

Mat4::Mat4(const Mat3& dcm) {
	M[0] = Vec4(dcm.M[0], 0.0);
	M[1] = Vec4(dcm.M[1], 0.0);
	M[2] = Vec4(dcm.M[2], 0.0);
	M[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4::Mat4(const Vec3& pos) {
	M[0] = Vec4(1.0f, 0.0f, 0.0f, 0.0f);
	M[1] = Vec4(0.0f, 1.0f, 0.0f, 0.0f);
	M[2] = Vec4(0.0f, 0.0f, 1.0f, 0.0f);
	M[3] = Vec4(pos[0], pos[1], pos[2], 1.0f);
}

Mat4::Mat4(const Quaternion& q) {
	Vec3 i = q.i;
	float r = q.r;
	float x2 = i[0] * i[0];
	float y2 = i[1] * i[1];
	float z2 = i[2] * i[2];

	M[0][0] = 1 - 2 * y2 - 2 * z2;
	M[0][1] = 2 * i[0] * i[1] + 2 * r * i[2];
	M[0][2] = 2 * i[0] * i[2] - 2 * r * i[1];

	M[1][0] = 2 * i[0] * i[1] - 2 * r * i[2];
	M[1][1] = 1 - 2 * x2 - 2 * z2;
	M[1][2] = 2 * i[1] * i[2] + 2 * r * i[0];

	M[2][0] = 2 * i[0] * i[2] + 2 * r * i[1];
	M[2][1] = 2 * i[1] * i[2] - 2 * r * i[0];
	M[2][2] = 1 - 2 * x2 - 2 * y2;

	M[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4 Mat4::Perspective(const float aspect, 
	                   const float vertFOV, 
	                   const float nearPlane, 
	                   const float farPlane) 
{
	float c = 1.0f / tan(vertFOV / 2.0f);
	float r = nearPlane / c;
	float l = -r;
	float m00 = c / aspect;
	float m22 = -(farPlane + nearPlane) / (farPlane - nearPlane);
	float m32 = -(2 * nearPlane * farPlane) / (farPlane - nearPlane);

	Mat4 perspective = Mat4(m00, 0.0, 0.0, 0.0,
							0.0,   c, 0.0, 0.0,
						    0.0, 0.0, m22, -1.0,
							0.0, 0.0, m32, 0.0);
	return perspective;
}

Mat4 Mat4::Orthographic(const float aspect, 
	                    const float vertFOV, 
	                    const float nearPlane, 
	                    const float farPlane) 
{
	float c = 1.0 / tanf(vertFOV / 2.0);
	float r = nearPlane / c;
	float l = -r;
	float t = aspect * nearPlane / c;
	float b = -t;

	float m00 = 2.0f / (r - l);
	float m11 = (2.0f * nearPlane) / (t - b);
	float m22 =  -2.0f / (farPlane - nearPlane);
	float m30 = -(r + l) / (r - l);
	float m31 = -(t + b) / (t - b);
	float m32 = -(farPlane + nearPlane) / (farPlane - nearPlane);

	Mat4 orthographic = Mat4(m00, 0.0, 0.0, 0.0,
		                     0.0, m11, 0.0, 0.0,
		                     0.0, 0.0, m22, 0.0,
		                     m30, m31, m32, 1.0);
	return orthographic;
}

Mat4 Mat4::LookAt(Vec3 eye, Vec3 at, Vec3 up) {
	Vec3 zaxis = Vec3::Unit(at - eye);
	Vec3 xaxis = Vec3::Unit(zaxis.Cross(up));
	Vec3 yaxis = xaxis.Cross(zaxis);
	zaxis *= -1;

	/*
	Mat4 viewMat = Mat4(Mat3(xaxis, yaxis, zaxis),
		                Vec3(-xaxis.Dot(eye), -yaxis.Dot(eye), -zaxis.Dot(eye)));
	*/

	Mat4 viewMat(xaxis[0], yaxis[0], zaxis[0], 0.0f,
				 xaxis[1], yaxis[1], zaxis[1], 0.0f,
				 xaxis[2], yaxis[2], zaxis[2], 0.0f,
			    -xaxis.Dot(eye), -yaxis.Dot(eye), -zaxis.Dot(eye), 1.0);
	return viewMat;
}

// Uses Laplace Expansion Theorem: 
// https://www.geometrictools.com/Documentation/LaplaceExpansionTheorem.pdf
float Mat4::Determinant() {
	float c5 = (M[2][2] * M[3][3]) - (M[2][3] * M[3][2]);
	float c4 = (M[2][1] * M[3][3]) - (M[2][3] * M[3][1]);
	float c3 = (M[2][1] * M[3][2]) - (M[2][2] * M[3][1]);
	float c2 = (M[2][0] * M[3][3]) - (M[2][3] * M[3][0]);
	float c1 = (M[2][0] * M[3][2]) - (M[2][2] * M[3][0]);
	float c0 = (M[2][0] * M[3][1]) - (M[2][1] * M[3][0]);

	float s0 = (M[0][0] * M[1][1]) - (M[0][1] * M[1][0]);
	float s1 = (M[0][0] * M[1][2]) - (M[0][2] * M[1][0]);
	float s2 = (M[0][0] * M[1][3]) - (M[0][3] * M[1][0]);
	float s3 = (M[0][1] * M[1][2]) - (M[0][2] * M[1][1]);
	float s4 = (M[0][1] * M[1][3]) - (M[0][3] * M[1][1]);
	float s5 = (M[0][2] * M[1][3]) - (M[0][3] * M[1][2]);

	float determinant = s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0;

	return determinant;
}

// Uses Laplace Expansion Theorem: 
// https://www.geometrictools.com/Documentation/LaplaceExpansionTheorem.pdf
void Mat4::Invert() {

	float c5 = (M[2][2] * M[3][3]) - (M[2][3] * M[3][2]);
	float c4 = (M[2][1] * M[3][3]) - (M[2][3] * M[3][1]);
	float c3 = (M[2][1] * M[3][2]) - (M[2][2] * M[3][1]);
	float c2 = (M[2][0] * M[3][3]) - (M[2][3] * M[3][0]);
	float c1 = (M[2][0] * M[3][2]) - (M[2][2] * M[3][0]);
	float c0 = (M[2][0] * M[3][1]) - (M[2][1] * M[3][0]);

	float s0 = (M[0][0] * M[1][1]) - (M[0][1] * M[1][0]);
	float s1 = (M[0][0] * M[1][2]) - (M[0][2] * M[1][0]);
	float s2 = (M[0][0] * M[1][3]) - (M[0][3] * M[1][0]);
	float s3 = (M[0][1] * M[1][2]) - (M[0][2] * M[1][1]);
	float s4 = (M[0][1] * M[1][3]) - (M[0][3] * M[1][1]);
	float s5 = (M[0][2] * M[1][3]) - (M[0][3] * M[1][2]);

	float determinant = s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0;

	if (determinant == 0) {
		Logger::LogPrint("Mat4::Invert Invalid Invert -> Determinant is 0");
		SetErrorMat();
	}
	else {
		Mat4 adj;
		adj[0][0] = (M[1][1] * c5) - (M[1][2] * c4) + (M[1][3] * c3);
		adj[0][1] = (M[0][1] * c5) + (M[0][2] * c4) - (M[0][3] * c3);
		adj[0][2] = (M[3][1] * s5) - (M[3][2] * s4) + (M[3][3] * s3);
		adj[0][3] = -(M[2][1] * s5) + (M[2][2] * s4) - (M[2][3] * s3);

		adj[1][0] = -(M[1][0] * c5) + (M[1][2] * c2) - (M[1][3] * c1);
		adj[1][1] = (M[0][0] * c5) - (M[0][2] * c2) + (M[0][3] * c1);
		adj[1][2] = -(M[3][0] * s5) + (M[3][2] * s2) - (M[3][3] * s1);
		adj[1][3] = (M[2][0] * s5) - (M[2][2] * s2) + (M[2][3] * s1);

		adj[2][0] = (M[1][0] * c4) - (M[1][1] * c2) + (M[1][3] * c0);
		adj[2][1] = -(M[0][0] * c4) + (M[0][1] * c2) - (M[0][3] * c0);
		adj[2][2] = (M[3][0] * s4) - (M[3][1] * s2) + (M[3][3] * s0);
		adj[2][3] = -(M[2][0] * s4) + (M[2][1] * s2) - (M[2][3] * s0);

		adj[3][0] = -(M[1][0] * c3) + (M[1][1] * c1) - (M[1][2] * c0);
		adj[3][1] = (M[0][0] * c3) - (M[0][1] * c1) + (M[0][2] * c0);
		adj[3][2] = -(M[3][0] * s3) + (M[3][1] * s1) - (M[3][2] * s0);
		adj[3][3] = (M[2][0] * s3) - (M[2][1] * s1) + (M[2][2] * s0);

		*this = adj / determinant;
	}
}

Mat4& Mat4::operator=(const Mat4& other) {
	M[0] = other.M[0];
	M[1] = other.M[1];
	M[2] = other.M[2];
	M[3] = other.M[3];

	return *this;
}

Mat4 Mat4::operator+(const Mat4& other) const {
	Mat4 temp;
	temp.M[0] = M[0] + other.M[0];
	temp.M[1] = M[1] + other.M[1];
	temp.M[2] = M[2] + other.M[2];
	temp.M[3] = M[3] + other.M[3];

	return temp;
}

Mat4& Mat4::operator+=(const Mat4& other) {
	M[0] += other.M[0];
	M[1] += other.M[1];
	M[2] += other.M[2];
	M[3] += other.M[3];

	return *this;
}

void Mat4::SetErrorMat() {
	M[0][0] = INFINITY; 
	M[0][1] = -INFINITY;
	M[0][2] = INFINITY;
	M[0][3] = -INFINITY;

	M[1][0] = -INFINITY; 
	M[1][1] = INFINITY;
	M[1][2] = -INFINITY;
	M[1][3] = INFINITY;

	M[2][0] = INFINITY; 
	M[2][1] = -INFINITY;
	M[2][2] = INFINITY;
	M[2][3] = -INFINITY;

	M[3][0] = -INFINITY; 
	M[3][1] = INFINITY;
	M[3][2] = -INFINITY;
	M[3][3] = INFINITY;
}

Mat4 Mat4::operator*(const Mat4& other) const {
	Mat4 temp;
	temp[0][0] = M[0][0] * other[0][0] + M[0][1] * other[1][0] + M[0][2] * other[2][0] + M[0][3] * other[3][0];
	temp[0][1] = M[0][0] * other[0][1] + M[0][1] * other[1][1] + M[0][2] * other[2][1] + M[0][3] * other[3][1];
	temp[0][2] = M[0][0] * other[0][2] + M[0][1] * other[1][2] + M[0][2] * other[2][2] + M[0][3] * other[3][2];
	temp[0][3] = M[0][0] * other[0][3] + M[0][1] * other[1][3] + M[0][2] * other[2][3] + M[0][3] * other[3][3];

	temp[1][0] = M[1][0] * other[0][0] + M[1][1] * other[1][0] + M[1][2] * other[2][0] + M[1][3] * other[3][0];
	temp[1][1] = M[1][0] * other[0][1] + M[1][1] * other[1][1] + M[1][2] * other[2][1] + M[1][3] * other[3][1];
	temp[1][2] = M[1][0] * other[0][2] + M[1][1] * other[1][2] + M[1][2] * other[2][2] + M[1][3] * other[3][2];
	temp[1][3] = M[1][0] * other[0][3] + M[1][1] * other[1][3] + M[1][2] * other[2][3] + M[1][3] * other[3][3];

	temp[2][0] = M[2][0] * other[0][0] + M[2][1] * other[1][0] + M[2][2] * other[2][0] + M[2][3] * other[3][0];
	temp[2][1] = M[2][0] * other[0][1] + M[2][1] * other[1][1] + M[2][2] * other[2][1] + M[2][3] * other[3][1];
	temp[2][2] = M[2][0] * other[0][2] + M[2][1] * other[1][2] + M[2][2] * other[2][2] + M[2][3] * other[3][2];
	temp[2][3] = M[2][0] * other[0][3] + M[2][1] * other[1][3] + M[2][2] * other[2][3] + M[2][3] * other[3][3];

	temp[3][0] = M[3][0] * other[0][0] + M[3][1] * other[1][0] + M[3][2] * other[2][0] + M[3][3] * other[3][0];
	temp[3][1] = M[3][0] * other[0][1] + M[3][1] * other[1][1] + M[3][2] * other[2][1] + M[3][3] * other[3][1];
	temp[3][2] = M[3][0] * other[0][2] + M[3][1] * other[1][2] + M[3][2] * other[2][2] + M[3][3] * other[3][2];
	temp[3][3] = M[3][0] * other[0][3] + M[3][1] * other[1][3] + M[3][2] * other[2][3] + M[3][3] * other[3][3];
	return temp;
}

// TODO: Fix
Mat4& Mat4::operator*=(const Mat4& other) {
	Mat4 temp;
	temp[0][0] = M[0][0] * other[0][0] + M[0][1] * other[1][0] + M[0][2] * other[2][0] + M[0][3] * other[3][0];
	temp[0][1] = M[0][0] * other[0][1] + M[0][1] * other[1][1] + M[0][2] * other[2][1] + M[0][3] * other[3][1];
	temp[0][2] = M[0][0] * other[0][2] + M[0][1] * other[1][2] + M[0][2] * other[2][2] + M[0][3] * other[3][2];
	temp[0][3] = M[0][0] * other[0][3] + M[0][1] * other[1][3] + M[0][2] * other[2][3] + M[0][3] * other[3][3];

	temp[1][0] = M[1][0] * other[0][0] + M[1][1] * other[1][0] + M[1][2] * other[2][0] + M[1][3] * other[3][0];
	temp[1][1] = M[1][0] * other[0][1] + M[1][1] * other[1][1] + M[1][2] * other[2][1] + M[1][3] * other[3][1];
	temp[1][2] = M[1][0] * other[0][2] + M[1][1] * other[1][2] + M[1][2] * other[2][2] + M[1][3] * other[3][2];
	temp[1][3] = M[1][0] * other[0][3] + M[1][1] * other[1][3] + M[1][2] * other[2][3] + M[1][3] * other[3][3];

	temp[2][0] = M[2][0] * other[0][0] + M[2][1] * other[1][0] + M[2][2] * other[2][0] + M[2][3] * other[3][0];
	temp[2][1] = M[2][0] * other[0][1] + M[2][1] * other[1][1] + M[2][2] * other[2][1] + M[2][3] * other[3][1];
	temp[2][2] = M[2][0] * other[0][2] + M[2][1] * other[1][2] + M[2][2] * other[2][2] + M[2][3] * other[3][2];
	temp[2][3] = M[2][0] * other[0][3] + M[2][1] * other[1][3] + M[2][2] * other[2][3] + M[2][3] * other[3][3];

	temp[3][0] = M[3][0] * other[0][0] + M[3][1] * other[1][0] + M[3][2] * other[2][0] + M[3][3] * other[3][0];
	temp[3][1] = M[3][0] * other[0][1] + M[3][1] * other[1][1] + M[3][2] * other[2][1] + M[3][3] * other[3][1];
	temp[3][2] = M[3][0] * other[0][2] + M[3][1] * other[1][2] + M[3][2] * other[2][2] + M[3][3] * other[3][2];
	temp[3][3] = M[3][0] * other[0][3] + M[3][1] * other[1][3] + M[3][2] * other[2][3] + M[3][3] * other[3][3];

	*this = temp;
	return *this;
}

Mat4 Mat4::operator*(const float& scale) const {
	Mat4 temp = *this;
	temp[0] *= scale;
	temp[1] *= scale;
	temp[2] *= scale;
	temp[3] *= scale;
	return temp;
}

Mat4& Mat4::operator*=(const float& scale) {
	M[0] *= scale;
	M[1] *= scale;
	M[2] *= scale;
	M[3] *= scale;
	return *this;
}

Mat4 Mat4::operator/(const float& scale) const {
	Mat4 temp = *this;
	temp[0] /= scale;
	temp[1] /= scale;
	temp[2] /= scale;
	temp[3] /= scale;
	return temp;
}

Mat4& Mat4::operator/=(const float& scale) {
	M[0] /= scale;
	M[1] /= scale;
	M[2] /= scale;
	M[3] /= scale;
	return *this;
}
