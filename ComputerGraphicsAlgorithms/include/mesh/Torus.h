#ifndef MESH_TORUS
#define MESH_TORUS

#include "ProceduralMesh.h"
#include "raytracer_math.h"

namespace mesh
{
	class Torus : public ProceduralMesh
	{
		const float radius1_;
		const float radius2_;
		const std::uint32_t vertical_subdivisions_;
		const std::uint32_t horizontal_subdivisions_;

		
	public:
		void GenerateMesh() override;
		Torus(float radius1_, float radius2_, const std::uint32_t& vertical_subdivisions_, const std::uint32_t& horizontal_subdivisions_)
			: radius1_(radius1_), radius2_(radius2_), vertical_subdivisions_(vertical_subdivisions_), horizontal_subdivisions_(horizontal_subdivisions_) {}
	};
}

#endif // !MESH_TORUS

