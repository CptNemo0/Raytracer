#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"

namespace rtr
{
	class PointLight : public Light
	{
	private:
		math::vec3 position_;

	public:
		PointLight(const math::vec3& position_, float intensity, color3f color, std::function<float(float)> function) : position_(position_), Light(intensity, color, function) {}
		const color3f CalculateColor(const math::vec3& position, const math::vec3& normal, const math::vec3& view_position) const override;

		PointLight(PointLight&& other) noexcept
		{
			intensity_ = other.intensity_;
			color_ = other.color_;
			attenuation_function = std::move(other.attenuation_function);
			position_ = other.position_;
		}

		void operator =(PointLight&& other) noexcept
		{
			intensity_ = other.intensity_;
			color_ = other.color_;
			attenuation_function = std::move(other.attenuation_function);
			position_ = other.position_;
		}

		PointLight(const PointLight&) = delete;
		PointLight& operator =(const PointLight&) = delete;
	};
}

#endif  POINT_LIGHT_H

