#include "transformations.h"

namespace math
{
	mat4x4 rotation_matrix_x(float angle, bool radians)
	{
		if (!radians)
		{
			angle = to_radians(angle);
		}

		auto sin = std::sinf(angle);
		auto cos = std::cosf(angle);

		return mat4x4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  cos,  sin, 0.0f,
			0.0f, -sin,  cos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	mat4x4 rotation_matrix_y(float angle, bool radians)
	{
		if (!radians)
		{
			angle = to_radians(angle);
		}

		auto sin = std::sinf(angle);
		auto cos = std::cosf(angle);

		return mat4x4(
			cos, 0.0f, -sin, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sin, 0.0f, cos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	mat4x4 rotation_matrix_z(float angle, bool radians)
	{
		if (!radians)
		{
			angle = to_radians(angle);
		}

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
}

