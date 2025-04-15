#ifndef RESTERIZER_H
#define RESTERIZER_H

#include "Triangle.h"
#include "ColorBuffer.h"


class Rasterizer
{
public:
	Rasterizer(buffer::ColorBuffer& buffer) : buffer_(buffer) {};

	void addTriangle(const Triangle& triangle)
	{

		triangles_ = std::make_shared<Triangle>(triangle);
	};

	void addProjectionMatrix(const math::mat4x4& projectionMatrix)
	{
		projectionMatrix_ = projectionMatrix;
	};

	void rasterize()
	{
		if (triangles_) {
			triangles_->ToScreenCoordinates(buffer_.width_, buffer_.height_);
			triangles_->drawTriangle(buffer_);
		}
	};

	void rasterize(Triangle& triangle)
	{
		triangle.ApplyProjection(projectionMatrix_);
		triangle.ToScreenCoordinates(buffer_.width_, buffer_.height_);
		triangle.drawTriangle(buffer_);
	};

	void ToScreenCoordinates(Triangle& triangle)
	{
		triangle.ToScreenCoordinates(buffer_.width_, buffer_.height_);
	}

	math::mat4x4 projection_matrix(float fov, float aspect, float near, float far)
	{
		const float a = 1.0f / (aspect * std::tan(fov * 0.5f));
		const float b = 1.0f / std::tan(fov * 0.5f);
		const float c = (far + near) / (near - far);
		const float d = (2.0f * far * near) / (near - far);

		return math::mat4x4(
			a, 0.0f, 0.0f, 0.0f,
			0.0f, b, 0.0f, 0.0f,
			0.0f, 0.0f, c, d,
			0.0f, 0.0f, -1.0f, 0.0f
		);

	}

private:
	buffer::ColorBuffer buffer_;
	math::mat4x4 projectionMatrix_;
	std::shared_ptr<Triangle> triangles_;

};



#endif // !RESTERIZER_H