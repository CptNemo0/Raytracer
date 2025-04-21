#ifndef RASTERIZER_H
#define RASTERIZER_H

#include<array>
#include<memory>

#include "aliasing.h"
#include "PixelBuffer.h"
#include "raytracer_math.h"
#include "Triangle.h"
#include "Vertex.h"
#include "Preprocessor.h"

namespace rtr
{
	class Rasterizer
	{
	private:
		struct TriangleRenderCache
		{
			float dx12;
			float dx23;
			float dx31;

			float dy12;
			float dy23;
			float dy31;

			float tl1;
			float tl2;
			float tl3;

			TriangleRenderCache(const Triangle& tri)
			{
				const auto x1 = tri.vertices[0].position.get(0);
				const auto y1 = tri.vertices[0].position.get(1);
				const auto x2 = tri.vertices[1].position.get(0);
				const auto y2 = tri.vertices[1].position.get(1);
				const auto x3 = tri.vertices[2].position.get(0);
				const auto y3 = tri.vertices[2].position.get(1);

				dx12 = x1 - x2;
				dx23 = x2 - x3;
				dx31 = x3 - x1;

				dy12 = y1 - y2;
				dy23 = y2 - y3;
				dy31 = y3 - y1;

				tl1 = dy12 < 0.0f || (math::eq(dy12, 0.0f) && dx12 > 0.0f);
				tl2 = dy23 < 0.0f || (math::eq(dy23, 0.0f) && dx23 > 0.0f);
				tl3 = dy31 < 0.0f || (math::eq(dy31, 0.0f) && dx31 > 0.0f);
			};
		};

		inline bool PixelInside(const float x, const float y, const Triangle& tri, const TriangleRenderCache& trc)
		{
			const auto x1 = tri.vertices[0].position.get(0);
			const auto y1 = tri.vertices[0].position.get(1);
			const auto x2 = tri.vertices[1].position.get(0);
			const auto y2 = tri.vertices[1].position.get(1);
			const auto x3 = tri.vertices[2].position.get(0);
			const auto y3 = tri.vertices[2].position.get(1);

			bool inside = true;

			inside &= trc.tl1 ? trc.dx12 * (y - y1) - trc.dy12 * (x - x1) >= 0 : trc.dx12 * (y - y1) - trc.dy12 * (x - x1) > 0;
			inside &= trc.tl2 ? trc.dx23 * (y - y2) - trc.dy23 * (x - x2) >= 0 : trc.dx23 * (y - y2) - trc.dy23 * (x - x2) > 0;
			inside &= trc.tl3 ? trc.dx31 * (y - y3) - trc.dy31 * (x - x3) >= 0 : trc.dx31 * (y - y3) - trc.dy31 * (x - x3) > 0;

			return  inside;
		};

		std::tuple<const float, const float, const float> GetLambdas(const float x, const float y, const Triangle& tri, const TriangleRenderCache& trc)
		{
			const auto x1 = tri.vertices[0].position.get(0);
			const auto y1 = tri.vertices[0].position.get(1);
			const auto x2 = tri.vertices[1].position.get(0);
			const auto y2 = tri.vertices[1].position.get(1);
			const auto x3 = tri.vertices[2].position.get(0);
			const auto y3 = tri.vertices[2].position.get(1);

			const float denom1 = trc.dx23 * trc.dy31 - trc.dy23 * trc.dx31;
			const float denom2 = trc.dy31 * trc.dx23 - trc.dx31 * trc.dy23;

			const float lambda1 = (trc.dy23 * (x - x3) - trc.dx23 * (y - y3)) / denom1;
			const float lambda2 = (trc.dy31 * (x - x3) - trc.dx31 * (y - y3)) / denom2;
			const float lambda3 = 1.0f - lambda1 - lambda2;

			return std::make_tuple(lambda1, lambda2, lambda3);
		};

	public:
		std::unique_ptr<PixelBuffer> framebuffer_;
		std::shared_ptr<Preprocessor> preprocessor_;
		Rasterizer(const std::uint32_t width, const std::uint32_t height, std::shared_ptr<Preprocessor> preprocessor);
		void DrawTriangle(const Triangle& tri);
	};
}


#endif // !RASTERIZER_H