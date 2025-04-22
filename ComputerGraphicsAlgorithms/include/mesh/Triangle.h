#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vertex.h"
#include "algorithm"

namespace mesh
{
	struct Triangle
	{
		std::array<Vertex, 3> vertices_;

		Triangle() = default;
		Triangle(const mesh::Vertex& a, const mesh::Vertex& b, const mesh::Vertex& c)
		{
			vertices_[0] = a;
			vertices_[1] = b;
			vertices_[2] = c;
		}
		~Triangle() = default;
		Triangle(const Triangle& other);
		Triangle& operator=(const Triangle& other);
	};
}



#endif // !TRIANGLE_H
