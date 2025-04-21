#ifndef VERTEX_H
#define VERTEX_H

#include <array>
#include "raytracer_math.h"
#include "aliasing.h"

namespace rtr
{
	struct Vertex
	{
		math::vec3 position;
		//math::vec3 normal;
		//color4f	   color;
	};
}

#endif // !VERTEX_H

