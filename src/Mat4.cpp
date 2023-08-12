/**
 * @file Mat4.cpp
 * @author Tyler Hanf
 * @brief Mat4 impl
 * @version 0.1
 * @date 2023-08-12
 */
#include "Mat4.h"
#include "Logger.h"
#include "Mat3.h"
#include <math.h>
#include <stdio.h>

Mat4::Mat4()
    : m{{1.f, 0.f, 0.f, 0.f},
        {0.f, 1.f, 0.f, 0.f},
        {0.f, 0.f, 1.f, 0.f},
        {0.f, 0.f, 0.f, 1.f}} {}

Mat4::Mat4(const float x0, const float x1, const float x2, const float w0,
           const float y0, const float y1, const float y2, const float w1,
           const float z0, const float z1, const float z2, const float w2,
           const float px, const float py, const float pz, const float w3) {
  m[0][0] = x0;
  m[0][1] = x1;
  m[0][2] = x2;
  m[0][3] = w0;

  m[1][0] = y0;
  m[1][1] = y1;
  m[1][2] = y2;
  m[1][3] = w1;

  m[2][0] = z0;
  m[2][1] = z1;
  m[2][2] = z2;
  m[2][3] = w2;

  m[3][0] = px;
  m[3][1] = py;
  m[3][2] = pz;
  m[3][3] = w3;
}

Mat4::Mat4(const Mat4 &other) {
  memcpy(&m[0][0], &other.m[0][0], 16 * sizeof(float));
}

Mat4::Mat4(const Mat3 &dcm, const Vec3 &pos) {
  memcpy(&m[0][0], &dcm.m[0][0], 3 * sizeof(float));
  memcpy(&m[1][0], &dcm.m[1][0], 3 * sizeof(float));
  memcpy(&m[2][0], &dcm.m[2][0], 3 * sizeof(float));
  memcpy(&m[3][0], &pos.v[0], 3 * sizeof(float));
}

Mat4::Mat4(const Mat3 &dcm) {
  memcpy(&m[0][0], &dcm.m[0][0], 3 * sizeof(float));
  memcpy(&m[1][0], &dcm.m[1][0], 3 * sizeof(float));
  memcpy(&m[2][0], &dcm.m[2][0], 3 * sizeof(float));
}

Mat4::Mat4(const Vec3 &pos) { memcpy(&m[3][0], &pos.v[0], 3 * sizeof(float)); }

