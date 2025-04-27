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

		mesh::Triangle world_triangle = input;
		preprocessor_->TriangleLocal2World(world_triangle);

		mesh::Triangle view_space_triangle = world_triangle;
		preprocessor_->TriangleWorld2View(view_space_triangle);

		mesh::Triangle projection_triangle = input;
		preprocessor_->TriangleLocal2Screen(projection_triangle);

		TriangleRasterizationCache trc(projection_triangle);

		float left = std::numeric_limits<float>::max();
		float right = std::numeric_limits<float>::min();
		float top = std::numeric_limits<float>::max();
		float bot = std::numeric_limits<float>::min();

		for (const auto& vertex : projection_triangle.vertices_)
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
				const auto fx = static_cast<float>(x) + 0.5f;
				const auto fy = static_cast<float>(y) + 0.5f;
				if (!PixelInside(fx, fy, projection_triangle, trc)) continue;
				const auto [lambda1, lambda2, lambda3] = GetLambdas(fx, fy, projection_triangle, trc);

				float depth = lambda1 * projection_triangle.vertices_[0].position_[2] +
					          lambda2 * projection_triangle.vertices_[1].position_[2] +
					          lambda3 * projection_triangle.vertices_[2].position_[2];

				auto position = world_triangle.vertices_[0].position_ * lambda1 +
								world_triangle.vertices_[1].position_ * lambda2 +
					            world_triangle.vertices_[2].position_ * lambda3;

				auto normal = input.vertices_[0].normal_ * lambda1 +
								input.vertices_[1].normal_ * lambda2 +
								input.vertices_[2].normal_ * lambda3;

				if (!framebuffer_->DepthCheckExchange(x, y, depth)) continue;
				
				auto position4 = math::vec4(position.get(0), position.get(1), position.get(2), 1.0f);
				auto normal4 = math::vec4(normal.get(0) * 255.0f, normal.get(1) * 255.0f, normal.get(2) * 255.0f, 255.0f);

				framebuffer_->SetPixelf(x, y, normal4);
			}
		}
	}

	void Rasterizer::DrawMesh(const mesh::ProceduralMesh& mesh)
	{
		srand(time(0));	
		for (const auto& index : mesh.indices_)
		{
			preprocessor_->color_ = color4f(rand() % 255, rand() % 255, rand() % 255, 255.0f);
			mesh::Triangle tri
			(
				mesh.vertices_[index.get(0)],
				mesh.vertices_[index.get(1)],
				mesh.vertices_[index.get(2)]
			);
			DrawTriangle(tri);
		}
	}
	
	void* Rasterizer::GetData()
	{
		return reinterpret_cast<void*>(const_cast<color4*>(framebuffer_->ColorBuffer().data()));
	}
	
	void Rasterizer::DrawTriangleLightVertex(const mesh::Triangle& input, const math::ivec3 vidx, const std::vector<color3f>& colors)
	{
		const auto width = static_cast<float>(framebuffer_->Width());
		const auto height = static_cast<float>(framebuffer_->Height());
		auto& color_buffer = framebuffer_->ColorBuffer();

		mesh::Triangle projection_triangle = input;
		preprocessor_->TriangleLocal2Screen(projection_triangle);

		TriangleRasterizationCache trc(projection_triangle);

		float left = std::numeric_limits<float>::max();
		float right = std::numeric_limits<float>::min();
		float top = std::numeric_limits<float>::max();
		float bot = std::numeric_limits<float>::min();

		for (const auto& vertex : projection_triangle.vertices_)
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
				const auto fx = static_cast<float>(x) + 0.5f;
				const auto fy = static_cast<float>(y) + 0.5f;
				if (!PixelInside(fx, fy, projection_triangle, trc)) continue;
				const auto [lambda1, lambda2, lambda3] = GetLambdas(fx, fy, projection_triangle, trc);

				float depth = lambda1 * projection_triangle.vertices_[0].position_[2] +
					lambda2 * projection_triangle.vertices_[1].position_[2] +
					lambda3 * projection_triangle.vertices_[2].position_[2];

				if (!framebuffer_->DepthCheckExchange(x, y, depth)) continue;

				auto color = colors[vidx.get(0)] * lambda1 +
							 colors[vidx.get(1)] * lambda2 +
							 colors[vidx.get(2)] * lambda3;


				auto color4 = math::vec4(color.get(0), color.get(1) , color.get(2), 255.0f);

				framebuffer_->SetPixelf(x, y, color4);
			}
		}
	}

	void Rasterizer::DrawMeshLightVertex(const mesh::ProceduralMesh& mesh)
	{
		std::vector<color3f> vertex_colors;
		vertex_colors.reserve(mesh.vertices_.size());
		for (const auto& vertex : mesh.vertices_)
		{
			auto local_position4 = math::vec4(vertex.position_.get(0), vertex.position_.get(1), vertex.position_.get(2), 1.0f);
			auto world_position4 = math::transformed(preprocessor_->model_matrix_, local_position4);
			auto world_position = math::vec3(world_position4.get(0), world_position4.get(1), world_position4.get(2));
			auto normal = preprocessor_->FixNormal(vertex.normal_);
			
			color3f color = color3f(0.0f);

			for (const auto& light : lights_)
			{
				//color += math::vec3(normal.get(1) * 255.0f, normal.get(2) * 255.0f, normal.get(2) * 255.0f);
				color += light->CalculateColor(world_position, normal, math::vec3(0.0f, 0.0f, 0.0f));
			}

			color[0] = std::clamp(color[0], 0.0f, 255.0f);
			color[1] = std::clamp(color[1], 0.0f, 255.0f);
			color[2] = std::clamp(color[2], 0.0f, 255.0f);


			vertex_colors.push_back(color);
		}

		for (const auto& index : mesh.indices_)
		{
			mesh::Triangle tri
			(
				mesh.vertices_[index.get(0)],
				mesh.vertices_[index.get(1)],
				mesh.vertices_[index.get(2)]
			);
			DrawTriangleLightVertex(tri, index, vertex_colors);
		}
	}
}

