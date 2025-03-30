#ifndef MATH_FLOAT_CMP
#define MATH_FLOAT_CMP

#include <cmath>
#include <limits>

namespace math
{
	inline bool flt_eq(float a, float b)
	{
		constexpr auto eps = std::numeric_limits<float>::epsilon();
		return fabs(a - b) < eps;
	}
}

#endif // !MATH_FLOAT_CMP
