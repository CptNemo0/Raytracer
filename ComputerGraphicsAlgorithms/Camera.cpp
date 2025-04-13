#include "Camera.h"

void Camera::SetPosition(const math::vec3& target)
{
	position_ = target;
}

math::mat4x4 Camera::UpdateViewMatrix()
{
    view_matrix_ = math::mat4x4
    (
		right_.get(0), up_.get(0), forward_.get(0), position_.get(0),
		right_.get(1), up_.get(1), forward_.get(1), position_.get(1),
		right_.get(2), up_.get(2), forward_.get(2), position_.get(2),
		         0.0f,       0.0f,            0.0f,             1.0f
    );
    return view_matrix_;
}

void Camera::LookAt(const math::vec3& target, const math::vec3& up)
{
	forward_ = math::normalized(target - position_);
	right_ = math::normalized(math::cross(up, forward_));
	up_ = math::normalized(math::cross(forward_, right_));
}
