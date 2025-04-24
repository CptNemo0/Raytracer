#include "mesh/Torus.h"

namespace mesh
{
    void Torus::GenerateMesh()
    {
        vertices_.clear();
        indices_.clear();

        const float pi = 3.14159265359f;
        const float two_pi = 2.0f * pi;

        // Loop through vertical and horizontal subdivisions to generate vertices
        for (std::uint32_t i = 0; i <= vertical_subdivisions_; ++i)
        {
            float v = static_cast<float>(i) / vertical_subdivisions_;
            float phi = v * two_pi;

            for (std::uint32_t j = 0; j <= horizontal_subdivisions_; ++j)
            {
                float u = static_cast<float>(j) / horizontal_subdivisions_;
                float theta = u * two_pi;

                // Calculate vertex position
                float x = (radius1_ + radius2_ * std::cos(phi)) * std::cos(theta);
                float y = (radius1_ + radius2_ * std::cos(phi)) * std::sin(theta);
                float z = radius2_ * std::sin(phi);

                // Add vertex to the list
                vertices_.emplace_back(Vertex{ x, y, z });
            }
        }

        // Generate indices for the torus
        for (std::uint32_t i = 0; i < vertical_subdivisions_; ++i)
        {
            for (std::uint32_t j = 0; j < horizontal_subdivisions_; ++j)
            {
                std::uint32_t current = i * (horizontal_subdivisions_ + 1) + j;
                std::uint32_t next = current + horizontal_subdivisions_ + 1;

                // First triangle
                indices_.push_back(current);
                indices_.push_back(next);
                indices_.push_back(current + 1);

                // Second triangle
                indices_.push_back(current + 1);
                indices_.push_back(next);
                indices_.push_back(next + 1);
            }
        }

        // Recalculate normals for the generated mesh
        RecalculateNormals();
    }
}