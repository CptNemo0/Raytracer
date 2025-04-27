#include "PointLight.h"
#include "algorithm"
#include "raytracer_math.h"

namespace rtr
{
	const color3f PointLight::CalculateColor(const math::vec3& position, const math::vec3& normal, const math::vec3& view_position) const
	{
		const auto light_direction = math::normalized(position_ - position);
		const auto dot_product = math::dot(light_direction, normal);
		if (dot_product > 0.0f)
		{
			const auto view_direction = math::normalized(view_position - position);
			const auto halfway_vector = math::normalized(light_direction + view_direction);

			float spec = std::pow(std::max(math::dot(normal, halfway_vector), 0.0f), 10.0f);

			color3f diffuse_color  = color_ * dot_product;
			color3f specular_color = color_ * spec;
			color3f final_color = diffuse_color + specular_color;
			const auto distance = math::length(position_ - position);
			const auto attenuation = attenuation_function(distance);
			final_color *= attenuation * intensity_;
			final_color[0] = std::clamp(final_color[0], 0.0f, 255.0f);
			final_color[1] = std::clamp(final_color[1], 0.0f, 255.0f);
			final_color[2] = std::clamp(final_color[2], 0.0f, 255.0f);
			return final_color;
		}
		else
		{
			return color3f(10.0f, 10.0f, 10.0f);
		}
	}
}