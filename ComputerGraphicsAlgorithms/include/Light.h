#ifndef LIGHT_H
#define LIGHT_H

#include <functional>
#include "aliasing.h"
#include "raytracer_math.h"

namespace rtr
{
	class Light
	{
	protected:
		float intensity_ = 1.0f;
		rtr::color3f color_ = color3f(255.0f, 255.0f, 255.0f);
		std::function<float(float)> attenuation_function = [](float d) {return d; };

		Light(const float intensity, const rtr::color3f& color, std::function<float(float)> function) : intensity_(intensity), color_(color), attenuation_function(function) {}

	public:
		Light() = default;
		Light(Light&& other) noexcept
		{
			intensity_ = other.intensity_;
			color_ = other.color_;
			attenuation_function = std::move(other.attenuation_function);
		}

		void operator =(Light&& other) noexcept
		{
			intensity_ = other.intensity_;
			color_ = other.color_;
			attenuation_function = std::move(other.attenuation_function);
		}

		Light(const Light&) = delete;
		Light& operator =(const Light&) = delete;

		virtual const color3f CalculateColor(const math::vec3& position, const math::vec3& normal, const math::vec3& view_position) const = 0;
	};
}

#endif // !LIGHT_H