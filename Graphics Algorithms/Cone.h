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
			Vertex apex;
			apex.position = apex_pos;
			apex.normal = { 0.0f, 1.0f, 0.0f };
			apex.uv = { 0.5f, 1.0f };
			vertices.push_back(apex);

			// Base vertices
			for (uint32_t i = 0; i < slices_; ++i)
			{
				float theta = i * 2.0f * math::pi / slices_;
				float x = radius_ * cos(theta);
				float z = radius_ * sin(theta);
				math::vec3 pos(x, 0.0f, z);
				math::vec3 norm = math::normalized(math::vec3(x, height_, z));

				Vertex v;
				v.position = pos;
				v.normal = norm;
				v.uv = { static_cast<float>(i) / slices_, 0.0f };  
				vertices.push_back(v);
			}

			// Center of base (for bottom face)
			Vertex baseCenter;
			baseCenter.position = { 0.0f, 0.0f, 0.0f };
			baseCenter.normal = { 0.0f, -1.0f, 0.0f };
			baseCenter.uv = { 0.5f, 0.5f };
			vertices.push_back(baseCenter);

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
				Vertex& vi = vertices[i + 1];
				Vertex& vj = vertices[next + 1];

				// Dodaj UV dla podstawy (radykalne mapowanie)
				float ui = 0.5f + (vi.position[0] / (2.0f * radius_));
				float vi_uv = 0.5f + (vi.position[2] / (2.0f * radius_));
				vi.uv = { ui, vi_uv };

				float uj = 0.5f + (vj.position[0] / (2.0f * radius_));
				float vj_uv = 0.5f + (vj.position[2] / (2.0f * radius_));
				vj.uv = { uj, vj_uv };

				indices.push_back({ baseCenterIndex, next + 1, i + 1 });
			}

			//vSize = vertices.size();
			//tSize = indices.size();
			//MakeNormals();

			for (auto& vertex : vertices)
			{
				vertex.normal = math::normalized(vertex.position);
			}
		}
	};
}


#endif // !CONE_H



