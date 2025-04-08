#ifndef RENDERING_RENDERER_H
#define RENDERING_RENDERER_H

#include "Camera.h"
#include "PixelBuffer.h"
#include "../primitives/primitives.h"
#include "../lights/Light.h"
#include <memory>
#include "../lights/PointLight.h"
namespace rendering
{
#define MAX_RECURSION 8
#define ADAPTIVE_THRESHOLD 0.001f

	class Renderer
	{
	public:
		Renderer() = default;
		Renderer(rendering::Camera* camera, rendering::PixelBuffer* buffer)
			: camera_(camera), buffer_(buffer) {
		}

		void AddGeometry(const primitives::geometry& geometry);
		void AddPointLight(const lights::PointLight& light);

		void RenderScene();

		std::shared_ptr<primitives::Sphere> AddSphere();
		std::shared_ptr<primitives::Sphere> AddSphere(const math::vec3& center, float radius);

		std::shared_ptr<primitives::Triangle> AddTriangle(const math::vec3& a, const math::vec3& b, const math::vec3& c);
		std::shared_ptr<primitives::Triangle> AddTriangle(const math::vec3& a, const math::vec3& b, const math::vec3& c, const math::vec3& na, const math::vec3& nb, const math::vec3& nc);

		rendering::color4f CalculatePointLighting(const intersections::IntersectionResult& result, const rendering::Material& material, const lights::PointLight light) const;

		void Render();
		void FillBackground();
	private:
		Camera* camera_;
		PixelBuffer* buffer_;
		std::vector<primitives::geometry> scene_;

		std::vector<primitives::geometry_sp> scene;

		std::vector<lights::PointLight> lights_;


		std::pair<intersections::IntersectionResult, rendering::Material> ShootRay(const intersections::Ray& ray) const;

		inline void RenderGeometry(
			const primitives::geometry& geometry,
			std::int32_t width, std::int32_t height,
			float pixel_width, float pixel_height,
			float start_x, float start_y);

		
		
	};
}

/*
num	          |   mul	         |  e^num	     |  e^num / sum
1	          |   2	             |  7.389056099	 |  0.290361336
0.5	          |   1	             |  2.718281828	 |  0.106817966
0.5	          |   1	             |  2.718281828	 |  0.106817966
0.5	          |   1	             |  2.718281828	 |  0.106817966
0.5	          |   1	             |  2.718281828	 |  0.106817966
0.292893219	  |   0.585786438	 |  1.796403189	 |  0.0705917
0.292893219	  |   0.585786438	 |  1.796403189	 |  0.0705917
0.292893219	  |   0.585786438	 |  1.796403189	 |  0.0705917
0.292893219	  |   0.585786438	 |  1.796403189	 |  0.0705917
              |                  |  25.44779617
*/

#endif // RENDERING_RENDERER_H
