#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

class PointLight : public Light
{
public:
    math::vec3 position;

    float constantAttenuation; 
    float linearAttenuation;
    float quadraticAttenuation;

    PointLight(const math::vec3& pos, const math::vec3& ambient, const math::vec3& diffuse, const math::vec3& specular, float shininess,
        float constant = 1.0f, float linear = 0.09f, float quadratic = 0.0032f, float intensitivity = 1)
        : Light(ambient, diffuse, specular, shininess, intensitivity), position(pos),
        constantAttenuation(constant), linearAttenuation(linear), quadraticAttenuation(quadratic)
    {
    }

    math::vec3 calculate(const Fragment& fragment, const math::vec3& eyePosition, bool useBlinn = true) const override
    {
        math::vec3 lightDir = position - fragment.position;
        math::vec3 N = math::normalized(fragment.normal);
        math::vec3 L = math::normalized(lightDir);

        float distance = math::length(lightDir);
        float attenuation = 1.0f / std::max(constantAttenuation + linearAttenuation * distance + quadraticAttenuation * (distance * distance), 0.0001f);

        float diff = std::max(math::dot(L, N), 0.0f);

        float spec = 0.0f;
        if (diff > 0.0f)
        {
            math::vec3 V = math::normalized(eyePosition - fragment.position);
            math::vec3 H = math::normalized(L + V);

            spec = pow(std::max(math::dot(N, H), 0.0f), shininess);
			return ambient + (diffuse * diff + specular * spec) * attenuation *  intensitivity;
        }
        else
        {
            return ambient;
        }
    }
};

#endif // POINTLIGHT_H
