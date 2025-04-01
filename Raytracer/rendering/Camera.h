#ifndef RENDERING_CAMERA_H
#define RENDERING_CAMERA_H

#include "raytracer_math.h"
#include "../intersections/Ray.h"

namespace rendering
{
	class Camera
	{
	public:
		math::vec3 position_   = math::vec3(0.0f, 0.0f, 0.0f);
		math::vec3 forward_    = math::vec3(0.0f, 0.0f, 1.0f);
		math::vec3 up_         = math::vec3(0.0f, 1.0f, 0.0f);
		math::vec3 right_      = math::vec3(1.0f, 0.0f, 0.0f);
		math::vec3 look_point_ = math::vec3(0.0f, 0.0f, 1.0f);
		float aspect_ratio_ = 16.0f / 9.0f;
		float scale_ = 2.0f;

		virtual std::pair<const float, const float> GetDimensions([[maybe_unused]] const std::uint32_t width = 0.0f, [[maybe_unused]] const std::uint32_t  height = 0.0f) const = 0;
		virtual intersections::Ray GetRay(const float x, const float y) const = 0;
		virtual math::vec3 GetPixelPosition(const float x, const float y) const = 0;

	protected:
		Camera() = default;

		Camera(const math::vec3& position, const math::vec3& forward, const math::vec3& up, const math::vec3& right, const math::vec3& look_point, float aspect_ratio, float scale)
			: position_(position), forward_(forward), up_(up), right_(right), look_point_(look_point), aspect_ratio_(aspect_ratio), scale_(scale)
		{
		}
	};

	class PerspectiveCamera : public Camera
	{
	public:
		float fov_ = math::pid4;

		PerspectiveCamera(const math::vec3& position, const math::vec3& forward, const math::vec3& up, const math::vec3& right, const math::vec3& look_point, float aspect_ratio, float fov, float scale)
			: Camera(position, forward, up, right, look_point, aspect_ratio, scale), fov_(fov){ }

		PerspectiveCamera() = default;

		std::pair<const float, const float> GetDimensions([[maybe_unused]] const std::uint32_t  width = 0.0f, [[maybe_unused]] const std::uint32_t  height = 0.0f) const override;
		intersections::Ray GetRay(const float x, const float y) const override;
		math::vec3 GetPixelPosition(const float x, const float y) const override;
	};

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(const math::vec3& position, const math::vec3& forward, const math::vec3& up, const math::vec3& right, const math::vec3& look_point, float aspect_ratio, float scale)
			: Camera(position, forward, up, right, look_point, aspect_ratio, scale) {
		}

		OrthographicCamera() = default;

		std::pair<const float, const float> GetDimensions([[maybe_unused]] const std::uint32_t  width = 0.0f, [[maybe_unused]] const std::uint32_t  height = 0.0f) const override;
		intersections::Ray GetRay(const float x, const float y) const override;
		math::vec3 GetPixelPosition(const float x, const float y) const override;
	};
}

#endif // !RENDERING_CAMERA_H