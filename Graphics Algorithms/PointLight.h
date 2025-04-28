#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

class PointLight : public Light
{
public:
    math::vec3 position; // pozycja œwiat³a

    PointLight(const math::vec3& pos, const math::vec3& ambient, const math::vec3& diffuse, const math::vec3& specular, float shininess)
        : Light(ambient, diffuse, specular, shininess), position(pos)
    {
    }

    math::vec3 calculate(const Fragment& fragment) const override
    {
        math::vec3 N = math::normalized(fragment.normal);
        math::vec3 V = math::normalized(-fragment.position);
        math::vec3 L = math::normalized(position - fragment.position);
        math::vec3 R = math::reflect(-L, N);

        float diff = std::max(math::dot(N, L), 0.0f);
        float spec = pow(std::max(math::dot(R, V), 0.0f), shininess);

        return ambient + diffuse * diff + specular * spec;
    }
};

#endif // POINTLIGHT_H
