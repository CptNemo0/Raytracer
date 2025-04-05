#ifndef RENDERING_MATERIAL_H
#define RENDERING_MATERIAL_H

#include "raytracer_math.h"
#include "PixelBuffer.h"

namespace rendering
{
	class Material
	{
	public:
		color4f ambient;
		color4f diffuse;
		color4f specular;
		float shininess;

        Material(const color4& ambient, const color4& diffuse, const color4f& specular, float shininess)
            : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {
        }

		Material(const color4 ambient) : ambient(ambient), diffuse(color4f(0.0f, 0.0f, 0.0f, 255.0f)),
			specular(color4f(0.0f, 0.0f, 0.0f, 255.0f)), shininess(0.0f) {}

        Material()
            : ambient(0.0f, 0.0f, 0.0f, 255.0f), diffuse(0.0f, 0.0f, 0.0f, 255.0f), specular(0.0f, 0.0f, 0.0f, 255.0f), shininess(0.0f) {
        }

        ~Material() {}

        Material& operator=(const Material& other)
        {
            if (this == &other)
                return *this;

            ambient = other.ambient;
            diffuse = other.diffuse;
            specular = other.specular;
            shininess = other.shininess;

            return *this;
        }
	};
}

#endif // !RENDERING_MATERIAL_H