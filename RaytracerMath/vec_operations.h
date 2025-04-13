#ifndef MATH_VEC_OPERATIONS_H
#define MATH_VEC_OPERATIONS_H

#include <cmath>
#include "angles.h"
#include "vec.h"

namespace math
{
	template <std::uint32_t l, typename T>
	requires std::is_arithmetic_v<T>
	inline T dot(const vec<l, T>& a, const vec<l, T>& b)
	{
		T result = static_cast<T>(0);
		for (std::uint32_t i = 0; i < l; ++i)
		{
			result += a.get(i) * b.get(i);
		}
		return result;
	}

    template <typename T>
    requires std::is_arithmetic_v<T>
	inline vec<3, T> cross(const vec<3, T>& a, const vec<3, T>& b)
    {
        vec<3, T> result;
        result[0] = a.get(1) * b.get(2) - a.get(2) * b.get(1);
		result[1] = a.get(2) * b.get(0) - a.get(0) * b.get(2);
		result[2] = a.get(0) * b.get(1) - a.get(1) * b.get(0);
        return result;
    }

	template <std::uint32_t l, typename T>
	requires std::is_arithmetic_v<T>
	inline T length(const vec<l, T>& a)
	{
		T result = static_cast<T>(0);

		for (std::uint32_t i = 0; i < l; i++)
		{
			result += a.get(i) * a.get(i);
		}

		return static_cast<T>(std::sqrtf(static_cast<float>(result)));
	}

	template <std::uint32_t l, typename T>
		requires std::is_arithmetic_v<T>
	inline T length2(const vec<l, T>& a)
	{
		T result = static_cast<T>(0);

		for (std::uint32_t i = 0; i < l; i++)
		{
			result += a.get(i) * a.get(i);
		}

		return static_cast<T>(result);
	}

	template <std::uint32_t l, typename T>
	requires std::is_arithmetic_v<T>
	inline T distance(const vec<l, T>& a, const vec<l, T>& b)
	{
		auto c = b - a;
		return length(c);
	}

	template <std::uint32_t l, typename T>
		requires std::is_arithmetic_v<T>
	inline T distance2(const vec<l, T>& a, const vec<l, T>& b)
	{
		auto c = b - a;
		return length2(c);
	}

	template <std::uint32_t l, typename T>
	requires std::is_arithmetic_v<T>
	inline void normalize(vec<l, T>& v)
	{
		auto len = length(v);
		v /= len;
	}

	template <std::uint32_t l, typename T>
	requires std::is_arithmetic_v<T>
	inline vec<l, T> normalized(const vec<l, T>& v)
	{
		auto len = length(v);
		auto inv_len = 1.0f / len;
		return v * inv_len;
	}

	template <std::uint32_t l, typename T>
	requires std::is_arithmetic_v<T>
	inline float angle_rad(const vec<l, T>& a, const vec<l, T>& b)
	{
		T dot_product = dot(a, b);
		T len_a = length(a);
		T len_b = length(b);
		auto cos_theta = static_cast<float>(dot_product) / static_cast<float>(len_a * len_b);
		return std::acosf(cos_theta);
	}

	template <std::uint32_t l, typename T>
	requires std::is_arithmetic_v<T>
	inline float angle_deg(const vec<l, T>& a, const vec<l, T>& b)
	{
		return to_degrees(angle_rad(a, b));
	}
}

#endif // !MATH_VEC_OPERATIONS_H
