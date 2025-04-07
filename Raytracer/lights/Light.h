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
			rendering::color3 color;
			float intensity;

			virtual rendering::color3 getDiffuse(math::vec3 cameraPosition, intersections::IntersectionResult intersectionInfo) = 0;
			virtual rendering::color3 getSpecular(math::vec3 cameraPosition, intersections::IntersectionResult intersectionInfo) = 0;
			virtual bool isInShadow(intersections::IntersectionResult intersectionInfo, primitives::geometry& geometry) = 0;
	};

}

#endif // !LIGHT_H

