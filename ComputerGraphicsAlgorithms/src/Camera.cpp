#include "Camera.h"

namespace rtr
{
	void Camera::SetPosition(const math::vec3& target)
	{
		position_ = target;
	}

	math::mat4x4 Camera::UpdateViewMatrix()
	{
		//view_matrix_ = math::mat4x4
		//(
		//	right_.get(0), up_.get(0), -forward_.get(0), 0.0f,
		//	right_.get(1), up_.get(1), -forward_.get(1), 0.0f,
		//	right_.get(2), up_.get(2), -forward_.get(2), 0.0f,
		//	-position_.get(0), -position_.get(1), position_.get(2), 1.0f
		//);

		view_matrix_ = math::mat4x4(
			   right_.get(0),    right_.get(1),    right_.get(2), 0.0f,
			      up_.get(0),       up_.get(1),       up_.get(2), 0.0f,
			-forward_.get(0), -forward_.get(1), -forward_.get(2), 0.0f,
						0.0f,			  0.0f,			    0.0f, 1.0f
		);

		auto trans = math::translation_matrix(-position_.get(0), -position_.get(1), -position_.get(2));
		view_matrix_ = math::matmul(view_matrix_, trans);
		return view_matrix_;
	}

	void Camera::LookAt(const math::vec3& target, const math::vec3& up)
	{
		forward_ = math::normalized(target - position_);
		right_ = math::cross(forward_, up);
		up_ = math::normalized(math::cross(right_, forward_));
	}
}