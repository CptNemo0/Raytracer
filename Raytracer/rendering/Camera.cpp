#include "Camera.h"

math::vec3 rendering::PerspectiveCamera::GetPixelPosition(const float x, const float y) const
{
	math::vec3 return_value = position_;

	return_value += right_ * x;
	return_value += up_ * y;
	return_value += forward_ * scale_;

	return return_value;
}

std::pair<const float, const float> rendering::PerspectiveCamera::GetDimensions([[maybe_unused]] const std::uint32_t  width, [[maybe_unused]] const std::uint32_t  height) const
{
	const float H = 2.0f * tanf(fov_ * 0.5f) * scale_;
	const float W = aspect_ratio_ * H;
	return std::make_pair(W, H);
}

intersections::Ray rendering::PerspectiveCamera::GetRay(const float x, const float y) const
{
	math::vec3 pixel_position = GetPixelPosition(x, y);
	math::vec3 ray_dir = (pixel_position - position_);
	return intersections::Ray(position_, ray_dir);
}

math::vec3 rendering::OrthographicCamera::GetPixelPosition(const float x, const float y) const
{
	math::vec3 return_value = position_;

	return_value += right_ * x;
	return_value += up_ * y;

	return return_value;
}

std::pair<const float, const float> rendering::OrthographicCamera::GetDimensions([[maybe_unused]] const std::uint32_t  width, [[maybe_unused]] const std::uint32_t  height) const
{
	return { scale_ * static_cast<float>(width), scale_ * static_cast<float>(height)};
}

intersections::Ray rendering::OrthographicCamera::GetRay(const float x, const float y) const
{
	math::vec3 pixel_position = GetPixelPosition(x, y);
	return intersections::Ray(pixel_position, forward_);
}

