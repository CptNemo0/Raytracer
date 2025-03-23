#pragma once

#include "vec.h"
#include "ray.h"
#include "raytracer_math.h"


namespace primitives
{
	class Plane
	{
	public:
		Plane() {};
		Plane(const math::vec3& normal, const math::vec3& point0) 
			: normal_(normal), point0_(point0) {}
		Plane(const math::vec3& normal, const math::vec3& point0, float distance)
			: normal_(normal), point0_(point0), distance_(distance) {}


		bool Intersect3(const Plane& p2, const Plane& p3, math::vec3& result) const
		{
			auto n2 = p2.getNormal();
			auto n3 = p3.getNormal();
			auto n1 = getNormal();
			const math::vec3 n2n3 = math::cross(n2, n3);
			auto n3n1 = math::cross(n3, n1);
			auto n1n2 = math::cross(n1, n2);
			auto denom = n1.dot(n2n3);

			if (denom == 0) return false;

			math::vec3 temp1, temp2, temp3;
			temp1 = n2n3 * distance_;
			temp2 = n3n1 * p2.distance_;
			temp3 = n1n2 * p3.distance_;

			result = (temp1 + temp2 + temp3) / denom;
			return true;
		}

		intersections::IntersectionResult Intersects(const intersections::Ray& ray, float range) const
		{
			intersections::IntersectionResult result;
			result.type = intersections::IntersectionResult::MISS;

			float denom = normal_.dot(ray.getDirection());
			if (denom == 0)
			{
				return result;
			}
			float t = (- distance_ - normal_.dot(ray.getOrigin())/denom);

			if (t > 0)
			{
				if (range == 0.0f || t < range)
				{
					if (normal_.dot(ray.getDirection()) < 0) 
					{
						result.type = intersections::IntersectionResult::HIT;
					}
					else
					{
						result.type = intersections::IntersectionResult::INSIDE_PRIMITIVE;
					}
					result.LPOINT = ray.solveParametricEquation(t);
					result.distance = t;
					result.intersectionNormal = normal_;
				}
			}
			return result;
		}

		const math::vec3& getNormal() const { return normal_; }
		const math::vec3& getPoint0() const { return point0_; }

		void setNormal(const math::vec3& normal) { normal_ = normal; }
		void setPoint0(const math::vec3& point0) { point0_ = point0; }

	private:
		math::vec3 normal_;
		math::vec3 point0_;
		float distance_;
	};
}