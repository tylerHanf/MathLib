/**
 * @file Mat4.h
 * @author Tyler Hanf
 * @brief Provides a SIMD Mat4 implementation
 * @version 0.1
 * @date 2023-08-12
 */
#pragma once

#include "TM_Intrinsics.h"
#include "TM_Quaternion.h"
#include "TM_Types.h"
#include "TM_Vec3.h"
#include "TM_Vec4.h"
#include "TM_Mat3.h"

// Defs
class Mat4 {
public:
  Mat4(void);
  Mat4(const float x0, const float y0, const float z0, const float px,
       const float x1, const float y1, const float z1, const float py,
       const float x2, const float y2, const float z2, const float pz,
       const float w0, const float w1, const float w2, const float w3);
  Mat4(const Mat4 &other);
  Mat4(const Mat3 &dcm, const Vec3 &pos);
  Mat4(const Mat3 &dcm);
  Mat4(const Vec3 &pos);
  Mat4(const Quaternion &q);

  std::string to_string(void);

  Vec4 Row(const uint8_t index);
  Vec4 Column(const uint8_t index);

  Mat4 GetInverse(void) const;
  Mat4 GetTranspose(void) const;

  float At(const uint8_t row, const uint8_t col) const;

  void Invert(void);
  void Transpose(void);
  void Translate(const Vec3 &pos);
  void Scale(const Vec3 &pos);
  float Determinant(void);

  float *Ptr(void);
  const float *ConstPtr(void) const;

  static Mat4 TranslateMatrix(const Vec3 &pos);
  static Mat4 ScaleMatrix(const Vec3 &scale);
  static Mat4 Perspective(const float aspect, const float vertFOV,
                          const float nearPlane, const float farPlane);

  static Mat4 Orthographic(const float aspect, const float vertFOV,
                           const float nearPlane, const float farPlane);

  static Mat4 LookAt(Vec3 eye, Vec3 at, Vec3 up);

  Mat4 &operator=(const Mat4 &other);

  Mat4 operator+(const Mat4 &other) const;
  Mat4 &operator+=(const Mat4 &other);

  Mat4 operator*(const Mat4 &other) const;
  Mat4 &operator*=(const Mat4 &other);
  Mat4 operator*(const float &scale) const;
  Mat4 &operator*=(const float &scale);
  Mat4 operator/(const float &scale) const;
  Mat4 &operator/=(const float &scale);

  Vec4 operator[](const uint8_t index);

  _M4;

private:
  void SetErrorMat(void);
};

inline float *Mat4::Ptr(void) { return &(m[0][0]); }

inline const float *Mat4::ConstPtr(void) const { return &(m[0][0]); }

// inline implementation
inline std::string Mat4::to_string(void) {
  std::string str(
      "(" + std::to_string(m[0][0]) + ", " + std::to_string(m[0][1]) + ", " +
          std::to_string(m[0][2]) + ", " + std::to_string(m[0][3]) + ",\n" +
      std::to_string(m[1][0]) + ", " + std::to_string(m[1][1]) + ", " +
      std::to_string(m[1][2]) + ", " + std::to_string(m[1][3]) + ",\n" +
      std::to_string(m[2][0]) + ", " + std::to_string(m[2][1]) + ", " +
      std::to_string(m[2][2]) + ", " + std::to_string(m[2][3]) + ",\n" +
      std::to_string(m[3][0]) + ", " + std::to_string(m[3][1]) + ", " +
      std::to_string(m[3][2]) + ", " + std::to_string(m[3][3]) + ")");

  return str;
}

inline float Mat4::At(const uint8_t row, const uint8_t col) const {
  return m[row][col];
}

inline Vec4 Mat4::Row(const uint8_t index) {
  return {m[index][0], m[index][1], m[index][2], m[index][3]};
}

inline Vec4 Mat4::Column(const uint8_t index) {
  return {m[0][index], m[1][index], m[2][index], m[3][index]};
}

inline void Mat4::Transpose() { _MM_TRANSPOSE4_PS(mv[0], mv[1], mv[2], mv[3]); }

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

inline void Mat4::Translate(const Vec3 &pos) {
  mv[3] = _mm_add_ps(mv[3], pos.vv);
}

inline void Mat4::Scale(const Vec3 &scale) {
  __m128 scaleX = _mm_set_ps1(scale.v[0]);
  __m128 scaleY = _mm_set_ps1(scale.v[1]);
  __m128 scaleZ = _mm_set_ps1(scale.v[2]);

  mv[0] = _mm_mul_ps(mv[0], scaleX);
  mv[1] = _mm_mul_ps(mv[1], scaleY);
  mv[2] = _mm_mul_ps(mv[2], scaleZ);
}

inline Mat4 Mat4::TranslateMatrix(const Vec3 &val) { return Mat4(val); }

inline Mat4 Mat4::Adjoint(void) {
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

          return adj;
}

inline Mat4 Mat4::ScaleMatrix(const Vec3 &scale) {
  return {scale.x, 0, 0, 0, 0, scale.y, 0, 0, 0, 0, scale.z, 0, 0, 0, 0, 1.f};
}

inline Vec4 Mat4::operator[](const uint8_t index) {
  return {m[index][0], m[index][1], m[index][2], m[index][3]};
}
