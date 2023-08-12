/**
 * @file Intrinsics.h
 * @author Tyler Hanf
 * @brief Defines which SIMD intrinsics header to use based on the compiler
 * @version 0.1
 * @date 2023-08-12
 */
#pragma once

#ifdef _MSC_VER
#include <intrin.h>
#elif __GNUC__ && (__x86_64__ || __i386__)
#include <x86intrin.h>
#endif
