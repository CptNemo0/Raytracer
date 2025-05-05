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
        /*math::vec3 L = math::normalized(-direction);


        float diff =math::dot(L, N);

        float spec = 0.0f;
        if (diff > 0.0f) {
            math::vec3 V = math::normalized(eyePosition - fragment.position);
            math::vec3 H = math::normalized(L + V);
            spec = pow(std::max(math::dot(N, H), 0.0f), shininess);
           
            return ambient + diffuse * diff + specular * spec;
        }
        else
        {
            return ambient;
        }*/

        const auto dot_product = math::dot(direction, fragment.normal);
        if (dot_product > 0.0f)
        {
            const auto view_direction = math::normalized(eyePosition - fragment.position);
            const auto halfway_vector = math::normalized(direction + view_direction);

            float spec = std::pow(std::max(math::dot(fragment.normal, halfway_vector), 0.0f), shininess);

            math::vec3 diffuse_color = diffuse * dot_product;
            math::vec3 specular_color = specular * spec;
            math::vec3 final_color = ambient+  diffuse_color + specular_color;
            return final_color;
        }
        else
        {
            return ambient;
        }
    }
};

#endif // !DIRECTIONALLIGHT_H




