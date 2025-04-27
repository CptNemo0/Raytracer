#include "mesh/ProceduralMesh.h"

namespace mesh
{
	void ProceduralMesh::RecalculateNormals()
	{
		for (auto& vertex : vertices_)
		{
			vertex.normal_ = math::vec3(0.0f, 0.0f, 0.0f);
		}

		for (const auto& index : indices_)
		{
			const auto& v0 = vertices_[index.get(0)];
			const auto& v1 = vertices_[index.get(1)];
			const auto& v2 = vertices_[index.get(2)];

			const math::vec3 edge1 = v1.position_ - v0.position_;
			const math::vec3 edge2 = v2.position_ - v0.position_;
			const math::vec3 normal = math::normalized(math::cross(edge2, edge1));

			vertices_[index.get(0)].normal_ += normal;
			vertices_[index.get(1)].normal_ += normal;
			vertices_[index.get(2)].normal_ += normal;
		}

		for (auto& vertex : vertices_)
		{
			math::normalize(vertex.normal_);
		}
	}
}