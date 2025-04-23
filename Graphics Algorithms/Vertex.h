#ifndef VERTEX_H
#define VERTEX_H

#include "raytracer_math.h"
#include "ColorBuffer.h"

struct Vertex
{
	math::vec3 position;
	math::vec3 normal;
	Color4 color;
};

#endif // !VERTEX_H