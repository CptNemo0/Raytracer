#pragma once
#include "raytracer_math.h"
#include "Material.h"
#include "ray.h"

namespace primitives
{
	class Geometry
	{
	public:
		Material material;
		virtual intersections::IntersectionResult Intersects(const intersections::Ray& ray, float range = 0.0f) const = 0;

	};
}


