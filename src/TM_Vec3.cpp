#include "TM_Vec3.h"
#include "TM_Mat4.h"
#include "TM_Vec2.h"
#include "TM_Vec4.h"
#include <math.h>

Vec3::Vec3() : v{0.0f, 0.0f, 0.0f} {}

Vec3::Vec3(const float x, const float y, const float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

Vec3::Vec3(const Vec3 &other) { vv = other.vv; }

Vec3::Vec3(const Vec2 &other) {
  x = other.x;
  y = other.y;
}

Vec3::Vec3(const Vec4 &vec4) { memcpy(&v[0], &vec4.v[0], 3 * sizeof(float)); }

Vec3::Vec3(const Mat4 &mat4) {
  memcpy(&v[0], &mat4.m[3][0], 3 * sizeof(float));
}

void Vec3::Normalize() {
  float length = Length();
  __m128 lv = _mm_set_ps1(&length);
  vv = _mm_div_ps(vv, lv);
}

Vec3 Vec3::Unit(const Vec3 &other) {
  Vec3 temp;
  float length = other.Length();
  __m128 lv = _mm_set_ps1(&length);
  temp.vv = _mm_div_ps(vv, lv);
  return temp;
}

Vec3 Vec3::Cross(const Vec3 &other) const {
  Vec3 temp;
  __m128 min = _mm_mul_ps(_mm_shuffle_ps(vv, {1, 2, 0, 3})
                              _mm_shuffle_ps(other.vv, {2, 0, 1, 3}));
  __m128 sub = _mm_mul_ps(_mm_shuffle_ps(vv, {2, 0, 1, 3}),
                          _mm_shuffle_ps(other.vv, {1, 2, 0, 3}));
  temp.vv = _mm_sub_ps(min, sub);
  return temp;
}
