#include "mesh/Cone.h"

namespace mesh
{
	void Cone::GenerateMesh()
	{
		const std::uint32_t vertex_count = subdivisions_ + 2; // ring vertices + bottom center + top apex
		const std::uint32_t index_count = subdivisions_ * 6; 
		const float normalizing_factor = std::max(height_, radius_);

		vertices_.reserve(vertex_count);
		indices_.reserve(index_count);

		vertices_.emplace_back(0.0f, 0.0f, 0.0f);    //0 - bottom center 
		vertices_.emplace_back(0.0f, height_, 0.0f); // 1 - top apex

		const float angle_step = math::two_pi / static_cast<float>(subdivisions_);

		for (std::uint32_t i = 0; i < subdivisions_; ++i)
		{
			const float angle = i * angle_step;
			const float x = radius_ * std::cos(angle);
			const float y = 0.0f;
			const float z = radius_ * std::sin(angle);
			vertices_.emplace_back(x, y, z); // ring vertices
		}

		for (std::uint32_t i = 2; i < vertex_count; ++i)
		{
			const std::uint32_t next = (i == vertex_count - 1) ? 2 : i + 1;
			// Bottom face
			indices_.push_back(0);
			indices_.push_back(next);
			indices_.push_back(i);
			
			// Side face
			indices_.push_back(1);
			indices_.push_back(i);
			indices_.push_back(next);
			
		}
		
		RecalculateNormals();
	}
}
