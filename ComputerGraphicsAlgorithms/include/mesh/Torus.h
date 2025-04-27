#ifndef MESH_TORUS
#define MESH_TORUS

#include "ProceduralMesh.h"
#include "raytracer_math.h"

namespace mesh
{
	class Torus : public ProceduralMesh
	{
		const float major_radius_;
		const float minor_radius_;
		const std::uint32_t major_subdivisions_;
		const std::uint32_t minor_subdivisions_;

		
	public:
		void GenerateMesh() override;
		
		Torus(float major_radius_, float minor_radius_, const std::uint32_t& major_subdivisions_, const std::uint32_t& minor_subdivisions_)
			: major_radius_(major_radius_), minor_radius_(minor_radius_), major_subdivisions_(major_subdivisions_), minor_subdivisions_(minor_subdivisions_) {
		}
	};
}

#endif // !MESH_TORUS

