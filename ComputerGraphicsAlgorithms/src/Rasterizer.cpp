#include "Rasterizer.h"
#include <limits>
#include <algorithm>
#include <iostream>

namespace rtr
{
	Rasterizer::Rasterizer(const std::uint32_t width, const std::uint32_t height, std::shared_ptr<Preprocessor> preprocessor)
	{
		framebuffer_ = std::make_unique<PixelBuffer>(width, height);
		preprocessor_ = preprocessor;
	}

	void Rasterizer::DrawTriangle(const mesh::Triangle& input)
	{
		const auto width = static_cast<float>(framebuffer_->Width());
		const auto height = static_cast<float>(framebuffer_->Height());
		auto& color_buffer = framebuffer_->ColorBuffer();

		mesh::Triangle transformed = input;
		preprocessor_->TriangleLocal2Screen(transformed);
		TriangleRasterizationCache trc(transformed);

		float left = std::numeric_limits<float>::max();
		float right = std::numeric_limits<float>::min();
		float top = std::numeric_limits<float>::max();
		float bot = std::numeric_limits<float>::min();

		for (const auto& vertex : transformed.vertices_)
		{
			left = std::fminf(vertex.position_.get(0), left);
			right = std::fmaxf(vertex.position_.get(0), right);
			top = std::fminf(vertex.position_.get(1), top);
			bot = std::fmaxf(vertex.position_.get(1), bot);

			left = std::fmaxf(left, 0.0f);
			right = std::fminf(right, width);
			top = std::fmaxf(top, 0.0f);
			bot = std::fminf(bot, height);
		}

		const std::uint32_t lefti = static_cast<std::uint32_t>(left);
		const std::uint32_t righti = static_cast<std::uint32_t>(right);
		const std::uint32_t topi = static_cast<std::uint32_t>(top);
		const std::uint32_t boti = static_cast<std::uint32_t>(bot);

		for (std::uint32_t x = lefti; x < righti; x++)
		{
			for (std::uint32_t y = topi; y < boti; y++)
			{
				const auto fx = static_cast<float>(x);
				const auto fy = static_cast<float>(y);
				if (!PixelInside(fx, fy, transformed, trc)) continue;
				const auto [lambda1, lambda2, lambda3] = GetLambdas(fx, fy, transformed, trc);

				float depth = lambda1 * transformed.vertices_[0].position_[2] +
					lambda2 * transformed.vertices_[1].position_[2] +
					lambda3 * transformed.vertices_[2].position_[2];

				if (!framebuffer_->DepthCheckExchange(x, y, depth)) continue;

				//math::vec3 color = transformed.vertices_[0].normal_ * lambda1 +
				//				   transformed.vertices_[1].normal_ * lambda2 +
				//				   transformed.vertices_[2].normal_ * lambda3;
				//math::vec4 color4 = math::vec4(color.get(0) * 255.0f, color.get(1) * 255.0f, color.get(2) * 255.0f, 255.0f);
				//depth = 1 - depth;

				//color = color4f(depth * 255.0f, depth * 255.0f, depth * 255.0f, 255.0f);

				framebuffer_->SetPixelf(x, y, preprocessor_->color_);
			}
		}
	}

	void Rasterizer::DrawMesh(const mesh::ProceduralMesh& mesh)
	{
		srand(time(0));	
		for (std::size_t i = 0; i < mesh.indices_.size(); i += 3)
		{
			preprocessor_->color_ = color4f(rand() % 255, rand() % 255, rand() % 255, 255.0f);
			mesh::Triangle tri 
			(
				mesh.vertices_[mesh.indices_[i]],
				mesh.vertices_[mesh.indices_[i + 1]],
				mesh.vertices_[mesh.indices_[i + 2]]
			);
			DrawTriangle(tri);
		}
	}
	
	void* Rasterizer::GetData()
	{
		return reinterpret_cast<void*>(const_cast<color4*>(framebuffer_->ColorBuffer().data()));
	}
}

