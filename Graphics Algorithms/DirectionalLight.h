#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.h"


class DirectionalLight : public Light
{
public:
    math::vec3 direction; // kierunek œwiat³a w uk³adzie œwiata

    DirectionalLight(const math::vec3& dir, const math::vec3& ambient, const math::vec3& diffuse, const math::vec3& specular, float shininess)
        : Light(ambient, diffuse, specular, shininess), direction(math::normalized(dir))
    {
    }

    math::vec3 calculate(const Fragment& fragment) const override
    {
        math::vec3 N = math::normalized(fragment.normal);
        math::vec3 V = math::normalized(-fragment.position); // wektor widoku

        math::vec3 L = math::normalized(-direction); // wektor œwiat³a
        math::vec3 R = math::reflect(-L, N);

        float diff = std::max(math::dot(N, L), 0.0f);
        float spec = pow(std::max(math::dot(R, V), 0.0f), shininess);

        return ambient + diffuse * diff + specular * spec;
    }
};

#endif // !DIRECTIONALLIGHT_H




