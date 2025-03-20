#include "pch.h"

namespace math
{
	mat4x4 rotation_matrix_x_rad(float angle)
	{
		auto sin = std::sinf(angle);
		auto cos = std::cosf(angle);

		return mat4x4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  cos,  sin, 0.0f,
			0.0f, -sin,  cos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	mat4x4 rotation_matrix_y_rad(float angle)
	{
		auto sin = std::sinf(angle);
		auto cos = std::cosf(angle);

		return mat4x4(
			cos, 0.0f, -sin, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sin, 0.0f, cos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	mat4x4 rotation_matrix_z_rad(float angle)
	{
		auto sin = std::sinf(angle);
		auto cos = std::cosf(angle);

		return mat4x4(
			cos, -sin, 0.0f, 0.0f,
			sin, cos, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	
	mat4x4 rotation_matrix_x_deg(float angle)
	{
		angle = to_radians(angle);
		auto sin = std::sinf(angle);
		auto cos = std::cosf(angle);

		return mat4x4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cos, sin, 0.0f,
			0.0f, -sin, cos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	mat4x4 rotation_matrix_y_deg(float angle)
	{
		angle = to_radians(angle);
		auto sin = std::sinf(angle);
		auto cos = std::cosf(angle);

		return mat4x4(
			cos, 0.0f, -sin, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sin, 0.0f, cos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	mat4x4 rotation_matrix_z_deg(float angle)
	{
		angle = to_radians(angle);
		auto sin = std::sinf(angle);
		auto cos = std::cosf(angle);

		return mat4x4(
			cos, -sin, 0.0f, 0.0f,
			sin, cos, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	mat4x4 translation_matrix(float x, float y, float z)
	{
		return mat4x4(
			1.0f, 0.0f, 0.0f, x,
			0.0f, 1.0f, 0.0f, y,
			0.0f, 0.0f, 1.0f, z,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	mat4x4 scale_matrix(float x, float y, float z)
	{
		return mat4x4(
			x, 0.0f, 0.0f, 0.0f,
			0.0f, y, 0.0f, 0.0f,
			0.0f, 0.0f, z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	
	void translate(const vec3& translation, vec4& vector)
	{
		auto M = translation_matrix(translation.get(0), translation.get(1), translation.get(2));
		transform(M, vector);
	}
	void rotate_rad(const vec3& rotation, vec4& vector)
	{
		auto X = rotation_matrix_x_rad(rotation.get(0));
		auto Y = rotation_matrix_y_rad(rotation.get(1));
		auto Z = rotation_matrix_z_rad(rotation.get(2));
		auto rotation_matrix = matmul(X, Y);
		rotation_matrix = matmul(rotation_matrix, Z);
		transform(rotation_matrix, vector);
	}
	void rotate_deg(const vec3& rotation, vec4& vector)
	{
		auto X = rotation_matrix_x_rad(to_radians(rotation.get(0)));
		auto Y = rotation_matrix_y_rad(to_radians(rotation.get(1)));
		auto Z = rotation_matrix_z_rad(to_radians(rotation.get(2)));
		auto rotation_matrix = matmul(X, Y);
		rotation_matrix = matmul(rotation_matrix, Z);
		transform(rotation_matrix, vector);
	}
	void scale(const vec3& scale, vec4& vector)
	{
		auto M = scale_matrix(scale.get(0), scale.get(1), scale.get(2));
		transform(M, vector);
	}
}

