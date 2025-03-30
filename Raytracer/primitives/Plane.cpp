#include "Plane.h"
#include "../intersections/IntersectionType.h"
#include "../intersections/Ray.h"
#include "float_eq.h"

namespace primitives
{
	bool Plane::Intersect3(const Plane& p2, const Plane& p3, math::vec3& result) const
	{
		const auto eq = [](float a, float b)
			{
				constexpr auto eps = std::numeric_limits<float>::epsilon();
				return fabs(a - b) < eps;
			};

		const auto n2 = p2.normal_;
		const auto n3 = p3.normal_;
		const auto n1 = normal_;
		const math::vec3 n2n3 = math::cross(n2, n3);
		const auto n3n1 = math::cross(n3, n1);
		const auto n1n2 = math::cross(n1, n2);
		const auto denominator = math::dot(n1, n2n3);

		if (eq(denominator, 0.0f)) return false;

		math::vec3 temp1;
		math::vec3 temp2;
		math::vec3 temp3;

		temp1 = n2n3 * normal_.dot(point0_);
		temp2 = n3n1 * p2.normal_.dot(p2.point0_);
		temp3 = n1n2 * p3.normal_.dot(p3.point0_);

		result = (temp1 + temp2 + temp3) / denominator;
		return true;
	}

	intersections::IntersectionResult Plane::IntersectImpl(const intersections::Ray& ray, const float range) const
	{
		intersections::IntersectionResult result;

		const float denominator = math::dot(normal_, ray.direction_);

		if (math::flt_eq(denominator, 0.0f)) return result;

		const float denominator_inv = 1.0f / denominator;
		const math::vec3 difference = point0_ - ray.origin_;
		const float t = math::dot(difference, normal_) * denominator_inv;

		if (t <= 0.0f) return result;

		if (range == 0.0f || t < range)
		{
			if (math::dot(normal_, ray.direction_) < 0.0f)
			{
				result.type = intersections::IntersectionType::HIT;
			}
			else
			{
				result.type = intersections::IntersectionType::INSIDE_PRIMITIVE;
			}

			result.intersection_point = ray.SolveParametricEquation(t);
			result.distance = t;
			result.intersection_normal = normal_;
		}

		return result;
	}
}

