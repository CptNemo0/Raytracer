#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.h"


class DirectionalLight : public Light
{
public:
	DirectionalLight(const math::vec3& direction, const math::vec3& ambient, const math::vec3& diffuse, const math::vec3& specular, float shininess)
		: Light(direction, ambient, diffuse, specular, shininess), direction_(direction) {
	}
	math::vec3 calculate(const Vertex& fragment, VertexProcessor& vertexProcessor) const override
	{
		// Normalize the direction vector
		math::vec3 lightDir = -math::normalized(direction_);
		// Calculate the final color
		math::vec3 ambientColor = ambient;
		math::vec3 diffuseColor = diffuse * std::max(0.0f, math::dot(fragment.normal, lightDir));
		math::vec3 specularColor = specular * std::pow(std::max(0.0f, math::dot(fragment.viewDir, lightDir)), shininess);
		return ambientColor + diffuseColor + specularColor;
	}

private:
	math::vec3 direction_;



};

#endif // !DIRECTIONALLIGHT_H




