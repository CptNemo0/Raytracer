#include "mesh/Torus.h"

namespace mesh
{
    void Torus::GenerateMesh()
    {
        vertices_.clear();
        indices_.clear();

		const auto major_step = math::two_pi / static_cast<float>(major_subdivisions_);
		const auto minor_step = math::two_pi / static_cast<float>(minor_subdivisions_);

		const auto major_step_uv = 1.0f / static_cast<float>(major_subdivisions_);
		const auto minor_step_uv = 1.0f / static_cast<float>(minor_subdivisions_);

		int i = 0;
        for (float alpha = 0.0f; alpha < math::two_pi; alpha += major_step)
        {
            const auto minor_x = std::cos(alpha) * major_radius_;
            const auto minor_y = 0.0f;
            const auto minor_z = std::sin(alpha) * major_radius_;

			math::vec3 minor_base = math::vec3(minor_x, minor_y, minor_z);
			math::vec3 direction = math::normalized(math::vec3(minor_x, minor_y, minor_z));
			
			int j = 0;
            for (float beta = 0.0f; beta < math::two_pi; beta += minor_step)
            {
                auto normal = math::normalized(direction * std::cos(beta) + math::vec3(0.0f, 1.0f, 0.0f) * std::sin(beta));
				auto position = minor_base + normal * minor_radius_;
				auto uv = math::vec2(major_step_uv * i, minor_step_uv * j);
				vertices_.emplace_back(std::move(position), std::move(normal), std::move(uv));
				j++;
            }
			i++;
        }

		for (std::uint32_t i = 0; i < major_subdivisions_; ++i)
		{
			const auto this_subidivision_start = i * minor_subdivisions_;
			const auto next_subidivision_start = ((i + 1) % major_subdivisions_) * minor_subdivisions_;

			for (std::uint32_t j = 0; j < minor_subdivisions_; ++j)
			{
				const auto a = this_subidivision_start + j;
				const auto b = this_subidivision_start + ((j + 1) % minor_subdivisions_);

				const auto c = next_subidivision_start + j;
				const auto d = next_subidivision_start + ((j + 1) % minor_subdivisions_);

				indices_.emplace_back(a, c, d);
				indices_.emplace_back(a, d, b);
			}
		}

		RecalculateNormals();
		//RecalculateUVs();
    }
}