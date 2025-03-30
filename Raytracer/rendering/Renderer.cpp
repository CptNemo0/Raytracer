#include "Renderer.h"

void rendering::Renderer::AddGeometry(const primitives::geometry& geometry)
{
	scene_.push_back(geometry);
}

void rendering::Renderer::RenderScene()
{
	buffer_->ClearBuffers(color4(0, 0, 0, 255), FLT_MAX);

	const auto [w, h] = camera_->GetDimensions();
	const float pixel_width = w / static_cast<float>(buffer_->Width());
	const float pixel_height = h / static_cast<float>(buffer_->Height());
	const float start_x = -w * 0.5f + pixel_width * 0.5f;
	const float start_y = h * 0.5f - pixel_height * 0.5f;
	const std::int32_t width = static_cast<std::int32_t>(buffer_->Width());
	const std::int32_t height = static_cast<std::int32_t>(buffer_->Height());

	for (const auto& geometry : scene_)
	{
		RenderGeometry(geometry, width, height, pixel_width, pixel_height, start_x, start_y);
	}

	buffer_->SaveColorToFile("test.bmp");
}

inline void rendering::Renderer::RenderGeometry(
	const primitives::geometry& geometry,
	std::int32_t width, std::int32_t height,
	float pixel_width, float pixel_height,
	float start_x, float start_y)
{
	for (std::int32_t y = 0; y < height; y++)
	{
		for (std::int32_t x = 0; x < width; x++)
		{
			const float fx = start_x + static_cast<float>(x) * pixel_width;
			const float fy = start_y - static_cast<float>(y) * pixel_height;

			intersections::Ray ray = camera_->GetRay(fx, fy);
			intersections::IntersectionResult result;

			std::visit
			(
				[&result, &ray](auto& primitive)
				{
					result = primitive.Intersect(ray, 1000);
				},
				geometry
			);

			if (result.type == intersections::IntersectionType::MISS)
			{
				continue;
			}

			float& depth = buffer_->DepthBuffer()[buffer_->xy_to_index(x, y)];

			if (result.distance < depth)
			{
				depth = result.distance;
				rendering::color4 color;
				std::visit
				(
					[&](auto& primitive)
					{
						color = primitive.GetMaterial().ambient;
					},
					geometry
				);

				buffer_->SetPixel(x, y, color);
			}

		}
	}
}
