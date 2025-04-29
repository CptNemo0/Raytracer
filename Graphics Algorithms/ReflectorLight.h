#ifndef REFLECTORLIGHT_H
#define REFLECTORLIGHT_H

#include "Light.h"

class ReflectorLight : public Light
{
public:
    math::vec3 position;
    math::vec3 direction;
    float cutoff;
	float outerCutoff;

    ReflectorLight(
        const math::vec3& pos,
        const math::vec3& dir,
        float cutoffAngleDeg,
		float outerCutoffAngleDeg,
        const math::vec3& ambient,
        const math::vec3& diffuse,
        const math::vec3& specular,
        float shininess)
        : Light(ambient, diffuse, specular, shininess),
        position(pos),
        direction(math::normalized(dir))
    {
        cutoff = std::cos(math::to_radians(cutoffAngleDeg));
        outerCutoff = std::cos(math::to_radians(outerCutoffAngleDeg));
    }

    math::vec3 calculate(const Fragment& fragment, const math::vec3& eyePosition, bool useBlinn = true) const override
    {
        math::vec3 N = math::normalized(fragment.normal);
        math::vec3 L = math::normalized(position - fragment.position);

        float theta = math::dot(direction, L); 

        if (theta > outerCutoff)
        {
            float epsilon = cutoff - outerCutoff;
            float intensity = std::clamp((theta - outerCutoff) / epsilon, 0.0f, 1.0f);

            float diff = std::max(math::dot(L, N), 0.0f);

            float spec = 0.0f;
            if (diff > 0.0f)
            {
                math::vec3 V = math::normalized(eyePosition - fragment.position);
                math::vec3 H = math::normalized(L + V);
                spec = std::pow(std::max(math::dot(N, H), 0.0f), shininess);
            }

            math::vec3 ambientComp = ambient;
            math::vec3 diffuseComp = diffuse * diff;
            math::vec3 specularComp = specular * spec;

            return (ambientComp + diffuseComp + specularComp) * intensity;
        }

        return ambient;  // poza zakresem sto¿ka
    }
};
#endif // !REFLECTORLIGHT_H
