#ifndef RASTERIZER_H
#define RASTERIZER_H

#include<array>
#include<memory>

#include "aliasing.h"
#include "PixelBuffer.h"
#include "raytracer_math.h"
#include "Preprocessor.h"
#include "TriangleRasterizationCache.h"

#include "mesh/ProceduralMesh.h"
#include "mesh/Triangle.h"
#include "mesh/Vertex.h"

namespace rtr
{
	class Rasterizer
	{
	private:
		inline bool PixelInside(const float x, const float y, const mesh::Triangle& tri, const TriangleRasterizationCache& trc)
		{
			const auto x1 = tri.vertices_[0].position_.get(0);
			const auto y1 = tri.vertices_[0].position_.get(1);
			const auto x2 = tri.vertices_[1].position_.get(0);
			const auto y2 = tri.vertices_[1].position_.get(1);
			const auto x3 = tri.vertices_[2].position_.get(0);
			const auto y3 = tri.vertices_[2].position_.get(1);

			bool inside = true;

			inside &= trc.tl1_ ? trc.dx12_ * (y - y1) - trc.dy12_ * (x - x1) >= 0 : trc.dx12_ * (y - y1) - trc.dy12_ * (x - x1) > 0;
			inside &= trc.tl2_ ? trc.dx23_ * (y - y2) - trc.dy23_ * (x - x2) >= 0 : trc.dx23_ * (y - y2) - trc.dy23_ * (x - x2) > 0;
			inside &= trc.tl3_ ? trc.dx31_ * (y - y3) - trc.dy31_ * (x - x3) >= 0 : trc.dx31_ * (y - y3) - trc.dy31_ * (x - x3) > 0;

			return  inside;
		};

		std::tuple<const float, const float, const float> GetLambdas(const float x, const float y, const mesh::Triangle& tri, const TriangleRasterizationCache& trc)
		{
			const auto x1 = tri.vertices_[0].position_.get(0);
			const auto y1 = tri.vertices_[0].position_.get(1);
			const auto x2 = tri.vertices_[1].position_.get(0);
			const auto y2 = tri.vertices_[1].position_.get(1);
			const auto x3 = tri.vertices_[2].position_.get(0);
			const auto y3 = tri.vertices_[2].position_.get(1);

			const float denom1 = trc.dx23_ * trc.dy31_ - trc.dy23_ * trc.dx31_;
			const float denom2 = trc.dy31_ * trc.dx23_ - trc.dx31_ * trc.dy23_;

			const float lambda1 = (trc.dy23_ * (x - x3) - trc.dx23_ * (y - y3)) / denom1;
			const float lambda2 = (trc.dy31_ * (x - x3) - trc.dx31_ * (y - y3)) / denom2;
			const float lambda3 = 1.0f - lambda1 - lambda2;

			return std::make_tuple(lambda1, lambda2, lambda3);
		};

	public:
		std::unique_ptr<PixelBuffer> framebuffer_;
		std::shared_ptr<Preprocessor> preprocessor_;
		Rasterizer(const std::uint32_t width, const std::uint32_t height, std::shared_ptr<Preprocessor> preprocessor);
		void DrawTriangle(const mesh::Triangle& tri);
		void DrawMesh(const mesh::ProceduralMesh& mesh);
		void* GetData();
		inline void ClearBuffers()
		{
			framebuffer_->ColorfClear(preprocessor_->background_color_);
			framebuffer_->DepthClear(std::numeric_limits<float>::max());
		};
	};
}


#endif // !RASTERIZER_H