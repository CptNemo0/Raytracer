#include "mesh/ProceduralMesh.h"

namespace mesh
{
	void ProceduralMesh::RecalculateNormals()
	{
		for (auto& vertex : vertices_)
		{
			vertex.normal_ = math::vec3(0.0f, 0.0f, 0.0f);
		}

		for (std::size_t i = 0; i < indices_.size(); i += 3)
		{
			const auto& v0 = vertices_[indices_[i]];
			const auto& v1 = vertices_[indices_[i + 1]];
			const auto& v2 = vertices_[indices_[i + 2]];

			const math::vec3 edge1 = v1.position_ - v0.position_;
			const math::vec3 edge2 = v2.position_ - v0.position_;
			const math::vec3 normal = math::normalized(math::cross(edge2, edge1));

			vertices_[indices_[i]].normal_ += normal;
			vertices_[indices_[i + 1]].normal_ += normal;
			vertices_[indices_[i + 2]].normal_ += normal;
		}

		for (auto& vertex : vertices_)
		{
			math::normalize(vertex.normal_);
		}
	}
}