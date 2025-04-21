#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vertex.h"
#include "algorithm"

struct Triangle
{
	std::array<Vertex, 3> vertices;

	Triangle() = default;
	~Triangle() = default;
	Triangle(const Triangle& other);
	Triangle& operator=(const Triangle& other);
};

#endif // !TRIANGLE_H
