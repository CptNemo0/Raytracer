#ifndef MESH_VERTEX_H
#define MESH_VERTEX_H

#include <array>
#include "raytracer_math.h"
#include "aliasing.h"

namespace mesh
{
	struct Vertex
	{
		math::vec3 position_;
		math::vec3 normal_;
		math::vec2 uv_;

		Vertex() = default;

		explicit Vertex(const float a, const float b, const float c)
		{
			position_ = math::vec3(a, b, c);
			normal_ = math::vec3(0.0f, 0.0f, 0.0f);
			uv_ = math::vec2(0.0);
		}

		explicit Vertex(const math::vec3& position)
		{
			position_ = position;
			normal_ = math::vec3(0.0f, 0.0f, 0.0f);
			uv_ = math::vec2(0.0);
		}

		explicit Vertex(math::vec3&& position, math::vec3&& normal)
		{
			position_ = position;
			normal_ = normal;
			uv_ = math::vec2(0.0);
		}

		explicit Vertex(math::vec3&& position, math::vec3&& normal, math::vec2&& uv)
		{
			position_ = position;
			normal_ = normal;
			uv_ = uv;
		}
	};
}

#endif // !MESH_VERTEX_H

