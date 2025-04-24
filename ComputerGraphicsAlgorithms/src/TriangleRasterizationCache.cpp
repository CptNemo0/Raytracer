#include "TriangleRasterizationCache.h"

namespace rtr
{
	TriangleRasterizationCache::TriangleRasterizationCache(const mesh::Triangle& tri)
	{
		const auto x1 = tri.vertices_[0].position_.get(0);
		const auto x2 = tri.vertices_[1].position_.get(0);
		const auto x3 = tri.vertices_[2].position_.get(0);

		const auto y1 = tri.vertices_[0].position_.get(1);
		const auto y2 = tri.vertices_[1].position_.get(1);
		const auto y3 = tri.vertices_[2].position_.get(1);

		dx12_ = static_cast<int>(x1 - x2);
		dx23_ = static_cast<int>(x2 - x3);
		dx31_ = static_cast<int>(x3 - x1);
							
		dy12_ = static_cast<int>(y1 - y2);
		dy23_ = static_cast<int>(y2 - y3);
		dy31_ = static_cast<int>(y3 - y1);

		tl1_ = ( dy12_ < 0 || ((dy12_ == 0.0f) && dx12_ > 0) );
		tl2_ = ( dy23_ < 0 || ((dy23_ == 0.0f) && dx23_ > 0) );
		tl3_ = ( dy31_ < 0 || ((dy31_ == 0.0f) && dx31_ > 0) );
	};
}