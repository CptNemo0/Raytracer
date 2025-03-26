#include "pch.h"
#include <numeric>
#include "raytracer_math.h"

using namespace math;

TEST(quat_operation_test, norm_test)
{
	quat a(1.0f, 1.0f, 1.0f, 1.0f);
	auto b = norm(a);
	constexpr auto eps = std::numeric_limits<float>::epsilon();
	ASSERT_TRUE(fabs(2.0f - b) < eps);
}

TEST(quat_operation_test, normalized_test)
{
	quat a(1.0f, 1.0f, 1.0f, 1.0f);
	quat b(0.5f, 0.5f, 0.5f, 0.5f);
	auto result = normalized(a);
	ASSERT_TRUE(b == result);
}

TEST(quat_operation_test, conjugate_test)
{
	quat a(1.0f, 1.0f, 1.0f, 1.0f);
	quat b(1.0f, -1.0f, -1.0f, - 1.0f);
	auto result = conjugated(a);
	ASSERT_TRUE(b == result);
}

TEST(quat_operation_test, inverse_test)
{
	quat a(2.0f, 2.0f, 2.0f, 2.0f);
	quat b(0.125f, -0.125f, -0.125f, -0.125f);
	auto result = inversed(a);
	ASSERT_TRUE(b == result);
}

TEST(quat_operation_test, unit_norm_test)
{
	quat a(30.0f, 1.0f, 0.0f, 0.0f);
	quat b(0.965925813f, 0.258819044f, 0.0f, 0.0f);
	to_unit_norm_deg(a);
	ASSERT_TRUE(b == a);
	
	
}