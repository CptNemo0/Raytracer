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
	inline vec<n, T> transformed(const mat<m, n, T>& matrix, const vec<n, T>& vector)
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
	inline void transform(const mat<m, n, T>& matrix, vec<n, T>& vector)
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

	mat4x4 rotation_matrix_x_rad(float angle);
	mat4x4 rotation_matrix_y_rad(float angle);
	mat4x4 rotation_matrix_z_rad(float angle);

	mat4x4 rotation_matrix_x_deg(float angle);
	mat4x4 rotation_matrix_y_deg(float angle);
	mat4x4 rotation_matrix_z_deg(float angle);

	mat4x4 translation_matrix(float x, float y, float z);
	mat4x4 scale_matrix(float x, float y, float z);

	vec3 quat_rotate_rad(vec3& vect, float angle, const vec3& axis);
	vec3 quat_rotate_deg(const vec3& vect, float angle, const vec3& axis);

	inline vec3 reflect(const vec3& vect, const vec3& normal)
	{
		return vect - normal * math::dot(vect, normal) * 2.0f;
	}

	void translate(const vec3& translation, vec4& vector);
	void rotate_rad(const vec3& rotation, vec4& vector);
	void rotate_deg(const vec3& rotation, vec4& vector);
	void scale(const vec3& scale, vec4& vector);
}

#endif // !MATH_TRANSFORMATIONS_H
