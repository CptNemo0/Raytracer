#ifndef MATH_TRANSFORMATIONS_H
#define MATH_TRANSFORMATIONS_H

#include <cmath>
#include <cstdint>

#include "mat.h"
#include "vec.h"	
#include "vec_operations.h"
#include "mat_operations.h"

namespace math
{
	template <std::uint32_t m, std::uint32_t n, typename T>
	requires std::is_arithmetic_v<T>
	vec<n, T> transformed(const mat<m, n, T>& matrix, const vec<n, T>& vector)
	{
		vec<n, T> result;
		for (std::uint32_t i = 0; i < n; i++)
		{
			T sum = 0;
			for (std::uint32_t j = 0; j < n; j++)
			{
				sum += matrix.get(j, i) * vector.get(j);
			}
			result[i] = sum;
		}
		return result;
	}

	template <std::uint32_t m, std::uint32_t n, typename T>
	requires std::is_arithmetic_v<T>
	void transform(const mat<m, n, T>& matrix, vec<n, T>& vector)
	{
		vec<n, T> result;
		for (std::uint32_t i = 0; i < n; i++)
		{
			T sum = 0;
			for (std::uint32_t j = 0; j < n; j++)
			{
				sum += matrix.get(j, i) * vector.get(j);
			}
			result[i] = sum;
		}
		vector = result;
	}

	mat4x4 rotation_matrix_x(float angle, bool radians = true);
	mat4x4 rotation_matrix_y(float angle, bool radians = true);
	mat4x4 rotation_matrix_z(float angle, bool radians = true);
	mat4x4 translation_matrix(float x, float y, float z);
	mat4x4 scale_matrix(float x, float y, float z);
}

#endif // !MATH_TRANSFORMATIONS_H
