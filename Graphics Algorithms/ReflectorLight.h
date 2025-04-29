#ifndef REFLECTORLIGHT_H
#define REFLECTORLIGHT_H

#include "Light.h"

class ReflectorLight : public Light
{
public:
    math::vec3 position;
    math::vec3 direction;
    float cutoff; // cosinus k¹ta odciêcia

    ReflectorLight(
        const math::vec3& pos,
        const math::vec3& dir,
        float cutoffAngleRadians,
        const math::vec3& ambient,
        const math::vec3& diffuse,
        const math::vec3& specular,
        float shininess)
        : Light(ambient, diffuse, specular, shininess),
        position(pos),
        direction(math::normalized(dir)),
        cutoff(cosf(cutoffAngleRadians)) {
    }

    math::vec3 calculate(const Fragment& fragment, const math::vec3& eyePosition, bool useBlinn = true) const override
    {
        math::vec3 N = math::normalized(fragment.normal);
        math::vec3 L = math::normalized(position - fragment.position);

        float theta = math::dot(math::normalized(-direction), L);  // -direction = œwiat³o padaj¹ce na obiekt

        if (theta >= cutoff) 
        {
            float diff = std::max(math::dot(N, L), 0.0f);

            float spec = 0.0f;
            if (diff > 0.0f)
            {
                math::vec3 V = math::normalized(eyePosition - fragment.position);
                math::vec3 H = math::normalized(L + V);
                spec = powf(std::max(math::dot(N, H), 0.0f), shininess);
            }

            return ambient + diffuse * diff + specular * spec;
        }

        return ambient;
    }
};
#endif // !REFLECTORLIGHT_H
