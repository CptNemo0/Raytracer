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

		Vertex() = default;

		explicit Vertex(const float a, const float b, const float c)
		{
			position_ = math::vec3(a, b, c);
			normal_ = math::vec3(0.0f, 0.0f, 0.0f);
		}
	};
}

#endif // !MESH_VERTEX_H

