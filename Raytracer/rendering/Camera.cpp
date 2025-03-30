#include "Camera.h"

std::pair<const float, const float> rendering::Camera::GetDimensions() const
{
	const float H = 2.0f * tanf(fov_ * 0.5f) * scale_;
	const float W = aspect_ratio_ * H;
	return std::make_pair(W, H);
}

math::vec3 rendering::Camera::GetPixelPosition(const float x, const float y) const
{
	math::vec3 return_value = position_;

	return_value += right_ * x;
	return_value += up_ * y;
	return_value += forward_ * scale_;

	return return_value;
}
