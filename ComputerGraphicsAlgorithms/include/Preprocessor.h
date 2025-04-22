#ifndef PREPROCESSOR
#define PREPROCESSOR

#include "raytracer_math.h"
#include "mesh/Triangle.h"
#include "aliasing.h"

namespace rtr
{
	class Preprocessor
	{
	private:
		float width_;
		float height_;

	public:
		Preprocessor(const float width, const float height) : width_(width), height_(height) {}

		math::mat4x4 model_matrix_ = math::mat4x4(1.0f, true);
		math::mat4x4 view_matrix_ = math::mat4x4(1.0f, true);;
		math::mat4x4 projection_matrix_ = math::mat4x4(1.0f, true);;

		color4f background_color_ = color4f(0.0f, 0.0f, 0.0f, 255.0f);
		color4f color_ = color4f(0.0f, 0.0f, 0.0f, 255.0f);

		void Local2World(math::vec3& position_) const;
		void World2View(math::vec3& position_) const;
		void View2Screen(math::vec3& position_) const;
		void Local2Screen(math::vec3& position_) const;

		void TriangleLocal2Screen(mesh::Triangle& triangle) const;
	};
}




#endif // !PREPROCESSOR