#include "pch.h"

#include "raytracer_math.h"

using namespace math;

TEST(vec_test, equality_operator)
{
	vec3 a (1, 2, 3);
	vec3 b (1, 2, 3);
	vec3 c (2, 5, 4);
	ASSERT_TRUE(a == b);
	ASSERT_TRUE(a != c);
}

TEST(vec_test, addition) 
{
	vec3 a(1.0f, 1.0f, 1.0f);
	vec3 b(2.0f, 2.0f, 2.0f);
	vec3 c(3.0f, 3.0f, 3.0f);
	vec3 result1 = a + b;
	vec3 result2 = b + a;

	ASSERT_TRUE(result1 == c);
	ASSERT_TRUE(result2 == c);
}

TEST(vec_test, add_eq)
{
	vec3 a(1.0f, 1.0f, 1.0f);
	vec3 b(1.0f, 1.0f, 1.0f);
	vec3 c(2.0f, 2.0f, 2.0f);
	a += b;

	ASSERT_TRUE(a == c);
}

TEST(vec_test, subtraction)
{
	vec3 a(1.0f, 1.0f, 1.0f);
	vec3 b(1.0f, 1.0f, 1.0f);
	vec3 c(0.0f, 0.0f, 0.0f);
	vec3 result = a - b;

	ASSERT_TRUE(result == c);
}

TEST(vec_test, sub_eq)
{
	vec3 a(1.0f, 1.0f, 1.0f);
	vec3 b(1.0f, 1.0f, 1.0f);
	vec3 c(0.0f, 0.0f, 0.0f);
	a -= b;

	ASSERT_TRUE(a == c);
}

TEST(vec_test, multiplication)
{
	vec3 a(1.0f, 1.0f, 1.0f);
	float b = 5.0f;
	vec3 c(5.0f, 5.0f, 5.0f);
	auto result = a * b;
	ASSERT_TRUE(result == c);
}

TEST(vec_test, mul_eq)
{
	vec3 a(1.0f, 1.0f, 1.0f);
	float b = 5.0f;
	vec3 c(5.0f, 5.0f, 5.0f);
	a *= b;
	ASSERT_TRUE(a == c);
}

TEST(vec_test, division)
{
	vec3 a(1.0f, 1.0f, 1.0f);
	float b = 5.0f;
	vec3 c(0.2f, 0.2f, 0.2f);
	auto result = a / b;
	ASSERT_TRUE(result == c);
}

TEST(vec_test, div_eq)
{
	vec3 a(1.0f, 1.0f, 1.0f);
	float b = 5.0f;
	vec3 c(0.2f, 0.2f, 0.2f);
	a /= b;
	ASSERT_TRUE(a == c);
}