#ifndef TRIANGLE_RASTERIZATION_CACHE
#define TRIANGLE_RASTERIZATION_CACHE

#include "mesh/Triangle.h"

namespace rtr
{
	class TriangleRasterizationCache
	{
	public:
		int dx12_ = 0;
		int dx23_ = 0;
		int dx31_ = 0;

		int dy12_ = 0;
		int dy23_ = 0;
		int dy31_ = 0;

		bool tl1_  = false;
		bool tl2_  = false;
		bool tl3_  = false;

		TriangleRasterizationCache(const mesh::Triangle& tri);
	};
}

#endif // !TRIANGLE_RASTERIZATION_CACHE