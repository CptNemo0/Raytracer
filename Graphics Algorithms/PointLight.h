#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

class PointLight : public Light
{
public:
    math::vec3 position; // pozycja œwiat³a

    float constantAttenuation;  // Sta³a os³abienia
    float linearAttenuation;    // Liniowa os³abienia
    float quadraticAttenuation; // Kwadratowa os³abienia

    PointLight(const math::vec3& pos, const math::vec3& ambient, const math::vec3& diffuse, const math::vec3& specular, float shininess,
        float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f)
        : Light(ambient, diffuse, specular, shininess), position(pos),
        constantAttenuation(constant), linearAttenuation(linear), quadraticAttenuation(quadratic)
    {
    }

    math::vec3 calculate(const Fragment& fragment, const math::vec3& eyePosition, bool useBlinn = true) const override
    {
        math::vec3 N = math::normalized(fragment.normal);
        math::vec3 L = math::normalized(position - fragment.position);

        float distance = math::length(position - fragment.position);
        float attenuation = 1.0f / (constantAttenuation + linearAttenuation * distance + quadraticAttenuation * (distance * distance));

        float diff = std::max(math::dot(L, N), 0.0f);

        float spec = 0.0f;
        if (diff > 0.0f)
        {
            math::vec3 V = math::normalized(eyePosition - fragment.position);
            math::vec3 H = math::normalized(L + V);

            spec = pow(std::max(math::dot(N, H), 0.0f), shininess);
        }

        return (ambient + diffuse * diff + specular * spec) * attenuation;
    }
};

#endif // POINTLIGHT_H
