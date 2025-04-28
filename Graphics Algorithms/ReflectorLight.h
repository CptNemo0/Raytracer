#ifndef REFLECTORLIGHT_H
#define REFLECTORLIGHT_H

#include "Light.h"
class ReflectorLight : public Light
{
public:
    math::vec3 position;
    math::vec3 direction;
    float cutoff; // k¹t sto¿ka reflektora (cosinus k¹ta)

    ReflectorLight(const math::vec3& pos, const math::vec3& dir, float cutoffAngle, const math::vec3& ambient, const math::vec3& diffuse, const math::vec3& specular, float shininess)
        : Light(ambient, diffuse, specular, shininess), position(pos), direction(math::normalized(dir)), cutoff(cosf(cutoffAngle))
    {
    }

    math::vec3 calculate(const Fragment& fragment, const math::vec3& eyePosition, bool useBlinn = true) const override
    {
        math::vec3 N = math::normalized(fragment.normal);
        math::vec3 V = math::normalized(eyePosition - fragment.position);
        math::vec3 L = math::normalized(position - fragment.position);

        float theta = math::dot(math::normalized(-L), direction);

        if (theta > cutoff) {
            float diff = std::max(math::dot(N, L), 0.0f);

            float spec = 0.0f;
            if (diff > 0.0f) {
                if (useBlinn) {
                    math::vec3 H = math::normalized(L + V);
                    spec = pow(std::max(math::dot(N, H), 0.0f), shininess);
                }
                /*else {
                    math::vec3 R = math::reflect(-L, N);
                    spec = pow(std::max(math::dot(R, V), 0.0f), shininess);
                }*/
            }

            return ambient + diffuse * diff + specular * spec;
        }
        else {
            return ambient;
        }
    }
}
#endif // !REFLECTORLIGHT_H




;

