#include "DirectionalLight.h"

namespace rtr
{
	const color3f DirectionalLight::CalculateColor(const math::vec3& position, const math::vec3& normal, const math::vec3& view_position) const
	{
		
		const auto dot_product = math::dot(direction_, normal);
		if (dot_product > 0.0f)
		{
			const auto view_direction = math::normalized(view_position - position);
			const auto halfway_vector = math::normalized(direction_ + view_direction);

			float spec = std::pow(std::max(math::dot(normal, halfway_vector), 0.0f), 40.0f);

			color3f diffuse_color = color_ * dot_product;
			color3f specular_color = color_ * spec;
			color3f final_color = diffuse_color + specular_color;
			return final_color;
		}
		else
		{
			return color3f(10.0f, 10.0f, 10.0f);
		}
	}
}