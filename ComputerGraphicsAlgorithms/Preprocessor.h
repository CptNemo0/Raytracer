#ifndef PREPROCESSOR
#define PREPROCESSOR

#include "raytracer_math.h"
#include "Triangle.h"

class Preprocessor
{
private:
	float width_;
	float height_;

public:
	Preprocessor(float width, float height) : width_(width), height_(height) {}

	math::mat4x4 model_matrix_		= math::mat4x4(1.0f, true);
	math::mat4x4 view_matrix_       = math::mat4x4(1.0f, true);;
	math::mat4x4 projection_matrix_ = math::mat4x4(1.0f, true);;

	math::vec3 Local2World(const math::vec3& position) const;
	math::vec3 World2View(const math::vec3& position) const;
	math::vec3 View2Screen(const math::vec3& position) const;
	math::vec3 Local2Sceen(const math::vec3& position) const;

	void TriangleLocal2Screen(Triangle& triangle) const;
};


#endif // !PREPROCESSOR