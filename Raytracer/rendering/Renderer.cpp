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

std::shared_ptr<primitives::Sphere> rendering::Renderer::AddSphere()
{
	auto sphere = std::make_shared<primitives::Sphere>();
	scene.push_back(sphere);
	return sphere;
}

std::shared_ptr<primitives::Sphere> rendering::Renderer::AddSphere(const math::vec3& center, float radius)
{
	auto sphere = std::make_shared<primitives::Sphere>(center, radius);
	scene.push_back(sphere);
	return sphere;
}

std::shared_ptr<primitives::Triangle> rendering::Renderer::AddTriangle(const math::vec3& a, const math::vec3& b, const math::vec3& c)
{
	auto triangle = std::make_shared<primitives::Triangle>(a, b, c);
	scene.push_back(triangle);
	return triangle;
}

std::shared_ptr<primitives::Triangle> rendering::Renderer::AddTriangle(const math::vec3& a, const math::vec3& b, const math::vec3& c, const math::vec3& na, const math::vec3& nb, const math::vec3& nc)
{
	auto triangle = std::make_shared<primitives::Triangle>(a, b, c, na, nb, nc);
	scene.push_back(triangle);
	return triangle;
}

void rendering::Renderer::Render() 
{
	static const std::vector<math::vec3> offsets
	{
		math::vec3(-0.5f, -0.5f, 0.07059f),
		math::vec3(0.5f, -0.5f, 0.07059f),
		math::vec3(-0.5f, 0.5f, 0.07059f),
		math::vec3(0.5f, 0.5f, 0.07059f),
		
		math::vec3(0.0f, -0.5f, 0.10682f),
		math::vec3(0.0f, 0.5f, 0.10682f),
		math::vec3(-0.5f, 0.0f,0.10682f),
		math::vec3(0.5f, 0.0f, 0.10682f),

		math::vec3(0.0f, 0.0f, 0.29036f)
	};

	const std::int32_t width = static_cast<std::int32_t>(buffer_->Width());
	const std::int32_t height = static_cast<std::int32_t>(buffer_->Height());

	const auto [camera_w, camera_h] = camera_->GetDimensions(buffer_->Width(), buffer_->Height());

	const float pixel_width  = camera_w / static_cast<float>(width);
	const float pixel_height = camera_h / static_cast<float>(height);

	const float start_x = -(camera_w * 0.5f) + pixel_width  * 0.5f;
	const float start_y =  (camera_h * 0.5f) - pixel_height * 0.5f;

	std::cout << "start_x: " << start_x << std::endl;
	std::cout << "start_y: " << start_y << std::endl;

	int hit = 0;
	int total = 0;

	for (std::int32_t y = 0; y < height; y++)
	{
		for (std::int32_t x = 0; x < width; x++)
		{
			if (x == 829 && y == 375)
			{
				std::cout << "x: " << x << " y: " << y << std::endl;
				
			}
			total++;
			math::vec4 color = buffer_->GetPixelf(x, y);
			math::vec4 result_color(0.0f);

			const float fx = start_x + static_cast<float>(x) * pixel_width;
			const float fy = start_y - static_cast<float>(y) * pixel_height;

			for (const auto& offset : offsets)
			{
				const auto addx = offset.get(0) * pixel_width * 1.50f;
				const auto addy = offset.get(1) * pixel_height * 1.50f;
				const auto weight = offset.get(2);

				const auto ray = camera_->GetRay(fx + addx, fy + addy);

				const auto& [result, mat] = ShootRay(ray);
				
				if (result.type == intersections::IntersectionType::MISS)
				{
					result_color += color * weight;
				}
				else if (result.type == intersections::IntersectionType::HIT)
				{
					hit++;
					result_color += mat.ambient * weight;
				}
			}
		
			buffer_->SetPixelf(x, y, result_color);
		}
	}

	std::cout << "hits: " << hit << std::endl;
	std::cout << "total: " << total << std::endl;
	
	buffer_->SaveColorToFile("test.bmp");
}

void rendering::Renderer::RenderAAOrto() 
{
	const std::int32_t width = static_cast<std::int32_t>(buffer_->Width());
	const std::int32_t height = static_cast<std::int32_t>(buffer_->Height());
	const auto [w, h] = camera_->GetDimensions(width, height);
	const auto pixel_width = w / static_cast<float>(buffer_->Width());
	const auto pixel_height = h / static_cast<float>(buffer_->Height());
	const auto start_x = -w * 0.5f + pixel_width * 0.5f;
	const auto start_y = h * 0.5f - pixel_height * 0.5f;
	
	int hits = 0;

	for (std::int32_t y = 0; y < height; y++)
	{
		for (std::int32_t x = 0; x < width; x++)
		{
			auto& color = buffer_->GetPixel(x, y);
			math::vec4 colorf = color;
			
			float localx = static_cast<float>(x) - (width / 2.0f);
			float localy = static_cast<float>(y) - (height / 2.0f);
			float fx = localx * camera_->scale_;
			float fy = localy * camera_->scale_;

			const math::vec3 ray_dir = camera_->forward_;
			const math::vec3 ray_pos = camera_->GetPixelPosition(fx, fy);

			if (ray_pos.get(2) != 0.0f)
			{
				exit(22);
			}

			const intersections::Ray ray(ray_pos, ray_dir);

			const auto& [result, mat] = ShootRay(ray);

			if (result.type == intersections::IntersectionType::HIT)
			{
				hits++;
				color = mat.ambient;
			}
		}
	}

	std::cout << "max hits: " << height * width << std::endl;
	std::cout << "hits: " << hits << std::endl;

	buffer_->SaveColorToFile("test.bmp");
}

std::pair<intersections::IntersectionResult, rendering::Material> rendering::Renderer::ShootRay(const intersections::Ray& ray) const
{
	Material hit_material;
	intersections::IntersectionResult hit_result;

	float depth = std::numeric_limits<float>::max();
	
	for (auto& geometry : scene)
	{
		intersections::IntersectionResult result;
		std::visit
		(
			[&result, &ray, &depth, &hit_material, &hit_result](auto& primitive)
			{
				result = primitive->Intersect(ray, 1000.0f);

				std::int16_t flags = 0;
				flags += (result.type != intersections::IntersectionType::HIT) << 0;
				flags += (depth < result.distance) << 1;
				
				if (flags) return;

				depth = result.distance;
				hit_material = primitive->material;
				hit_result = result;
			},
			geometry
		);
	}

	return std::make_pair(hit_result, hit_material);
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