#ifndef TORUS_H
#define TORUS_H

#include "Mesh.h"
#include "raytracer_math.h"

namespace mesh
{	
	class Torus : public Mesh
	{
	private:
		const float majorRadius_;  // R
		const float minorRadius_;  // r
		const uint32_t majorSegments_;
		const uint32_t minorSegments_;

	public:
		Torus(uint32_t majorSeg, uint32_t minorSeg, float R, float r)
			: majorSegments_(majorSeg), minorSegments_(minorSeg), majorRadius_(R), minorRadius_(r)
		{
			vSize = (majorSegments_ + 1) * (minorSegments_ + 1);
			tSize = majorSegments_ * minorSegments_ * 2;
			vertices.resize(vSize);
			indices.resize(tSize);
			Generate();
		}

		void Generate() override
		{
			vertices.clear();
			indices.clear();

			for (uint32_t i = 0; i <= majorSegments_; ++i)
			{
				float theta = 2.0f * math::pi * i / majorSegments_;
				float cosTheta = cos(theta);
				float sinTheta = sin(theta);

				for (uint32_t j = 0; j <= minorSegments_; ++j)
				{
					float phi = 2.0f * math::pi * j / minorSegments_;
					float cosPhi = cos(phi);
					float sinPhi = sin(phi);

					float x = (majorRadius_ + minorRadius_ * cosPhi) * cosTheta;
					float y = minorRadius_ * sinPhi;
					float z = (majorRadius_ + minorRadius_ * cosPhi) * sinTheta;

					float nx = x - majorRadius_ * cosTheta;
					float ny = y;
					float nz = z - majorRadius_ * sinTheta;

					math::vec3 n(nx, ny, nz);
					math::vec3 normal = math::normalized(n);

					vertices.push_back({ {x, y, z}, normal });
				}
			}

			for (uint32_t i = 0; i < majorSegments_; ++i)
			{
				for (uint32_t j = 0; j < minorSegments_; ++j)
				{
					uint32_t a = i * (minorSegments_ + 1) + j;
					uint32_t b = ((i + 1) % (majorSegments_ + 1)) * (minorSegments_ + 1) + j;
					uint32_t c = a + 1;
					uint32_t d = b + 1;

					indices.push_back({ a, c, b });
					indices.push_back({ c, d, b });
				}
			}

			vSize = vertices.size();
			tSize = indices.size();
			MakeNormals();
		}
	};
}

#endif // !TORUS_H
