#ifndef INTERSECTIONS_RAY_H
#define INTERSECTIONS_RAY_H

#include <iostream>
#include "raytracer_math.h"

namespace intersections
{
	class Ray
	{
	public:
		math::vec3 origin_;
		math::vec3 direction_;
		math::vec3 destination_;
		float distance_ = 0.0f;

		Ray() : origin_(), direction_(), destination_() {}
		Ray(const math::vec3& origin, const math::vec3& destination) : origin_(origin), direction_(math::normalized(destination - origin)), destination_(destination) {}
		Ray(const math::vec3& origin, float distance) : origin_(origin), direction_(), destination_(origin), distance_(distance) {}
		Ray(const math::vec3& origin, const math::vec3& direction, float distance) : origin_(origin), direction_(direction), destination_(origin + direction * distance), distance_(distance) {}
		~Ray() {};

		inline math::vec3 SolveParametricEquation(float t) const
		{
			return origin_ + direction_ * t;
		}

		friend std::ostream& operator<<(std::ostream& os, const Ray& ray)
		{
			os << "Ray\n("
				<< "Origin: " << ray.origin_
				<< ",\nDirection: " << ray.direction_
				<< ",\nDestination: " << ray.destination_
				<< ",\nDistance: " << ray.distance_
				<< ")";
			return os;
		}
	};
}

#endif // !INTERSECTIONS_RAY_H