#include "pch.h"

#include "raytracer_math.h"

using namespace math;

TEST(quat_test, equality_operator)
{
	quat a(1.0f, 2.0f, 3.0f, 4.0f);
	quat b(1.0f, 2.0f, 3.0f, 4.0f);
	ASSERT_TRUE(a == b);
}

TEST(quat_test, inequality_operator)
{
	quat a(1.0f, 2.0f, 3.0f, 4.0f);
	quat b(1.0f, 0.0f, 3.0f, 4.0f);
	quat c(0.0f, 2.0f, 3.0f, 4.0f);
	ASSERT_TRUE(a != b);
	ASSERT_TRUE(b != c);
}

TEST(quat_test, add_operator)
{
	quat a(1.0f, 2.0f, 3.0f, 4.0f);
	quat b(1.0f, 2.0f, 3.0f, 4.0f);
	quat c(2.0f, 4.0f, 6.0f, 8.0f);
	auto result = a + b;
	ASSERT_TRUE(result == c);
}

TEST(quat_test, add_eq_operator)
{
	quat a(1.0f, 2.0f, 3.0f, 4.0f);
	quat b(1.0f, 2.0f, 3.0f, 4.0f);
	quat c(2.0f, 4.0f, 6.0f, 8.0f);
	a += b;
	ASSERT_TRUE(a == c);
}

TEST(quat_test, sub_operator)
{
	quat a(1.0f, 2.0f, 3.0f, 4.0f);
	quat b(1.0f, 2.0f, 3.0f, 4.0f);
	quat c(0.0f, 0.0f, 0.0f, 0.0f);
	auto result = a - b;
	ASSERT_TRUE(result == c);
}

TEST(quat_test, sub_eq_operator)
{
	quat a(1.0f, 2.0f, 3.0f, 4.0f);
	quat b(1.0f, 2.0f, 3.0f, 4.0f);
	quat c(0.0f, 0.0f, 0.0f, 0.0f);
	a -= b;
	ASSERT_TRUE(a == c);
}

TEST(quat_test, mul_float_operator)
{
	quat a(1.0f, 2.0f, 3.0f, 4.0f);
	float b = 2.0f;
	quat c(2.0f, 4.0f, 6.0f, 8.0f);
	auto result = a * b;
	ASSERT_TRUE(result == c);
}

TEST(quat_test, mul_eq_float_operator)
{
	quat a(1.0f, 2.0f, 3.0f, 4.0f);
	float b = 2.0f;
	quat c(2.0f, 4.0f, 6.0f, 8.0f);
	a *= b;
	ASSERT_TRUE(a == c);
}

TEST(quat_test, mul_operator)
{
	quat a(1.0f, 2.0f, 3.0f, 4.0f);
	quat b(5.0f, 6.0f, 7.0f, 8.0f);
	auto result1 = a * b;
	auto result2 = b * a;
	ASSERT_TRUE(result1 != result2);
	quat c(-60.0f, 12.0f, 30.0f, 24.0f);
	quat d(-60.0f, 20.0f, 14.0f, 32.0f);

	ASSERT_TRUE(c == result1);
	ASSERT_TRUE(d == result2);
}

TEST(quat_test, mul_eq_operator)
{
	quat a(1.0f, 2.0f, 3.0f, 4.0f);
	quat b(5.0f, 6.0f, 7.0f, 8.0f);
	quat c(-60.0f, 12.0f, 30.0f, 24.0f);
	a *= b;

	ASSERT_TRUE(c == a);
}