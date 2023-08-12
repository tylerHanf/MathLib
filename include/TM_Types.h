/**
 * @file TM_Types.h
 * @author Tyler Hanf
 * @brief Defines useful types for working with SIMD data
 * @version 0.1
 * @date 2023-08-12
 */
#pragma once
#include "TM_Intrinsics.h"

// SIMD bodies
#define _M4_IMPL                                                               \
  float m[4][4];                                                               \
  __m128 mv[4];

#define _M3_IMPL                                                               \
  float m[3][3];                                                               \
  __m128 mv[3];

#define _Q_IMPL                                                                \
  float q[4];                                                                  \
  __m128 qv;                                                                   \
  float r, ix, iy, iz;

#define _V4_IMPL                                                               \
  float v[4];                                                                  \
  __m128 vv;                                                                   \
  float x, y, z, w;

#define _V3_IMPL                                                               \
  float v[3];                                                                  \
  __m128 vv;                                                                   \
  float x, y, z;

#define _V2_IMPL                                                               \
  float v[2];                                                                  \
  __m64 vv;                                                                    \
  float x, y;

// Anonymous Impls
#define _M4                                                                    \
  union {                                                                      \
    _M4_IMPL                                                                   \
  };

#define _M3                                                                    \
  union {                                                                      \
    _M3_IMPL                                                                   \
  };

#define _Q                                                                     \
  union {                                                                      \
    _Q_IMPL                                                                    \
  };

#define _V4                                                                    \
  union {                                                                      \
    _V4_IMPL                                                                   \
  };

#define _V3                                                                    \
  union {                                                                      \
    _V3_IMPL                                                                   \
  };

#define _V2                                                                    \
  union {                                                                      \
    _V2_IMPL                                                                   \
  };

/**
 * @brief Mat4 simd
 */
union M4 {
  _M4_IMPL
};

/**
 * @brief Mat3 simd
 */
union M3 {
  _M3_IMPL
};

/**
 * @brief Quaternion simd
 */
union Q {
  _Q_IMPL
};

/**
 * @brief Vec4 simd
 */
union V4 {
  _V4_IMPL
};

/**
 * @brief Vec3 simd
 */
union V3 {
  _V3_IMPL
};

/**
 * @brief Vec2 simd
 */
union V2 {
  _V2_IMPL
};