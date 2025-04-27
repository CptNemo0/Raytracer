#ifndef MESH_PROCEDURAL_MESH_H
#define MESH_PROCEDURAL_MESH_H

#include <vector>
#include <cstdint>

#include "Vertex.h"
#include "raytracer_math.h"

namespace mesh
{
	class ProceduralMesh
	{
	public:
		std::vector<Vertex> vertices_;
		std::vector<math::ivec3> indices_;

	public:
		void RecalculateNormals();
		virtual void GenerateMesh() = 0;
	};
}

#endif // MESH_PROCEDURAL_MESH_H
