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

public:
	
	Camera() = default;
	Camera(const math::vec3& position, const math::vec3& target, const math::vec3& up)
		: position_(position)
	{
		LookAt(target, up);
	}

	void SetPosition(const math::vec3& target);
	math::mat4x4 UpdateViewMatrix();
	void LookAt(const math::vec3& target, const math::vec3& up = math::vec3(0.0f, 1.0f, 0.0f));

	inline math::vec3 position() const
	{
		return position_;
	}
};

#endif // !CAMERA_H