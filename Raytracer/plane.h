#pragma once

#include "vec.h"
#include "ray.h"

namespace primitives
{
	class Plane
	{
	public:
		Plane() {};
		Plane(const math::vec3& normal, const math::vec3& point0) 
			: normal_(normal), point0_(point0) {}


		const math::vec3& getNormal() const { return normal_; }
		const math::vec3& getPoint0() const { return point0_; }

		void setNormal(const math::vec3& normal) { normal_ = normal; }
		void setPoint0(const math::vec3& point0) { point0_ = point0; }

	private:
		math::vec3 normal_;
		math::vec3 point0_;
	};
}