#ifndef MATH_ANGLES_H
#define MATH_ANGLES_H

namespace math
{
	constexpr float pi = 3.14159265359f;
	constexpr float two_pi = 2.0f * 3.14159265359f;
	constexpr float pid2 = 3.14159265359f / 2.0f;
	constexpr float pid3 = 3.14159265359f / 3.0f;
	constexpr float pid4 = 3.14159265359f / 4.0f;
	constexpr float pid6 = 3.14159265359f / 6.0f;
	constexpr float pid8 = 3.14159265359f / 8.0f;

	float to_radians(float degrees)
	{
		degrees *= 0.0174532925f;
	}

	float to_degrees(float radians)
	{
		radians *= 57.2957795f;
	}
}

#endif // !MATH_ANGLES_H
