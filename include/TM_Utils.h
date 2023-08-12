/**
 * @file TM_Utils.h
 * @author Tyler Hanf
 * @brief Defines helper functions and constants
 * @version 0.1
 * @date 2023-08-12
 */
#pragma once

#define PI 3.14159265359
#define TO_RAD PI / 180
#define TO_DEG 180 / PI

inline static float ToRadians(float degrees) { return degrees * TO_RAD; }

inline static float ToDegrees(float radians) { return radians * TO_DEG; }