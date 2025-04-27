#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Light.h"
#include "raytracer_math.h"

namespace rtr
{
	class DirectionalLight : public Light
	{
	private:
		math::vec3 direction_;
	public:
		DirectionalLight(const math::vec3& direction_, float intensity, color3f color, std::function<float(float)> function)
			: direction_(math::normalized(direction_)), Light(intensity, color, function) {
		}

		const color3f CalculateColor(const math::vec3& position, const math::vec3& normal, const math::vec3& view_position) const override;

		DirectionalLight(DirectionalLight&& other) noexcept
		{
			intensity_ = other.intensity_;
			color_ = other.color_;
			attenuation_function = std::move(other.attenuation_function);
			direction_ = other.direction_;
		}

		void operator =(DirectionalLight&& other) noexcept
		{
			intensity_ = other.intensity_;
			color_ = other.color_;
			attenuation_function = std::move(other.attenuation_function);
			direction_ = other.direction_;
		}

		DirectionalLight(const DirectionalLight&) = delete;
		DirectionalLight& operator =(const DirectionalLight&) = delete;
	};
}

#endif DIRECTIONAL_LIGHT_H

