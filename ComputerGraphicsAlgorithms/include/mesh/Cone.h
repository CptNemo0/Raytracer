#ifndef MESH_CONE_H
#define MESH_CONE_H

#include <algorithm>
#include <cstdint>
#include <limits>

#include "ProceduralMesh.h"

namespace mesh
{
	class Cone : public ProceduralMesh
	{
		float radius_;
		float height_;
		std::uint32_t subdivisions_;

	public:
		Cone(const float radius, const float height, const int subdivisions)
			: radius_(std::max(std::numeric_limits<float>().min(), radius)), height_(std::max(std::numeric_limits<float>().min(), height)), subdivisions_(std::max(3, subdivisions)) {}
		
		virtual void GenerateMesh() override;
	};
}

#endif // !MESH_CONE_H
