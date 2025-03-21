#ifndef MATH_QUAT_H
#define MATH_QUAT_H

#include <cstdint>

#include "vec.h"
#include "vec_operations.h"

namespace math
{
	class quat
	{
	public:
		float s_ = 0.0f;
		vec3 v_;
		quat() : v_(0.0f) {};
		quat(float s, const vec3& v) : s_(s), v_(v){}
		quat(const quat& q);

		quat& operator=(const quat& other);
		quat operator+(const quat& other);
		quat operator-(const quat& other);
		void operator+=(const quat& other);
		void operator-=(const quat& other);
		bool operator==(const quat& other);
		quat operator*(const quat& other);
		quat operator*(const float other);
		void operator*=(const quat& other);
		void operator*=(const float other);
	};
}

#endif // !MATH_QUAT_H