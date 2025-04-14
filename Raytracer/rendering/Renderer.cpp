#include "Renderer.h"


void rendering::Renderer::AddPointLight(const lights::PointLight& light)
{
	lights_.push_back(light);
}

std::shared_ptr<primitives::Sphere> rendering::Renderer::AddSphere()
{
	auto sphere = std::make_shared<primitives::Sphere>();
	scene_.push_back(sphere);
	return sphere;
}

std::shared_ptr<primitives::Sphere> rendering::Renderer::AddSphere(const math::vec3& center, float radius)
{
	auto sphere = std::make_shared<primitives::Sphere>(center, radius);
	scene_.push_back(sphere);
	return sphere;
}

std::shared_ptr<primitives::Triangle> rendering::Renderer::AddTriangle(const math::vec3& a, const math::vec3& b, const math::vec3& c)
{
	auto triangle = std::make_shared<primitives::Triangle>(a, b, c);
	scene_.push_back(triangle);
	return triangle;
}

std::shared_ptr<primitives::Triangle> rendering::Renderer::AddTriangle(const math::vec3& a, const math::vec3& b, const math::vec3& c, const math::vec3& na, const math::vec3& nb, const math::vec3& nc)
{
	auto triangle = std::make_shared<primitives::Triangle>(a, b, c, na, nb, nc);
	scene_.push_back(triangle);
	return triangle;
}

std::shared_ptr<primitives::Plane> rendering::Renderer::AddPlane(const math::vec3& normal, const math::vec3& point)
{
	auto plane = std::make_shared<primitives::Plane>(normal, point);
	scene_.push_back(plane);
	return plane;
}

rendering::color4f rendering::Renderer::CalculatePointLighting(const intersections::IntersectionResult& result, const rendering::Material& material_, const lights::PointLight light) const
{
	rendering::color4f final_color(0, 0, 0, 255);
	
	math::vec3 light_dir = light.position - result.intersection_point;
	math::normalize(light_dir);

	float distance = math::length(light_dir);
	float attenuation = 1.0f / (light.intensity + light.constAtten + light.linearAtten * distance + light.quadAtten * distance * distance);


	rendering::color4f ambient_ = material_.ambient_ * light.color;

	float diff = std::max(math::dot(result.intersection_normal, light_dir), 0.0f);
	rendering::color4f diffuse_ = material_.diffuse_ * diff * light.color;

	math::vec3 view_dir = camera_->position_ - result.intersection_point;
	math::normalize(view_dir);

	math::vec3 reflect_dir =  result.intersection_normal * 2.0f * math::dot(result.intersection_normal, light_dir) - light_dir;

	float spec = std::pow(std::max(math::dot(view_dir, reflect_dir), 0.0f), material_.shininess_);
	rendering::color4f specular_ = material_.specular_ * light.color * spec;

	ambient_ = ambient_ * attenuation;
	diffuse_ = diffuse_ * attenuation;
	specular_ = specular_ * attenuation;

	final_color += ambient_ + diffuse_ + specular_;

	return final_color;
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

		math::vec3(0.0f, 0.0f, 0.29036f)//
	};

	const std::int32_t width = static_cast<std::int32_t>(buffer_->Width());
	const std::int32_t height = static_cast<std::int32_t>(buffer_->Height());

	const auto [camera_w, camera_h] = camera_->GetDimensions(buffer_->Width(), buffer_->Height());

	const float pixel_width  = camera_w / static_cast<float>(width);
	const float pixel_height = camera_h / static_cast<float>(height);

	const float start_x = -(camera_w * 0.5f) + pixel_width  * 0.5f;
	const float start_y =  (camera_h * 0.5f) - pixel_height * 0.5f;
	int shadowed = 0;
	for (std::int32_t y = 0; y < height; y++)
	{
		for (std::int32_t x = 0; x < width; x++)
		{
			const math::vec4 color = buffer_->GetPixelf(x, y);
			math::vec4 result_color(0.0f);

			const float fx = start_x + static_cast<float>(x) * pixel_width;
			const float fy = start_y - static_cast<float>(y) * pixel_height;

			for (const auto& offset : offsets)
			{
				const auto addx = offset.get(0) * pixel_width * 1.50f;
				const auto addy = offset.get(1) * pixel_height * 1.50f;
				const auto weight = offset.get(2);

				auto ray = camera_->GetRay(fx + addx, fy + addy);
				Material mat;
				intersections::IntersectionResult result;

				bool refractive = false;

				for (std::uint32_t depth = 0; depth < max_depth_; depth++)
				{
					const auto& [local_result, local_mat] = ShootRay(ray);
					mat = local_mat;
					result = local_result;

					if (result.type == intersections::IntersectionType::MISS || mat.material_type_ == MaterialType::DIFFUSE) break;

					if (mat.material_type_ == MaterialType::REFLECTIVE)
					{
						const auto new_dir = math::reflect(ray.direction_, result.intersection_normal);
						ray = intersections::Ray(result.intersection_point + result.intersection_normal * 0.0001f, new_dir);
					}
					else if (mat.material_type_ == MaterialType::REFRACTIVE)
					{
						auto refracted_dir = math::refract(ray.direction_, result.intersection_normal, mat.refraction_index_);
						
						if (refracted_dir == math::vec3(0.0f))
						{
							const auto new_dir = math::reflect(ray.direction_, result.intersection_normal);
							ray = intersections::Ray(result.intersection_point + result.intersection_normal * 0.0001f, new_dir);
							continue;
						}

						auto refracted_origin = result.intersection_point + ray.direction_ * 0.001f;
						auto refracted_ray = intersections::Ray(refracted_origin, refracted_dir);
						const auto& [refracted_result, refracted_material] = ShootRay(refracted_ray);
						refracted_dir = math::refract(refracted_ray.direction_, refracted_result.intersection_normal, 1.0f / refracted_material.refraction_index_);
						refracted_origin = refracted_result.intersection_point + refracted_ray.direction_ * 0.0001f;
						ray = intersections::Ray(refracted_origin, refracted_dir);
					}
				}

				if (result.type == intersections::IntersectionType::MISS)
				{
					result_color += color * weight;
				}
				else
				{
					for (const auto& light : lights_)
					{
						auto new_origin = result.intersection_point + result.intersection_normal * 0.0001f;
						auto new_dir = math::normalized(light.position - new_origin);
						auto new_ray = intersections::Ray(new_origin, new_dir);
						auto new_distance = math::distance(new_origin, light.position);

						const auto& [new_result, new_mat] = ShootRay(new_ray);

						if (new_result.type == intersections::IntersectionType::HIT && new_result.distance < new_distance)
						{
							result_color += mat.ambient_ * weight; shadowed++;
							//std::cout << "Hit light shadow" << std::endl;
							continue;
						}

						result_color += CalculatePointLighting(result, mat, light) * weight;

					}
				}
				
			}

			result_color[3] = 255.0f;

			buffer_->SetPixelf(x, y, result_color);
		}
	}
	std::cout << "shadowed: " << shadowed << std::endl;
	buffer_->SaveColorToFile("test.bmp");
}

std::pair<intersections::IntersectionResult, rendering::Material> rendering::Renderer::ShootRay(const intersections::Ray& ray) const
{
	Material hit_material;
	intersections::IntersectionResult hit_result;

	float depth = std::numeric_limits<float>::max();
	
	for (auto& geometry : scene_)
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
				hit_material = *(primitive->material_.get());
				hit_result = result;
			},
			geometry
		);
	}

	return std::make_pair(hit_result, hit_material);
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