#pragma once
#include "../lights/Light.h"

namespace lights
{
    class PointLight : public Light
    {
    public:
        PointLight(const math::vec3& position, const rendering::color3& color, float intensity)
        {
            this->position = position;
            this->color = color;
            this->intensity = intensity;
        }

        virtual rendering::color3 getDiffuse(math::vec3 cameraPosition, intersections::IntersectionResult intersectionInfo) override;

        virtual rendering::color3 getSpecular(math::vec3 cameraPosition, intersections::IntersectionResult intersectionInfo) override;

        virtual bool isInShadow(intersections::IntersectionResult intersectionInfo, primitives::geometry& geometry) override;
		
void setAttenuation(float constAtten, float linearAtten, float quadAtten)
		{
			this->constAtten = constAtten;
			this->linearAtten = linearAtten;
			this->quadAtten = quadAtten;
		}
    private:
        float constAtten;
        float linearAtten;
        float quadAtten;
    };

}

