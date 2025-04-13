#ifndef RENDERING_MATERIAL_H
#define RENDERING_MATERIAL_H

#include "raytracer_math.h"
#include "PixelBuffer.h"
#include "MaterialType.h"

namespace rendering
{
	class Material
	{
	public:
		MaterialType material_type_ = MaterialType::DIFFUSE;
		
		color4f ambient_ = color4f(0.0f, 0.0f, 0.0f, 255.0f);
		color4f diffuse_ = color4f(0.0f, 0.0f, 0.0f, 255.0f);
		color4f specular_ = color4f(0.0f, 0.0f, 0.0f, 255.0f);

		float shininess_ = 1.0f;

		float reflect_fraction_ = 1.0f;
		float refraction_index_ = 1.0f;
       

        Material(const color4& ambient_, 
				 const color4& diffuse_, 
				 const color4f& specular_, 
				 float shininess_,
				 MaterialType type) : ambient_(ambient_), diffuse_(diffuse_), specular_(specular_), shininess_(shininess_), material_type_(type) {}

		Material(const color4 ambient_) : ambient_(ambient_), diffuse_(color4f(0.0f, 0.0f, 0.0f, 255.0f)), specular_(color4f(0.0f, 0.0f, 0.0f, 255.0f)), shininess_(0.0f) {}

        Material() : ambient_(0.0f, 0.0f, 0.0f, 255.0f), diffuse_(0.0f, 0.0f, 0.0f, 255.0f), specular_(0.0f, 0.0f, 0.0f, 255.0f), shininess_(0.0f) {}

		explicit Material(const Material& other);

        Material& operator=(const Material& other);

		Material(Material&& other) = delete;
		Material& operator=(Material&& other) = delete;

        ~Material() {}
	};
}

#endif // !RENDERING_MATERIAL_H