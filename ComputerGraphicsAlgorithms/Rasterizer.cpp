#include "Rasterizer.h"
#include <limits>
#include <algorithm>
#include <iostream>

Rasterizer::Rasterizer(const std::uint32_t width, const std::uint32_t height)
{
	framebuffer_ = std::make_unique<PixelBuffer>(width, height);
}

void Rasterizer::DrawTriangle(const Triangle& input, const math::mat4x4& view_matrix)
{
	const auto width = static_cast<float>(framebuffer_->Width());
	const auto height = static_cast<float>(framebuffer_->Height());
	auto color_buffer = framebuffer_->ColorBuffer();
	
	const auto projection_matrix = math::projection_matrix(90, width / height, 0.1f, 100.0f);

	Triangle transformed = input;

	auto cull_bleeding = [](Triangle& tri)
	{
		for (std::int32_t i = 0; i < 3; i++)
		{
			auto& x = tri.vertices[i].position[0];
			auto& y = tri.vertices[i].position[1];

			if (x < -1.0f || x > 1.0f || y > 1.0 || y < -1.0f) return 1;
		}
		return 0;
	};

	auto transform_triangle = [width, height, &projection_matrix, &view_matrix](Triangle& tri)
	{
		for (std::int32_t i = 0; i < 3; i++)
		{
			auto& x = tri.vertices[i].position[0];
			auto& y = tri.vertices[i].position[1];
			auto& z = tri.vertices[i].position[2];

			const math::vec4 extended(x, y, z, 1.0f);
			const auto view_pos = math::transformed(view_matrix, extended);
			const auto projected = math::transformed(projection_matrix, view_pos);

			x = projected.get(0);
			y = projected.get(1);
			z = projected.get(2);

			x = (x + 1.0f) * width  * 0.5f;
			y = (y + 1.0f) * height * 0.5f;
		}
	};

	auto get_limits = [width, height](const Triangle& tri)
	{
		float left = std::numeric_limits<float>::max();
		float right = std::numeric_limits<float>::min();
		float top = std::numeric_limits<float>::max();
		float bot = std::numeric_limits<float>::min();

		for (const auto& vertex : tri.vertices)
		{
			left  = std::fminf(vertex.position.get(0), left);
			right = std::fmaxf(vertex.position.get(0), right);
			top   = std::fminf(vertex.position.get(1), top);
			bot   = std::fmaxf(vertex.position.get(1), bot);

			left  = std::fmaxf(left,  0.0f);
			right = std::fminf(right, width);
			top   = std::fmaxf(top,   0.0f);
			bot   = std::fminf(bot,   height);
		}

		const std::uint32_t lefti  = static_cast<std::uint32_t>(left);
		const std::uint32_t righti = static_cast<std::uint32_t>(right);
		const std::uint32_t topi   = static_cast<std::uint32_t>(top);
		const std::uint32_t boti   = static_cast<std::uint32_t>(bot);

		return std::make_tuple(lefti, righti, topi, boti);
	};

	auto pixel_inside = [](const float x, const float y, const Triangle& tri)
	{
		const auto x1 = tri.vertices[0].position.get(0);
		const auto y1 = tri.vertices[0].position.get(1);
		const auto x2 = tri.vertices[1].position.get(0);
		const auto y2 = tri.vertices[1].position.get(1);
		const auto x3 = tri.vertices[2].position.get(0);
		const auto y3 = tri.vertices[2].position.get(1);

		const auto dx12 = x1 - x2;
		const auto dx23 = x2 - x3;
		const auto dx31 = x3 - x1;

		const auto dy12 = y1 - y2;
		const auto dy23 = y2 - y3;
		const auto dy31 = y3 - y1;

		const auto tl1 = dy12 < 0.0f || (math::eq(dy12, 0.0f) && dx12 > 0.0f);
		const auto tl2 = dy23 < 0.0f || (math::eq(dy23, 0.0f) && dx23 > 0.0f);
		const auto tl3 = dy31 < 0.0f || (math::eq(dy31, 0.0f) && dx31 > 0.0f);

		bool inside = true;

		inside &= tl1 ? (x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) >= 0 : (x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) > 0;
		inside &= tl2 ? (x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) >= 0 : (x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) > 0;
		inside &= tl3 ? (x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) >= 0 : (x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) > 0;

		return  inside;
	};
	
	auto get_lambdas = [](const float x, const float y, const Triangle& tri)
	{
		const auto x1 = tri.vertices[0].position.get(0);
		const auto y1 = tri.vertices[0].position.get(1);
		const auto x2 = tri.vertices[1].position.get(0);
		const auto y2 = tri.vertices[1].position.get(1);
		const auto x3 = tri.vertices[2].position.get(0);
		const auto y3 = tri.vertices[2].position.get(1);
		
		const float denom1 = (y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3);
		const float denom2 = (y3 - y1) * (x2 - x3) + (x1 - x3) * (y2 - y3);
		
		const float lambda1 = ((y2 - y3) * (x - x3) + (x3 - x2) * (y - y3)) / denom1;
		const float lambda2 = ((y3 - y1) * (x - x3) + (x1 - x3) * (y - y3)) / denom2;
		const float lambda3 = 1.0f - lambda1 - lambda2;
		
		return std::make_tuple(lambda1, lambda2, lambda3);
	};

	transform_triangle(transformed);
	const auto [lefti, righti, topi, boti] = get_limits(transformed);
	
	for (std::uint32_t x = lefti; x < righti; x++)
	{
		for (std::uint32_t y = topi; y < boti; y++)
		{
			const auto fx = static_cast<float>(x) ;
			const auto fy = static_cast<float>(y) ;
			if (!pixel_inside(fx, fy, transformed)) continue;
			const auto [lambda1, lambda2, lambda3] = get_lambdas(fx, fy, transformed);

			const float depth = lambda1 * transformed.vertices[0].position[2] +
								lambda2 * transformed.vertices[1].position[2] +
								lambda3 * transformed.vertices[2].position[2];

			if (!framebuffer_->DepthCheckExchange(x, y, depth)) continue;

			color4f color = transformed.vertices[0].color * lambda1 +
							transformed.vertices[1].color * lambda2 +
							transformed.vertices[2].color * lambda3;

			framebuffer_->SetPixelf(x, y, color);
		}
	}
}