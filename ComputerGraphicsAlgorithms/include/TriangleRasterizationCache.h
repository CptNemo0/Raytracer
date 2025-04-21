#ifndef TRIANGLE_RASTERIZATION_CACHE
#define TRIANGLE_RASTERIZATION_CACHE

#include "Triangle.h"

namespace rtr
{
	class TriangleRasterizationCache
	{
	public:
		float dx12_ = 0.0f;
		float dx23_ = 0.0f;
		float dx31_ = 0.0f;

		float dy12_ = 0.0f;
		float dy23_ = 0.0f;
		float dy31_ = 0.0f;

		float tl1_  = 0.0f;
		float tl2_  = 0.0f;
		float tl3_  = 0.0f;

		TriangleRasterizationCache(const Triangle& tri);
	};
}

#endif // !TRIANGLE_RASTERIZATION_CACHE