#ifndef LIGHT_H
#define LIGHT_H

#include "raytracer_math.h"
#include "../rendering/PixelBuffer.h"
#include "../intersections/IntersectionResult.h"
#include "../primitives/primitives.h"


namespace lights
{
	class Light
	{
		public:
			math::vec3 position;
			rendering::color4f color;
			float intensity;

			virtual bool IsInShadow(intersections::IntersectionResult intersectionInfo, primitives::geometry& geometry) = 0;
	};

}

#endif // !LIGHT_H

