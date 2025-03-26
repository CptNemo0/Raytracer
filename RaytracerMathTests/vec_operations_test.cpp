#include "pch.h"

#include "raytracer_math.h"

using namespace math;

TEST(vec_operations_test, dot_product)
{
	vec3 a(12, 20, 10);
	vec3 b(16, -5, 5);
	auto result = dot(a, b);
	ASSERT_EQ(result, 142);
}
TEST(vec_operations_test, cross_product)
{
	vec3 a(4.0f, 5.0f, 1.0f);
	vec3 b(4.0f, 1.0f, 3.0f);
	auto result = cross(a, b);
	vec3 c(14.0f, -8.0f, -16.0f);
	ASSERT_TRUE(result == c);
}
TEST(vec_operations_test, vec_length)
{
	vec2 a(12.0f, -5.0f);
	auto result = length(a);
	ASSERT_EQ(result, 13.0f);
}

TEST(vec_operations_test, vec_normalization)
{
	vec3 a(14.0f, -8.0f, -16.0f);
	auto len = length(a);
	auto result = normalized(a);
	vec3 c = a / len;
	ASSERT_TRUE(result == c);
	normalize(a);
	ASSERT_TRUE(a == c);
}
TEST(vec_operations_test, vec_angle_rad)
{
	vec3 a(0.0f, 3.0f, 0.0f);
	vec3 b(5.0f, 5.0f, 0.0f);
	auto result = angle_rad(a, b);
	float c = pid4;
	ASSERT_EQ(result, c);
}
TEST(vec_operations_test, vec_angle_deg)
{
	vec3 a(0.0f, 3.0f, 0.0f);
	vec3 b(5.0f, 5.0f, 0.0f);
	auto result = angle_deg(a, b);
	float c = 45.0f;
	ASSERT_EQ(result, c);
}
