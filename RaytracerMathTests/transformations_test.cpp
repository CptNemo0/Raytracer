#include "pch.h"

#include "raytracer_math.h"

#include <iostream>

using namespace math;

TEST(transformations_test, mat_rotation_test)
{
	vec4 a(1.0f, 0.0f, 0.0f, 1.0f);
	rotate_deg(vec3(0.0f, 90.0f, 0.0f), a);
	vec4 b(0.0f, 0.0f, 1.0f, 1.0f);
	ASSERT_TRUE(a == b);
}

TEST(transformations_test, quat_rotation_test)
{
	vec3 a(3.0f, 1.0f, 3.0f);
	vec3 axis(1.0f, 0.0f, 1.0f);
	vec3 result = quat_rotate_deg(a, 45.0f, axis);
	vec3 c(2.5f, sqrtf(2.0f) / 2.0f, 3.5f);
	std::cout << "quat_rotation_test: " << result << std::endl;
}