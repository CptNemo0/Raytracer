#ifndef MESH_SPHERE
#define MESH_SPHERE

#include "ProceduralMesh.h"
#include "raytracer_math.h"

namespace mesh
{
	class Sphere : public ProceduralMesh
	{
		const float radius_;
		const std::uint32_t vertical_subdivisions_;
		const std::uint32_t horizontal_subdivisions_;
	public:
		Sphere(const float radius, const int vertical_subdivisions, const int horizontal_subdivisions)
			: radius_(std::max(std::numeric_limits<float>().min(), radius)),
			  vertical_subdivisions_(vertical_subdivisions),
			  horizontal_subdivisions_(std::max(3, horizontal_subdivisions)) {
		}
		virtual void GenerateMesh() override;
	};
}


#endif // !MESH_SPHERE
