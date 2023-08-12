/**
 * @file TM_Vec3.h
 * @author Tyler Hanf
 * @brief Provides a Vec3 SIMD implementation
 * @version 0.1
 * @date 2023-08-12
 */
#pragma once
#include "Logger.h"
#include "TM_Types.h"
#include <math.h>
#include <string>

class Vec2;
class Vec4;
class Mat4;

class Vec3 {
public:
  Vec3(void);
  Vec3(const float x, const float y, const float z);
  Vec3(const Vec3 &other);
  Vec3(const Vec2 &vec2);
  Vec3(const Vec4 &vec4);
  Vec3(const Mat4 &mat4);

  std::string to_string(bool brackets = true);

  bool IsLeftOf(const Vec3 &other) const;

  float Length(void) const;
  void Normalize(void);
  float Dot(const Vec3 &other) const;
  Vec3 Cross(const Vec3 &other) const;

  static Vec3 Unit(const Vec3 &other);

  Vec3 &operator=(const Vec3 &other);

  Vec3 operator+(const Vec3 &other) const;
  Vec3 &operator+=(const Vec3 &other);

  Vec3 operator-(const Vec3 &other) const;
  Vec3 &operator-=(const Vec3 &other);

  Vec3 operator*(const float scale) const;
  Vec3 &operator*=(const float scale);

  Vec3 operator/(const float scale) const;
  Vec3 &operator/=(const float scale);

  float &operator[](const int index);
  const float &operator[](const int index) const;

  bool operator==(const Vec3 &other) const;

  _V3;
};

inline std::string Vec3::to_string(bool brackets) {
  if (brackets)
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " +
           std::to_string(z) + ")";
  return std::to_string(x) + ", " + std::to_string(y) + ", " +
         std::to_string(z);
}

inline float Vec3::Length() const {
  V3 sq;
  sq.vv = _mm_mul_ps(vv, vv);
  return sqrtf(sq.x + sq.y + sq.y);
}

inline float Vec3::Dot(const Vec3 &other) const {
  V3 mult;
  mult.vv = _mm_mul_ps(vv, other.vv);
  return (mult.x + mult.y + mult.z);
}

inline bool Vec3::IsLeftOf(const Vec3 &other) const {
  return Cross(other).y > 0;
}

inline Vec3 &Vec3::operator=(const Vec3 &other) {
  memcpy(&v[0], &other.v[0], 3 * sizeof(float));
  return *this;
}

inline Vec3 Vec3::operator+(const Vec3 &other) const {
  Vec3 temp;
  temp.vv = _mm_add_ps(vv, other.vv);
  return temp;
}

inline Vec3 &Vec3::operator+=(const Vec3 &other) {
  vv = _mm_add_ps(vv, other.vv);
  return *this;
}

inline Vec3 Vec3::operator-(const Vec3 &other) const {
  Vec3 temp;
  temp.vv = _mm_sub_ps(vv, other.vv);
  return temp;
}

inline Vec3 &Vec3::operator-=(const Vec3 &other) {
  vv = _mm_sub_ps(vv, other.vv);
  return *this;
}

inline Vec3 Vec3::operator*(const float scale) const {
  Vec3 temp;
  __m128 scalev = _mm_set_ps1(scale);
  temp.vv = _mm_mul_ps(vv, scalev);
  return temp;
}

inline Vec3 &Vec3::operator*=(const float scale) {
  __m128 scalev = _mm_set_ps1(scale);
  vv = _mm_mul_ps(vv, scalev);
  return *this;
}

inline Vec3 Vec3::operator/(const float scale) const {
  Vec3 temp;
  if (scale != 0.0f) {
    __m128 scalev = _mm_set_ps1(scale);
    temp.vv = _mm_div_ps(vv, scalev);
  } else {
    Logger::Log("DIVISION BY ZERO");
  }
  return temp;
}

inline Vec3 &Vec3::operator/=(const float scale) {
  if (scale != 0.0f) {
    __m128 scalev = _mm_set_ps1(scale);
    vv = _mm_div_ps(vv, scalev);
  } else {
    Logger::Log("DIVISION BY ZERO");
  }
  return *this;
}

inline float &Vec3::operator[](const int index) { return v[index]; }

inline const float &Vec3::operator[](const int index) const { return v[index]; }

inline bool Vec3::operator==(const Vec3 &other) const {
  V3 equal;
  equal.vv = _mm_cmpeq_ps(vv, other.vv);
  return (equal.x || equal.y || equal.z);
}
