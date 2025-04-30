#ifndef PREPROCESSOR
#define PREPROCESSOR

#include "raytracer_math.h"
#include "mesh/Triangle.h"
#include "aliasing.h"
#include "Texture.h"
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
		math::mat4x4 ti_model_matrix = math::mat4x4(1.0f, true);	
		math::vec3 eye_position = math::vec3(0.0f);
		color4f background_color_ = color4f(0.0f, 0.0f, 0.0f, 255.0f);
		color4f color_ = color4f(0.0f, 0.0f, 0.0f, 255.0f);
		Texture default_texture_ = Texture();
		Texture* texture_;

		void Local2World(math::vec3& position_) const;
		void World2View(math::vec3& position_) const;
		void View2Screen(math::vec3& position_) const;
		void Local2Screen(math::vec3& position_) const;

		void TriangleLocal2World(mesh::Triangle& triangle) const;

		void TriangleWorld2View(mesh::Triangle& triangle) const;

		void TriangleView2Screen(mesh::Triangle& triangle) const;

		void TriangleLocal2Screen(mesh::Triangle& triangle) const;
		math::vec3 FixNormal(const math::vec3& normal) const;

		color3f SampleTexture(const math::vec2& uv) const;
	};
}




#endif // !PREPROCESSOR