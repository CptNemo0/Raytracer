#include "Renderer.h"

void rendering::Renderer::AddGeometry(const primitives::geometry& geometry)
{
	scene_.push_back(geometry);
}

void rendering::Renderer::RenderScene()
{
	buffer_->ClearBuffers(color4(0, 0, 0, 255), FLT_MAX);
	FillBackground();


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

void rendering::Renderer::RenderGeometry(
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

void rendering::Renderer::FillBackground()
{
    const std::uint32_t bufWidth = buffer_->Width();
    const std::uint32_t bufHeight = buffer_->Height();

    constexpr int numCols = 6;
    constexpr int numRows = 6;

    // Obliczamy rozmiar jednego kwadratu w pikselach
    float squareWidth = static_cast<float>(bufWidth) / numCols;
    float squareHeight = static_cast<float>(bufHeight) / numRows;

    rendering::color4 baseColors[numCols] = {
        rendering::color4(255,   0,   0, 255),  // Red
        rendering::color4(0, 255,   0, 255),  // Green
        rendering::color4(0,   0, 255, 255),  // Blue
        rendering::color4(255,   0, 255, 255),  // Magenta
        rendering::color4(0, 255, 255, 255),  // Cyan
        rendering::color4(255, 255,   0, 255)   // Yellow
    };

    // Iterujemy po wierszach i kolumnach siatki 6x6
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            // Normalizujemy współczynniki w zakresie [0, 1]
            float factor_row = static_cast<float>(row + 1) / (numRows);

            // Interpolujemy kolor w zależności od wiersza
            int r = static_cast<int>(baseColors[col][0] * factor_row);
            int g = static_cast<int>(baseColors[col][1] * factor_row);
            int b = static_cast<int>(baseColors[col][2] * factor_row);
            rendering::color4 squareColor = rendering::color4(r, g, b, 255);

            // Wyznaczamy pikselowe współrzędne dla bieżącego kwadratu
            int startX = static_cast<int>(col * squareWidth);
            int startY = static_cast<int>(row * squareHeight);
            int endX = static_cast<int>((col + 1) * squareWidth);
            int endY = static_cast<int>((row + 1) * squareHeight);

            // Wypełniamy dany kwadrat ustalonym kolorem
            for (int y = startY; y < endY; ++y)
            {
                for (int x = startX; x < endX; ++x)
                {
                    buffer_->SetPixel(x, y, squareColor);
                }
            }
        }
    }
}