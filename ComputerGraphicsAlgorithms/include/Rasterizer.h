#ifndef RASTERIZER_H
#define RASTERIZER_H

#include<array>
#include<memory>

#include "aliasing.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
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
			const auto x2 = tri.vertices_[1].position_.get(0);
			const auto x3 = tri.vertices_[2].position_.get(0);

			const auto y1 = tri.vertices_[0].position_.get(1);
			const auto y2 = tri.vertices_[1].position_.get(1);
			const auto y3 = tri.vertices_[2].position_.get(1);

			auto edge1 = trc.dx12_* (y - y1) - trc.dy12_ * (x - x1);
			auto edge2 = trc.dx23_* (y - y2) - trc.dy23_ * (x - x2);
			auto edge3 = trc.dx31_* (y - y3) - trc.dy31_ * (x - x3);

			//return (edge1 >= 1.0f && edge2 >= 1.0f && edge3 >= 1.0f);

			return    (trc.tl1_ ? edge1 >= 0.0f : edge1 > 0.0f)
				   && (trc.tl2_ ? edge2 >= 0.0f : edge2 > 0.0f)
				   && (trc.tl3_ ? edge3 >= 0.0f : edge3 > 0.0f);
		};

		std::tuple<const float, const float, const float> GetLambdas(const float x, const float y, const mesh::Triangle& tri, const TriangleRasterizationCache& trc)
		{
			const auto x1 = tri.vertices_[0].position_.get(0);
			const auto y1 = tri.vertices_[0].position_.get(1);
			const auto x2 = tri.vertices_[1].position_.get(0);
			const auto y2 = tri.vertices_[1].position_.get(1);
			const auto x3 = tri.vertices_[2].position_.get(0);
			const auto y3 = tri.vertices_[2].position_.get(1);

			const float denom1 = static_cast<float>(trc.dx23_ * trc.dy31_ - trc.dy23_ * trc.dx31_);
			const float denom2 = static_cast<float>(trc.dy31_ * trc.dx23_ - trc.dx31_ * trc.dy23_);

			const float lambda1 = (trc.dy23_ * (x - x3) - trc.dx23_ * (y - y3)) / denom1;
			const float lambda2 = (trc.dy31_ * (x - x3) - trc.dx31_ * (y - y3)) / denom2;
			const float lambda3 = 1.0f - lambda1 - lambda2;

			return std::make_tuple(lambda1, lambda2, lambda3);
		};

	public:
		std::unique_ptr<PixelBuffer> framebuffer_;
		std::shared_ptr<Preprocessor> preprocessor_;
		
		std::vector<std::shared_ptr<Light>> lights_;

		Rasterizer(const std::uint32_t width, const std::uint32_t height, std::shared_ptr<Preprocessor> preprocessor);
		void DrawTriangle(const mesh::Triangle& tri);
		void DrawMesh(const mesh::ProceduralMesh& mesh);
		void* GetData();
		inline void ClearBuffers()
		{
			framebuffer_->ColorfClear(preprocessor_->background_color_);
			framebuffer_->DepthClear(std::numeric_limits<float>::max());
		};

		void DrawTriangleLightVertex(const mesh::Triangle& input, const math::ivec3 vidx, const std::vector<color3f>& colors);
		void DrawMeshLightVertex(const mesh::ProceduralMesh& mesh);
	};
}


#endif // !RASTERIZER_H