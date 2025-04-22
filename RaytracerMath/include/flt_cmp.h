#ifndef FLT_CMP_H
#define FLT_CMP_H

#include "raytracer_math.h"
#include <limits>
namespace math
{
	inline bool eq(float a, float b)
	{
		constexpr auto eps = std::numeric_limits<float>::epsilon();

		return fabsf(a - b) < eps;
	}
}

#endif // !FLT_CMP_H

