#ifndef VERTEX_H
#define VERTEX_H

#include <array>
#include "raytracer_math.h"
#include "aliasing.h"

struct Vertex
{
	math::vec3 position;
	color4f	   color;
};

#endif // !VERTEX_H

