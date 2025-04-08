#pragma once
#include "../lights/Light.h"

namespace lights
{
    class PointLight : public Light
    {
    public:
        PointLight(const math::vec3& position, const rendering::color4f& color, float intensity)
        {
            this->position = position;
            this->color = color;
            this->intensity = intensity;
        }

        virtual bool IsInShadow(intersections::IntersectionResult intersectionInfo, primitives::geometry& geometry) override;
		
        void setAttenuation(float constAtten, float linearAtten, float quadAtten)
		{
			this->constAtten = constAtten;
			this->linearAtten = linearAtten;
			this->quadAtten = quadAtten;
		}

        float constAtten;
        float linearAtten;
        float quadAtten;
    };

}

