#ifndef CAMERA_H
#define CAMERA_H

#include "raytracer_math.h"


class Camera
{

public:
	
	Camera(const math::vec3& position, const math::vec3& forward, const math::vec3& up, float fov, float aspect, float near, float far)
		: position_(position), fov_(fov), aspect_(aspect), near_(near), far_(far)
	{
		LookAt(position_, forward_, up_);
		projectionMatrix_ = math::projection_matrix(fov_, aspect_, near_, far_);
		UpdateViewMatrix();
	}

	void SetPosition(const math::vec3& position) { position_ = position; }
	math::vec3 GetPosition() const { return position_; }

	void SetTarget(const math::vec3& target) { forward_ = target; }
	void SetUp(const math::vec3& up) { up_ = up; }
	const math::mat4x4& GetViewMatrix() const { return viewMatrix_; }
	const math::mat4x4& GetProjectionMatrix() const { return projectionMatrix_; }

	void UpdateViewMatrix()
	{
		viewMatrix_ = math::mat4x4(
			right_[0], up_[0], forward_[0], position_[0],
			right_[1], up_[1], forward_[1], position_[0],
			right_[2], up_[2], forward_[2], position_[0],
			0.0f,      0.0f,   0.0f,        1.0f
		);

	}

	void LookAt(const math::vec3& position, const math::vec3& target, const math::vec3& up)
	{
		forward_ = math::normalized(target - position);
		right_ = math::normalized(math::cross(up, forward_));
		up_ = math::normalized(math::cross(forward_, right_));
	}


private:
	math::vec3 position_ = math::vec3(0.0f, 0.0f, 0.0f);
	math::vec3 forward_ = math::vec3(0.0f, 0.0f, 1.0f);
	math::vec3 up_ = math::vec3(0.0f, 1.0f, 0.0f);
	math::vec3 right_ = math::vec3(1.0f, 0.0f, 0.0f);

	math::mat4x4 viewMatrix_;
	math::mat4x4 projectionMatrix_;

	float aspect_;
	float far_;
	float near_;
	float fov_;
};



#endif // !CAMERA_H



