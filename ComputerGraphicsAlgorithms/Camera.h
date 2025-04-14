#ifndef CAMERA_H
#define CAMERA_H

#include "raytracer_math.h"

class Camera
{
private:
	math::vec3 position_ = math::vec3(0.0f, 0.0f, 0.0f);
	math::vec3 forward_ = math::vec3(0.0f, 0.0f, 1.0f);
	math::vec3 up_ = math::vec3(0.0f, 1.0f, 0.0f);
	math::vec3 right_ = math::vec3(1.0f, 0.0f, 0.0f);

	math::mat4x4 view_matrix_;
	math::mat4x4 projection_matrix_;

	float aspect_ratio_;
	float far_;
	float near_;
	float fov_;

public:
	
	Camera() = default;
	Camera(const math::vec3& position, 
		   const math::vec3& target, 
		   const math::vec3& up,
		   float aspect_ratio,
		   float fov,
		   float far,
		   float near)
		: position_(position), aspect_ratio_(aspect_ratio), fov_(fov), near_(near), far_(far)
	{
		LookAt(target, up);
	}

	void SetPosition(const math::vec3& target);
	math::mat4x4 UpdateViewMatrix();
	void LookAt(const math::vec3& target, const math::vec3& up = math::vec3(0.0f, 1.0f, 0.0f));

	inline math::mat4x4 ProjectionMatrix()
	{
		return math::projection_matrix(fov_, aspect_ratio_, near_, far_);
	}

	inline math::vec3 position() const
	{
		return position_;
	}
};

#endif // !CAMERA_H