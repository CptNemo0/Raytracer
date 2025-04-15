#ifndef CAMERA_H
#define CAMERA_H

#include "raytracer_math.h"


class Camera
{

public:
	
	Camera(const math::vec3& position, const math::vec3& target, const math::vec3& up, float fov, float aspect, float near, float far)
		: position_(position), target_(target), up_(up), fov_(fov), aspect_(aspect), near_(near), far_(far)
	{
		LookAt(position_, target_, up_);
		projectionMatrix_ = math::projection_matrix(fov_, aspect_, near_, far_);
	}

	void SetPosition(const math::vec3& position) { position_ = position; }
	void SetTarget(const math::vec3& target) { target_ = target; }
	void SetUp(const math::vec3& up) { up_ = up; }
	const math::mat4x4& GetViewMatrix() const { return viewMatrix_; }
	const math::mat4x4& GetProjectionMatrix() const { return projectionMatrix_; }

	void UpdateViewMatrix()
	{
		viewMatrix_ = math::mat4x4(
			right_[0], up_[0], forward_[0], 0.0f, -math::dot(right_, position_),
			right_[1], up_[1], forward_[1], 0.0f, -math::dot(up_, position_),
			right_[2], up_[2], forward_[2], 0.0f, -math::dot(forward_, position_),
			0.0f, 0.0f, 0.0f, 1.0f
		);

	}

	void LookAt(const math::vec3& position, const math::vec3& target, const math::vec3& up)
	{
		forward_ = math::normalized(target - position);
		right_ = math::normalized(math::cross(up, forward_));
		up_ = math::normalized(math::cross(forward_, right_));
	}


private:
	math::vec3 position_;
	math::vec3 forward_;
	math::vec3 up_;
	math::vec3 right_;
	math::vec3 target_;

	math::mat4x4 viewMatrix_;
	math::mat4x4 projectionMatrix_;

	float aspect_;
	float far_;
	float near_;
	float fov_;
};



#endif // !CAMERA_H



