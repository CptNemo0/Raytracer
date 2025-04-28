#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

class PointLight : public Light
{
public:
    PointLight(const math::vec3& position, const math::vec3& ambient, const math::vec3& diffuse, const math::vec3& specular, float shininess, float constant, float linear, float quadratic)
        : Light(position, ambient, diffuse, specular, shininess), constant_(constant), linear_(linear), quadratic_(quadratic) {}

    math::vec3 calculate(const Vertex& fragment, VertexProcessor& vertexProcessor) const override
    {
		math::vec3 lightDir = position - fragment.position;
		float distance = math::length(lightDir);
		lightDir = math::normalized(lightDir);
		// Calculate attenuation
		float attenuation = 1.0f / (constant_ + linear_ * distance + quadratic_ * distance * distance);
		// Calculate the final color
		math::vec3 ambientColor = ambient * attenuation;
		math::vec3 diffuseColor = diffuse * std::max(0.0f, math::dot(fragment.normal, lightDir)) * attenuation;
		math::vec3 specularColor = specular * std::pow(std::max(0.0f, math::dot(fragment.viewDir, lightDir)), shininess) * attenuation;
		return ambientColor + diffuseColor + specularColor;
    };

private:
    float constant_;
    float linear_;
    float quadratic_;
};

#endif // POINTLIGHT_H
