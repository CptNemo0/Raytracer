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
	class Renderer
	{
	public:
		Renderer() = default;
		Renderer(rendering::Camera* camera, rendering::PixelBuffer* buffer, std::uint32_t max_depth)
			: camera_(camera), buffer_(buffer), max_depth_(max_depth){
		}

		void AddPointLight(const lights::PointLight& light);

		std::shared_ptr<primitives::Sphere> AddSphere();
		std::shared_ptr<primitives::Sphere> AddSphere(const math::vec3& center, float radius);

		std::shared_ptr<primitives::Triangle> AddTriangle(const math::vec3& a, const math::vec3& b, const math::vec3& c);
		std::shared_ptr<primitives::Triangle> AddTriangle(const math::vec3& a, const math::vec3& b, const math::vec3& c, const math::vec3& na, const math::vec3& nb, const math::vec3& nc);

		std::shared_ptr<primitives::Plane> AddPlane(const math::vec3& normal, const math::vec3& point);

		rendering::color4f CalculatePointLighting(const intersections::IntersectionResult& result, const rendering::Material& material_, const lights::PointLight light) const;

		void Render();
		void FillBackground();

		bool TraceToLight(const lights::PointLight& light, const math::vec3& initial_position, int n)
		{
			//&& new_result.distance < new_distance && !(new_mat.material_type_ == MaterialType::REFRACTIVE)
			if (n == 5) return false;
			auto new_distance = math::distance(initial_position, light.position);
			auto direction = math::normalized(light.position - initial_position);
			auto ray = intersections::Ray(initial_position, direction);
			const auto& [first_result, first_mat] = ShootRay(ray);

			if (first_result.type == intersections::IntersectionType::MISS ||
				(first_result.type == intersections::IntersectionType::HIT && first_result.distance > new_distance)) return true;
			if (first_mat.material_type_ != MaterialType::REFRACTIVE) return false;
			
			auto refracted_dir = math::refract(ray.direction_, first_result.intersection_normal, first_mat.refraction_index_);
			if (refracted_dir == math::vec3(0.0f)) return false;

			auto refracted_origin = first_result.intersection_point + ray.direction_ * 0.001f;
			auto refracted_ray = intersections::Ray(refracted_origin, refracted_dir);
			const auto& [refracted_result, refracted_material] = ShootRay(refracted_ray);
			refracted_dir = math::refract(refracted_ray.direction_, refracted_result.intersection_normal, 1.0f / refracted_material.refraction_index_);
			refracted_origin = refracted_result.intersection_point + refracted_ray.direction_ * 0.0001f;

			return TraceToLight(light, refracted_origin, n + 1);
		}

	private:
		Camera* camera_;
		PixelBuffer* buffer_;
		std::vector<primitives::geometry_sp> scene_;
		std::vector<lights::PointLight> lights_;
		std::pair<intersections::IntersectionResult, rendering::Material> ShootRay(const intersections::Ray& ray) const;
		std::uint32_t max_depth_ = 1;		
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
