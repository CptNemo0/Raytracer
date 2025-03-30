#ifndef PRIMITIVES_PLANE
#define PRIMITIVES_PLANE

#include <optional>

#include "Geometry.h"
#include "../intersections/Ray.h"
#include "../intersections/IntersectionResult.h"
#include "raytracer_math.h"

namespace primitives
{
	class Plane : public Geometry<Plane>
	{
	public:
		math::vec3 normal_ = math::vec3(0.0f, 1.0f, 0.0f);
		math::vec3 point0_ = math::vec3(0.0f);

		Plane() = default;
		Plane(const math::vec3& normal, const math::vec3& point0) : normal_(normal), point0_(point0) {}

		bool Intersect3(const Plane& p2, const Plane& p3, math::vec3& result) const;
		intersections::IntersectionResult IntersectImpl(const intersections::Ray& ray, float range) const;

		friend std::ostream& operator<<(std::ostream& os, const Plane& p)
		{
			os  << "Plane:\n"
				<< "{\n"
				<< "\tnormal_: " << p.normal_
				<< "\n\tpoint0_: " << p.point0_
				<< "\n}";
			
			return os;
		}
	};
}

#endif // !PRIMITIVES_PLANE