Mat4::Mat4(const Quaternion &q) {
  Vec4 i = q.Imaginary();
  __m128 iv = _mm_load_ps(&i[0]);
  float r(q.r);

  const float two_f(2.f);
  __m128 two_v = _mm_load1_ps(&two_f);
  __m128 i_sqr = _mm_mul_ps(iv, iv);
  __m128 i_dub = _mm_mul_ps(iv, two_v);

  m[0][0] = 1 - i_dub[1] - i_dub[2];
  M[0][1] = 2 * i.x * i.y + 2 * r * i.z;
  M[0][2] = 2 * i.x * i.z - 2 * r * i.y;

  M[1].x = 2 * i.x * i.y - 2 * r * i.z;
  M[1].y = 1 - 2 * x2 - 2 * z2;
  M[1].z = 2 * i.y * i.z + 2 * r * i.x;

  M[2].x = 2 * i.x * i.z + 2 * r * i.y;
  M[2].y = 2 * i.y * i.z - 2 * r * i.x;
  M[2].z = 1 - 2 * x2 - 2 * y2;

  M[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4 Mat4::Perspective(const float aspect, const float vertFOV,
                       const float nearPlane, const float farPlane) {
  float c = 1.0f / tan(vertFOV / 2.0f);
  float r = nearPlane / c;
  float l = -r;
  float m00 = c / aspect;
  float m22 = -(farPlane + nearPlane) / (farPlane - nearPlane);
  float m32 = -(2 * nearPlane * farPlane) / (farPlane - nearPlane);

  Mat4 perspective = Mat4(m00, 0.0, 0.0, 0.0, 0.0, c, 0.0, 0.0, 0.0, 0.0, m22,
                          -1.0, 0.0, 0.0, m32, 0.0);
  return perspective;
}

Mat4 Mat4::Orthographic(const float aspect, const float vertFOV,
                        const float nearPlane, const float farPlane) {
  float c = 1.0 / tanf(vertFOV / 2.0);
  float r = nearPlane / c;
  float l = -r;
  float t = aspect * nearPlane / c;
  float b = -t;

  float m00 = 2.0f / (r - l);
  float m11 = (2.0f * nearPlane) / (t - b);
  float m22 = -2.0f / (farPlane - nearPlane);
  float m30 = -(r + l) / (r - l);
  float m31 = -(t + b) / (t - b);
  float m32 = -(farPlane + nearPlane) / (farPlane - nearPlane);

  Mat4 orthographic = Mat4(m00, 0.0, 0.0, 0.0, 0.0, m11, 0.0, 0.0, 0.0, 0.0,
                           m22, 0.0, m30, m31, m32, 1.0);
  return orthographic;
}

Mat4 Mat4::LookAt(Vec3 eye, Vec3 at, Vec3 up) {
  Vec3 zaxis = Vec3::Unit(at - eye);
  Vec3 xaxis = Vec3::Unit(zaxis.Cross(up));
  Vec3 yaxis = xaxis.Cross(zaxis);
  zaxis *= -1;

  Mat4 viewMat(xaxis.x, yaxis.x, zaxis.x, 0.0f, xaxis.y, yaxis.y, zaxis.y, 0.0f,
               xaxis.z, yaxis.z, zaxis.z, 0.0f, -xaxis.Dot(eye),
               -yaxis.Dot(eye), -zaxis.Dot(eye), 1.0);
  return viewMat;
}

// Uses Laplace Expansion Theorem:
// https://www.geometrictools.com/Documentation/LaplaceExpansionTheorem.pdf
float Mat4::Determinant() {

  // Speed up time by reducing look ups repeatedly
  float m00 = m[0].x;
  float m01 = m[0].y;
  float m02 = m[0].z;
  float m03 = m[0].w;
  float m10 = m[1].x;
  float m11 = m[1].y;
  float m12 = m[1].z;
  float m13 = m[1].w;
  float m20 = m[2].x;
  float m21 = M[2].y;
  float m22 = M[2].z;
  float m23 = M[2].w;
  float m30 = M[3].x;
  float m31 = M[3].y;
  float m32 = M[3].z;
  float m33 = M[3].w;

  float c5 = (m22 * m33) - (m23 * m32);
  float c4 = (m21 * m33) - (m23 * m31);
  float c3 = (m21 * m32) - (m22 * m31);
  float c2 = (m20 * m33) - (m23 * m30);
  float c1 = (m20 * m32) - (m22 * m30);
  float c0 = (m20 * m31) - (m21 * m30);

  float s0 = (m00 * m11) - (m01 * m10);
  float s1 = (m00 * m12) - (m02 * m10);
  float s2 = (m00 * m13) - (m03 * m10);
  float s3 = (m01 * m12) - (m02 * m11);
  float s4 = (m01 * m13) - (m03 * m11);
  float s5 = (m02 * m13) - (m03 * m12);

  float determinant = s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0;

  return determinant;
}

// Uses Laplace Expansion Theorem:
// https://www.geometrictools.com/Documentation/LaplaceExpansionTheorem.pdf
void Mat4::Invert() {
  /*
  float m00 = M[0].x;
  float m01 = M[0].y;
  float m02 = M[0].z;
  float m03 = M[0].w;
  float m10 = M[1].x;
  float m11 = M[1].y;
  float m12 = M[1].z;
  float m13 = M[1].w;
  float m20 = M[2].x;
  float m21 = M[2].y;
  float m22 = M[2].z;
  float m23 = M[2].w;
  float m30 = M[3].x;
  float m31 = M[3].y;
  float m32 = M[3].z;
  float m33 = M[3].w;

  float c5 = (m22 * m33) - (m23 * m32);
  float c4 = (m21 * m33) - (m23 * m31);
  float c3 = (m21 * m32) - (m22 * m31);
  float c2 = (m20 * m33) - (m23 * m30);
  float c1 = (m20 * m32) - (m22 * m30);
  float c0 = (m20 * m31) - (m21 * m30);

  float s0 = (m00 * m11) - (m01 * m10);
  float s1 = (m00 * m12) - (m02 * m10);
  float s2 = (m00 * m13) - (m03 * m10);
  float s3 = (m01 * m12) - (m02 * m11);
  float s4 = (m01 * m13) - (m03 * m11);
  float s5 = (m02 * m13) - (m03 * m12);

  float determinant = s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0;

  if (determinant == 0) {
          Logger::Log("Mat4::Invert Invalid Invert -> Determinant is 0");
          SetErrorMat();
  }
  else {
          Mat4 adj;
          adj[0].x = (m11 * c5) - (m12 * c4) + (m13 * c3);
          adj[0].y = (m01 * c5) + (m02 * c4) - (m03 * c3);
          adj[0].z = (m31 * s5) - (m32 * s4) + (m33 * s3);
          adj[0].w = -(m21 * s5) + (m22 * s4) - (m23 * s3);

          adj[1].x = -(m10 * c5) + (m12 * c2) - (m13 * c1);
          adj[1].y = (m00 * c5) - (m02 * c2) + (m03 * c1);
          adj[1].z = -(m30 * s5) + (m32 * s2) - (m33 * s1);
          adj[1].w = (m20 * s5) - (m22 * s2) + (m23 * s1);

          adj[2].x = (m10 * c4) - (m11 * c2) + (m13 * c0);
          adj[2].y = -(m00 * c4) + (m01 * c2) - (m03 * c0);
          adj[2].z = (m30 * s4) - (m31 * s2) + (m33 * s0);
          adj[2].w = -(m20 * s4) + (m21 * s2) - (m23 * s0);

          adj[3].x = -(m10 * c3) + (m11 * c1) - (m12 * c0);
          adj[3].y = (m00 * c3) - (m01 * c1) + (m02 * c0);
          adj[3].z = -(m30 * s3) + (m31 * s1) - (m32 * s0);
          adj[3].w = (m20 * s3) - (m21 * s1) + (m22 * s0);

          *this = adj / determinant;
  }
  */
}

Mat4 &Mat4::operator=(const Mat4 &other) {
  M[0] = other.M[0];
  M[1] = other.M[1];
  M[2] = other.M[2];
  M[3] = other.M[3];

  return *this;
}

Mat4 Mat4::operator+(const Mat4 &other) const {
  Mat4 temp;
  temp.M[0] = M[0] + other.M[0];
  temp.M[1] = M[1] + other.M[1];
  temp.M[2] = M[2] + other.M[2];
  temp.M[3] = M[3] + other.M[3];

  return temp;
}

Mat4 &Mat4::operator+=(const Mat4 &other) {
  M[0] += other.M[0];
  M[1] += other.M[1];
  M[2] += other.M[2];
  M[3] += other.M[3];

  return *this;
}

void Mat4::SetErrorMat() {
  M[0].x = INFINITY;
  M[0].y = -INFINITY;
  M[0].z = INFINITY;
  M[0].w = -INFINITY;

  M[1].x = -INFINITY;
  M[1].y = INFINITY;
  M[1].z = -INFINITY;
  M[1].w = INFINITY;

  M[2].x = INFINITY;
  M[2].y = -INFINITY;
  M[2].z = INFINITY;
  M[2].w = -INFINITY;

  M[3].x = -INFINITY;
  M[3].y = INFINITY;
  M[3].z = -INFINITY;
  M[3].w = INFINITY;
}

Mat4 Mat4::operator*(const Mat4 &other) const {

  Mat4 temp;
  /*
  float m00 = M[0].x;
  float m01 = M[0].y;
  float m02 = M[0].z;
  float m03 = M[0].w;
  float m10 = M[1].x;
  float m11 = M[1].y;
  float m12 = M[1].z;
  float m13 = M[1].w;
  float m20 = M[2].x;
  float m21 = M[2].y;
  float m22 = M[2].z;
  float m23 = M[2].w;
  float m30 = M[3].x;
  float m31 = M[3].y;
  float m32 = M[3].z;
  float m33 = M[3].w;

  float o00 = other[0].x;
  float o01 = other[0].y;
  float o02 = other[0].z;
  float o03 = other[0].w;
  float o10 = other[1].x;
  float o11 = other[1].y;
  float o12 = other[1].z;
  float o13 = other[1].w;
  float o20 = other[2].x;
  float o21 = other[2].y;
  float o22 = other[2].z;
  float o23 = other[2].w;
  float o30 = other[3].x;
  float o31 = other[3].y;
  float o32 = other[3].z;
  float o33 = other[3].w;

  temp[0].x = m00 * o00 + m01 * o10 + m02 * o20 + m03 * o30;
  temp[0].y = m00 * o01 + m01 * o11 + m02 * o21 + m03 * o31;
  temp[0].z = m00 * o02 + m01 * o12 + m02 * o22 + m03 * o32;
  temp[0].w = m00 * o03 + m01 * o13 + m02 * o23 + m03 * o33;

  temp[1].x = m10 * o00 + m11 * o10 + m12 * o20 + m13 * o30;
  temp[1].y = m10 * o01 + m11 * o11 + m12 * o21 + m13 * o31;
  temp[1].z = m10 * o02 + m11 * o12 + m12 * o22 + m13 * o32;
  temp[1].w = m10 * o03 + m11 * o13 + m12 * o23 + m13 * o33;

  temp[2].x = m20 * o00 + m21 * o10 + m22 * o20 + m23 * o30;
  temp[2].y = m20 * o01 + m21 * o11 + m22 * o21 + m23 * o31;
  temp[2].z = m20 * o02 + m21 * o12 + m22 * o22 + m23 * o32;
  temp[2].w = m20 * o03 + m21 * o13 + m22 * o23 + m23 * o33;

  temp[3].x = m30 * o00 + m31 * o10 + m32 * o20 + m33 * o30;
  temp[3].y = m30 * o01 + m31 * o11 + m32 * o21 + m33 * o31;
  temp[3].z = m30 * o02 + m31 * o12 + m32 * o22 + m33 * o32;
  temp[3].w = m30 * o03 + m31 * o13 + m32 * o23 + m33 * o33;
  */
  return temp;
}

// TODO: Fix
Mat4 &Mat4::operator*=(const Mat4 &other) {
  /*
  float m00 = M[0].x;
  float m01 = M[0].y;
  float m02 = M[0].z;
  float m03 = M[0].w;
  float m10 = M[1].x;
  float m11 = M[1].y;
  float m12 = M[1].z;
  float m13 = M[1].w;
  float m20 = M[2].x;
  float m21 = M[2].y;
  float m22 = M[2].z;
  float m23 = M[2].w;
  float m30 = M[3].x;
  float m31 = M[3].y;
  float m32 = M[3].z;
  float m33 = M[3].w;

  float o00 = other[0].x;
  float o01 = other[0].y;
  float o02 = other[0].z;
  float o03 = other[0].w;
  float o10 = other[1].x;
  float o11 = other[1].y;
  float o12 = other[1].z;
  float o13 = other[1].w;
  float o20 = other[2].x;
  float o21 = other[2].y;
  float o22 = other[2].z;
  float o23 = other[2].w;
  float o30 = other[3].x;
  float o31 = other[3].y;
  float o32 = other[3].z;
  float o33 = other[3].w;

  Mat4 temp;
  temp[0].x = m00 * o00 + m01 * o10 + m02 * o20 + m03 * o30;
  temp[0].y = m00 * o01 + m01 * o11 + m02 * o21 + m03 * o31;
  temp[0].z = m00 * o02 + m01 * o12 + m02 * o22 + m03 * o32;
  temp[0].w = m00 * o03 + m01 * o13 + m02 * o23 + m03 * o33;

  temp[1].x = m10 * o00 + m11 * o10 + m12 * o20 + m13 * o30;
  temp[1].y = m10 * o01 + m11 * o11 + m12 * o21 + m13 * o31;
  temp[1].z = m10 * o02 + m11 * o12 + m12 * o22 + m13 * o32;
  temp[1].w = m10 * o03 + m11 * o13 + m12 * o23 + m13 * o33;

  temp[2].x = m20 * o00 + m21 * o10 + m22 * o20 + m23 * o30;
  temp[2].y = m20 * o01 + m21 * o11 + m22 * o21 + m23 * o31;
  temp[2].z = m20 * o02 + m21 * o12 + m22 * o22 + m23 * o32;
  temp[2].w = m20 * o03 + m21 * o13 + m22 * o23 + m23 * o33;

  temp[3].x = m30 * o00 + m31 * o10 + m32 * o20 + m33 * o30;
  temp[3].y = m30 * o01 + m31 * o11 + m32 * o21 + m33 * o31;
  temp[3].z = m30 * o02 + m31 * o12 + m32 * o22 + m33 * o32;
  temp[3].w = m30 * o03 + m31 * o13 + m32 * o23 + m33 * o33;
  *this = temp;
  */
  return *this;
}

Mat4 Mat4::operator*(const float &scale) const {

  Mat4 temp = *this;
  /*
  temp[0] *= scale;
  temp[1] *= scale;
  temp[2] *= scale;
  temp[3] *= scale;
  */
  return temp;
}

Mat4 &Mat4::operator*=(const float &scale) {
  /*
  M[0] *= scale;
  M[1] *= scale;
  M[2] *= scale;
  M[3] *= scale;
  */
  return *this;
}

Mat4 Mat4::operator/(const float &scale) const {
  Mat4 temp = *this;
  temp[0] /= scale;
  temp[1] /= scale;
  temp[2] /= scale;
  temp[3] /= scale;
  return temp;
}

Mat4 &Mat4::operator/=(const float &scale) {
  M[0] /= scale;
  M[1] /= scale;
  M[2] /= scale;
  M[3] /= scale;
  return *this;
}
