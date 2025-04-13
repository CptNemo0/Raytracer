#include "Sphere.h"
#include <algorithm>
#include <iostream>

namespace primitives
{
    intersections::IntersectionResult Sphere::IntersectImpl(const intersections::Ray& ray, float range) const
    {
		intersections::IntersectionResult result;

		math::vec3 oc = ray.origin_ - center_;
		float a = math::dot(ray.direction_, ray.direction_);
		float b = 2.0f * math::dot(oc, ray.direction_);
		float c = math::dot(oc, oc) - radius_ * radius_;
		float discriminant = b * b - 4 * a * c;

		if (discriminant < 0) return result;

		float sqrtDisc = std::sqrt(discriminant);
		float t1 = (-b - sqrtDisc) / (2.0f * a);
		float t2 = (-b + sqrtDisc) / (2.0f * a);

		float t = (t1 > 0) ? t1 : ((t2 > 0) ? t2 : -1.0f);
		if (t < 0 || t > range) return result;

		result.type = intersections::IntersectionType::HIT;
		result.intersection_point = ray.SolveParametricEquation(t);
		result.intersection_normal = math::normalized(result.intersection_point - center_);
		result.distance = math::distance(result.intersection_point, ray.origin_);
		
		
		return result;
    }
}

