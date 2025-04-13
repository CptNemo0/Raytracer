#ifndef PRIMITIVES_GEOMETRY_H
#define PRIMITIVES_GEOMETRY_H

#include <optional>
#include <memory>

#include "../intersections/Ray.h"
#include "../intersections/IntersectionResult.h"
#include "raytracer_math.h"
#include "../rendering/Material.h"


namespace primitives
{
	template <typename T>
	class Geometry
	{
	public:
		std::shared_ptr<rendering::Material> material_;
		intersections::IntersectionResult Intersect(const intersections::Ray& ray, float range = 0.0f) const;

	protected:
		Geometry() = default;
	};

	template<typename T>
	inline intersections::IntersectionResult Geometry<T>::Intersect(const intersections::Ray& ray, float range) const
	{
		auto& derived = (T&)(*this);
		return derived.IntersectImpl(ray, range);
	}
}

#endif // !PRIMITIVES_GEOMETRY_H