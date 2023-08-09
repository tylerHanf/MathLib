/*********************************************
	Implements basic 2-vector Math
**********************************************/
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include <math.h>

Vec2::Vec2() {
	x = 0.0f;
	y = 0.0f;
}

Vec2::Vec2(const float x, const float y) {
	// this->x = x;
	// this->y = y;
	v[0] = x;
	v[1] = y;
}

Vec2::Vec2(const Vec2& other) {
	x = other.x;
	y = other.y;
}

Vec2::Vec2(const Vec3& vec3) {
	x = vec3[0];
	y = vec3[1];
}

Vec2::Vec2(const Vec4& vec4) {
	x = vec4[0];
	y = vec4[1];
}

void Vec2::Normalize() {
	float len = Length();
	x /= len;
	y /= len;
}

Vec2 Vec2::Unit(const Vec2& vector) {
	Vec2 temp;
	float length = vector.Length();
	temp.x = vector.x / length;
	temp.y = vector.y / length;
	return temp;
}
