#include "Rasterizer.h"
#include <limits>
#include <algorithm>
#include <iostream>

Rasterizer::Rasterizer(const std::uint32_t width, const std::uint32_t height)
{
	framebuffer_ = std::make_unique<PixelBuffer>(width, height);
}

void Rasterizer::DrawTriangle(const triangle& input)
{
	for (const auto& vertex : input.vertices)
	{
		const auto& x = vertex.data_[0];
		const auto& y = vertex.data_[1];

		if (x > 1.0f || x < -1.0f || y > 1.0f || y < -1.0f) return;
	}

	triangle tri([&]()
	{
		triangle transformed = input;

		for (std::int32_t i = 0; i < 3; i++)
		{
			auto& x = transformed.vertices[i][0];
			auto& y = transformed.vertices[i][1];

			x = (x + 1) * this->framebuffer_->Width() * 0.5f;
			y = (y + 1) * this->framebuffer_->Height() * 0.5f;
		}

		return transformed;
	} ());

	float left = std::numeric_limits<float>::max();
	float right = std::numeric_limits<float>::min();
	float top = std::numeric_limits<float>::max();
	float bot = std::numeric_limits<float>::min();

	for (const auto& vertex : tri.vertices)
	{
		left = std::fminf(vertex.get(0), left);
		right = std::fmaxf(vertex.get(0), right);
		top = std::fminf(vertex.get(1), top);
		bot = std::fmaxf(vertex.get(1), bot);
	}

	left = std::fmaxf(left, 0.0f);
	right = std::fminf(right, static_cast<float>(framebuffer_->Width()));
	top = std::fmaxf(top, 0.0f);
	bot = std::fminf(bot, static_cast<float>(framebuffer_->Height()));

	const std::uint32_t lefti  = static_cast<std::uint32_t>(left);
	const std::uint32_t righti = static_cast<std::uint32_t>(right);
	const std::uint32_t topi   = static_cast<std::uint32_t>(top);
	const std::uint32_t boti   = static_cast<std::uint32_t>(bot);

	auto inside = [&tri](const std::uint32_t x, const std::uint32_t y)
	{
		const auto x1 = tri.vertices[0].get(0);
		const auto y1 = tri.vertices[0].get(1);
		const auto x2 = tri.vertices[1].get(0);
		const auto y2 = tri.vertices[1].get(1);
		const auto x3 = tri.vertices[2].get(0);
		const auto y3 = tri.vertices[2].get(1);
		return (x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) > 0
			&& (x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) > 0
			&& (x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) > 0;
	};

	auto color_buffer = framebuffer_->ColorBuffer();
	const auto h = framebuffer_->Height();
	const auto w = framebuffer_->Width();
	for (std::uint32_t x = lefti; x < right && x < w; x++)
	{
		for (std::uint32_t y = topi; y < boti && y < h; y++)
		{
			if (!inside(x, y)) continue;
			auto& color = framebuffer_->GetPixel(x, y);
			color = color4(255.0f, 0.0f, 0.0f, 255.0f);
		}
	}
}