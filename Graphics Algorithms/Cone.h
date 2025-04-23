#ifndef CONE_H
#define CONE_H

#include "Mesh.h"

namespace mesh
{
	class Cone : public Mesh
	{
	private:
		const float radius_;
		const float height_;
		const uint32_t slices_;

	public:
		Cone(uint32_t slices, float radius, float height)
			: slices_(slices), radius_(radius), height_(height)
		{
			vSize = slices + 2;
			tSize = slices * 2;
			vertices.resize(vSize);
			indices.resize(tSize);
			Generate();
		}
		void Generate() override
		{
			vertices.clear();
			indices.clear();

			// Apex (top of cone)
			math::vec3 apex_pos(0.0f, height_, 0.0f);
			vertices.push_back({ apex_pos, {0.0f, 1.0f, 0.0f} });

			// Base vertices
			for (uint32_t i = 0; i < slices_; ++i)
			{
				float theta = i * 2.0f * math::pi / slices_;
				float x = radius_ * cos(theta);
				float z = radius_ * sin(theta);
				math::vec3 pos(x, 0.0f, z);
				math::vec3 norm = math::normalized(math::vec3(x, height_, z));
				vertices.push_back({ pos, norm });
			}

			// Center of base (for bottom face)
			vertices.push_back({ {0.0f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f} });

			// Side triangles
			for (uint32_t i = 0; i < slices_; ++i)
			{
				uint32_t next = (i + 1) % slices_;
				indices.push_back({ 0, i + 1, next + 1 }); // apex - side
			}

			// Bottom cap triangles
			uint32_t baseCenterIndex = static_cast<uint32_t>(vertices.size()) - 1;
			for (uint32_t i = 0; i < slices_; ++i)
			{
				uint32_t next = (i + 1) % slices_;
				indices.push_back({ baseCenterIndex, next + 1, i + 1 }); // base cap
			}

			//vSize = vertices.size();
			//tSize = indices.size();
			MakeNormals();
		}
	};
}


#endif // !CONE_H



