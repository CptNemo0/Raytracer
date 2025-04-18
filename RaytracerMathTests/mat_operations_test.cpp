#include "pch.h"

#include "raytracer_math.h"

using namespace math;

TEST(mat_operations_test, matmul_test)
{
	mat3x3 a 
	{
		1.0f, 2.0f, 3.0f,
		3.0f, 2.0f, 1.0f,
		1.0f, 2.0f, 3.0f
	};

	mat3x3 b
	{
		4.0f, 5.0f, 6.0f,
		6.0f, 5.0f, 4.0f,
		4.0f, 6.0f, 5.0f
	};

	auto result1 = matmul(a, b);
	auto result2 = matmul(b, a);

	mat3x3 c
	{ 
		28.0f, 33.0f, 29.0f, 
		28.0f, 31.0f, 31.0f, 
		28.0f, 33.0f, 29.0f 
	};

	mat3x3 d
	{
		25.0f, 30.0f, 35.0f,
		25.0f, 30.0f, 35.0f,
		27.0f, 30.0f, 33.0f
	};

	ASSERT_TRUE(c == result1);
	ASSERT_TRUE(d == result2);
	ASSERT_TRUE(result1 != result2);
}

TEST(mat_operations_test, transpose_test)
{
	mat3x3 a
	{
		1.0f, 2.0f, 3.0f,
		1.0f, 2.0f, 3.0f,
		1.0f, 2.0f, 3.0f
	};

	mat3x3 b
	{
		1.0f, 1.0f, 1.0f,
		2.0f, 2.0f, 2.0f,
		3.0f, 3.0f, 3.0f
	};

	auto result = transposed(a);
	ASSERT_TRUE(result == b);
}
