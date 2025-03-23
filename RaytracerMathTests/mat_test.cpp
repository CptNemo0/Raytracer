#include "pch.h"

#include "raytracer_math.h"

using namespace math;

TEST(mat_test, equality_operator)
{
	mat4x4 a 
	{
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f
	};
	mat4x4 b
	{
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f
	};
	
	ASSERT_TRUE(a == b);
}

TEST(mat_test, inequality_operator)
{
	mat4x4 a
	{
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 0.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f
	};
	mat4x4 b
	{
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f
	};

	ASSERT_TRUE(a != b);
}

TEST(mat_test, add_operator)
{
	mat4x4 a
	{
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f
	};
	mat4x4 b
	{
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f
	};
	mat4x4 c
	{
		2.0f, 4.0f, 6.0f, 8.0f,
		2.0f, 4.0f, 6.0f, 8.0f,
		2.0f, 4.0f, 6.0f, 8.0f,
		2.0f, 4.0f, 6.0f, 8.0f
	};
	auto result = a + b;

	ASSERT_TRUE(c == result);
}

TEST(mat_test, add_eq_operator)
{
	mat4x4 a
	{
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f
	};
	mat4x4 b
	{
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f
	};
	mat4x4 c
	{
		2.0f, 4.0f, 6.0f, 8.0f,
		2.0f, 4.0f, 6.0f, 8.0f,
		2.0f, 4.0f, 6.0f, 8.0f,
		2.0f, 4.0f, 6.0f, 8.0f
	};
	a += b;

	ASSERT_TRUE(c == a);
}

TEST(mat_test, sub_operator)
{
	mat4x4 a
	{
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f
	};
	mat4x4 b
	{
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f
	};
	mat4x4 c;
	auto result = a - b;

	ASSERT_TRUE(c == result);
}

TEST(mat_test, sub_eq_operator)
{
	mat4x4 a
	{
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f
	};
	mat4x4 b
	{
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f
	};
	mat4x4 c;
	a -= b;

	ASSERT_TRUE(c == a);
}

TEST(mat_test, mul_operator)
{
	mat4x4 a
	{
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f
	};
	float b = 2.0f;
	auto result = a * b;
	mat4x4 c
	{
		2.0f, 4.0f, 6.0f, 8.0f,
		2.0f, 4.0f, 6.0f, 8.0f,
		2.0f, 4.0f, 6.0f, 8.0f,
		2.0f, 4.0f, 6.0f, 8.0f
	};
	
	ASSERT_TRUE(c == result);
}

TEST(mat_test, mul_eq_operator)
{
	mat4x4 a
	{
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f,
		1.0f, 2.0f, 3.0f, 4.0f
	};
	float b = 2.0f;
	a *= b;
	mat4x4 c
	{
		2.0f, 4.0f, 6.0f, 8.0f,
		2.0f, 4.0f, 6.0f, 8.0f,
		2.0f, 4.0f, 6.0f, 8.0f,
		2.0f, 4.0f, 6.0f, 8.0f
	};

	ASSERT_TRUE(c == a);
}

TEST(mat_test, div_operator)
{
	mat4x4 a
	{
		2.0f, 2.0f, 2.0f, 2.0f,
		2.0f, 2.0f, 2.0f, 2.0f,
		2.0f, 2.0f, 2.0f, 2.0f,
		2.0f, 2.0f, 2.0f, 2.0f,
	};
	float b = 2.0f;
	auto result = a / b;
	mat4x4 c(1.0f, false);

	ASSERT_TRUE(c == result);
}

TEST(mat_test, div_eq_operator)
{
	mat4x4 a
	{
		2.0f, 2.0f, 2.0f, 2.0f,
		2.0f, 2.0f, 2.0f, 2.0f,
		2.0f, 2.0f, 2.0f, 2.0f,
		2.0f, 2.0f, 2.0f, 2.0f,
	};
	float b = 2.0f;
	a /= b;
	mat4x4 c(1.0f, false);

	ASSERT_TRUE(c == a);
}