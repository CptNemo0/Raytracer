#ifndef MATH_VEC_OPERATIONS_H
#define MATH_VEC_OPERATIONS_H

#include <cmath>
#include "angles.h"
#include "vec.h"

namespace math
{
	template <std::uint32_t l, typename T>
	requires std::is_arithmetic_v<T>
	T dot(const vec<l, T>& a, const vec<l, T>& b)
	{
		T result = static_cast<T>(0);
		for (std::uint32_t i = 0; i < l; ++i)
		{
			result += a[i] * b[i];
		}
		return result;
	}

    template <typename T>
    requires std::is_arithmetic_v<T>
    vec<3, T> cross(const vec<3, T>& a, const vec<3, T>& b)
    {
        vec<3, T> result;
        result[0] = a[1] * b[2] - a[2] * b[1];
        result[1] = a[2] * b[0] - a[0] * b[2];
        result[2] = a[0] * b[1] - a[1] * b[0];
        return result;
    }

	template <std::uint32_t l, typename T>
	requires std::is_arithmetic_v<T>
	T length(const vec<l, T>& a)
	{
		T result = static_cast<T>(0);

		for (std::uint32_t i = 0; i < l; ++i)
		{
			result += a[i] * a[i];
		}

		return static_cast<T>(std::sqrtf(static_cast<float>(result)));
	}

	template <std::uint32_t l, typename T>
	requires std::is_arithmetic_v<T>
	T distance(const vec<l, T>& a, const vec<l, T>& b)
	{
		auto c = b - a;
		return length(c);
	}

	template <std::uint32_t l, typename T>
	requires std::is_arithmetic_v<T>
	void normalize(vec<l, T>& v)
	{
		auto len = length(v);
		v /= len;
	}

	template <std::uint32_t l, typename T>
	requires std::is_arithmetic_v<T>
	float angle_rad(const vec<l, T>& a, const vec<l, T>& b)
	{
		T dot_product = dot(a, b);
		T len_a = length(a);
		T len_b = length(b);
		auto cos_theta = static_cast<float>(dot_product) / static_cast<float>(len_a * len_b);
		return std::acosf(cos_theta);
	}

	template <std::uint32_t l, typename T>
	requires std::is_arithmetic_v<T>
	float angle_deg(const vec<l, T>& a, const vec<l, T>& b)
	{
		T dot_product = dot(a, b);
		T len_a = length(a);
		T len_b = length(b);
		auto cos_theta = static_cast<float>(dot_product) / static_cast<float>(len_a * len_b);
		return to_degrees(std::acosf(cos_theta));
	}
}

#endif // !MATH_VEC_OPERATIONS_H
