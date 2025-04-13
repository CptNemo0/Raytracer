#ifndef INTERSECTIONS_INTERSECTION_RESULT_H
#define INTERSECTIONS_INTERSECTION_RESULT_H

#include "IntersectionType.h"
#include "vec.h"

namespace intersections
{
	struct IntersectionResult 
	{
		IntersectionType type = IntersectionType::MISS;
		float distance = 0.0f;
		math::vec3 intersection_point = math::vec3(0.0f, 0.0f, 0.0f);
		math::vec3 intersection_normal = math::vec3(0.0f, 0.0f, 0.0f);
	};
}

#endif // !INTERSECTIONS_INTERSECTION_RESULT_H
