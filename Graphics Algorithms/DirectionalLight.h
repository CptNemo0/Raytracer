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

    math::vec3 calculate(const Fragment& fragment, const math::vec3& eyePosition, bool useBlinn = true) const override
    {
        math::vec3 N = math::normalized(fragment.normal);

        float diff =math::dot(direction, N);

        float spec = 0.0f;
        if (diff > 0.0f) {
            math::vec3 V = math::normalized(eyePosition - fragment.position);
            math::vec3 H = math::normalized(direction + V);
            spec = pow(std::max(math::dot(N, H), 0.0f), shininess);
            
            /*else {
                math::vec3 R = math::reflect(-L, N);
                spec = pow(std::max(math::dot(R, V), 0.0f), shininess);
            }*/
            return ambient + diffuse * diff + specular * spec;
        }
        else
        {
            return math::vec3(0.0f, 0.0f, 0.0f);
        }

       
    }
};

#endif // !DIRECTIONALLIGHT_H




