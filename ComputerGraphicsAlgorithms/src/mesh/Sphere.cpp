#include "mesh/Sphere.h"

void mesh::Sphere::GenerateMesh()
{
	const std::uint32_t vertex_count = (vertical_subdivisions_ + 1) * (horizontal_subdivisions_ + 1);
	const std::uint32_t index_count = vertical_subdivisions_ * horizontal_subdivisions_ * 6;
	vertices_.reserve(vertex_count);
	indices_.reserve(index_count);

	auto subsetp_u = 1.0f / static_cast<float>(vertical_subdivisions_);
	auto subsetp_v = 1.0f / static_cast<float>(horizontal_subdivisions_);

	for (std::uint32_t i = 0; i <= vertical_subdivisions_; ++i)
	{
		const float theta = static_cast<float>(i) / static_cast<float>(vertical_subdivisions_) * math::pi;
		const float sin_theta = std::sin(theta);
		const float cos_theta = std::cos(theta);
		for (std::uint32_t j = 0; j <= horizontal_subdivisions_; ++j)
		{
			const float phi = static_cast<float>(j) / static_cast<float>(horizontal_subdivisions_) * math::two_pi;
			const float sin_phi = std::sin(phi);
			const float cos_phi = std::cos(phi);
			const float x = radius_ * sin_theta * cos_phi;
			const float y = radius_ * cos_theta;
			const float z = radius_ * sin_theta * sin_phi;

			math::vec3 position(x, y, z);
			math::vec3 normal = math::normalized(position);
			math::vec2 uv(subsetp_u * static_cast<float>(j), subsetp_v * static_cast<float>(i));
			vertices_.emplace_back(std::move(position), std::move(normal), std::move(uv));
		}
	}

	for (std::uint32_t i = 0; i < vertical_subdivisions_; ++i)
	{
		for (std::uint32_t j = 0; j < horizontal_subdivisions_; ++j)
		{
			const std::uint32_t first = (i * (horizontal_subdivisions_ + 1)) + j;
			const std::uint32_t second = first + horizontal_subdivisions_ + 1;
			
			indices_.emplace_back(first, second, first + 1);
			indices_.emplace_back(second, second + 1, first + 1);
		}
	}

	for (auto& vertex : vertices_)
	{
		vertex.normal_ = math::normalized(vertex.position_);
	}
	//RecalculateUVs();
	//RecalculateNormals();
}
