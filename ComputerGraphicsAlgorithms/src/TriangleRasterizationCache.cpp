#include "TriangleRasterizationCache.h"

namespace rtr
{
	TriangleRasterizationCache::TriangleRasterizationCache(const Triangle& tri) 
	{
		const auto x1 = tri.vertices_[0].position_.get(0);
		const auto y1 = tri.vertices_[0].position_.get(1);
		const auto x2 = tri.vertices_[1].position_.get(0);
		const auto y2 = tri.vertices_[1].position_.get(1);
		const auto x3 = tri.vertices_[2].position_.get(0);
		const auto y3 = tri.vertices_[2].position_.get(1);

		dx12_ = x1 - x2;
		dx23_ = x2 - x3;
		dx31_ = x3 - x1;

		dy12_ = y1 - y2;
		dy23_ = y2 - y3;
		dy31_ = y3 - y1;

		tl1_ = dy12_ < 0.0f || (math::eq(dy12_, 0.0f) && dx12_ > 0.0f);
		tl2_ = dy23_ < 0.0f || (math::eq(dy23_, 0.0f) && dx23_ > 0.0f);
		tl3_ = dy31_ < 0.0f || (math::eq(dy31_, 0.0f) && dx31_ > 0.0f);
	};
}