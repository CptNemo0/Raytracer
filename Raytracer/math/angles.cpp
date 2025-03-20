#include "angles.h"

namespace math
{
	float to_radians(float degrees)
	{
		return degrees * 0.0174532925f;
	}

	float to_degrees(float radians)
	{
		return radians * 57.2957795f;
	}
}