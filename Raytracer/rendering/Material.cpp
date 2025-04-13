#include "Material.h"

namespace rendering
{
	Material::Material(const Material& other)
	{
		ambient_ = other.ambient_;
		diffuse_ = other.diffuse_;
		specular_ = other.specular_;
		shininess_ = other.shininess_;
		reflect_fraction_ = other.reflect_fraction_;
		material_type_ = other.material_type_;
		refraction_index_ = other.refraction_index_;
	}

	Material& Material::operator=(const Material& other)
	{
		if (this == &other)
			return *this;

		ambient_ = other.ambient_;
		diffuse_ = other.diffuse_;
		specular_ = other.specular_;
		shininess_ = other.shininess_;
		reflect_fraction_ = other.reflect_fraction_;
		material_type_ = other.material_type_;
		refraction_index_ = other.refraction_index_;

		return *this;
	}
}