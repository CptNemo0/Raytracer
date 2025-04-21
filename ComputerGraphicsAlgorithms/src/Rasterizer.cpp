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

	void Rasterizer::DrawTriangle(const Triangle& input)
	{
		const auto width = static_cast<float>(framebuffer_->Width());
		const auto height = static_cast<float>(framebuffer_->Height());
		auto& color_buffer = framebuffer_->ColorBuffer();

		Triangle transformed = input;
		preprocessor_->TriangleLocal2Screen(transformed);
		TriangleRenderCache trc(transformed);

		float left = std::numeric_limits<float>::max();
		float right = std::numeric_limits<float>::min();
		float top = std::numeric_limits<float>::max();
		float bot = std::numeric_limits<float>::min();

		for (const auto& vertex : transformed.vertices)
		{
			left = std::fminf(vertex.position.get(0), left);
			right = std::fmaxf(vertex.position.get(0), right);
			top = std::fminf(vertex.position.get(1), top);
			bot = std::fmaxf(vertex.position.get(1), bot);

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

				float depth = lambda1 * transformed.vertices[0].position[2] +
					lambda2 * transformed.vertices[1].position[2] +
					lambda3 * transformed.vertices[2].position[2];

				if (!framebuffer_->DepthCheckExchange(x, y, depth)) continue;

				//color4f color = transformed.vertices[0].color * lambda1 +
				//				transformed.vertices[1].color * lambda2 +
				//				transformed.vertices[2].color * lambda3;

				//depth = 1 - depth;

				//color = color4f(depth * 255.0f, depth * 255.0f, depth * 255.0f, 255.0f);

				framebuffer_->SetPixelf(x, y, preprocessor_->color_);
			}
		}
	}
}

