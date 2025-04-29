#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "raytracer_math.h"
#include "ColorBuffer.h"
#include "VertexProcessor.h"
#include "algorithm"
#include "Vertex.h"
#include "Light.h"
#include "vector"

class Triangle
{

public:
    Triangle(const math::vec3& v0, const math::vec3& v1, const math::vec3& v2)
    {
        /*auto isClockwise = [](const math::vec2 a, const math::vec2 b, const math::vec2 c) {
            return (b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0]) > 0;
        };

        if (isClockwise(v0, v1, v2)) {
            v0_ = v0;
            v1_ = v1;
            v2_ = v2;
        } else {
            v0_ = v0;
            v1_ = v2;
            v2_ = v1;
		}*/

		v0_ = v0;
		v1_ = v1;
		v2_ = v2;
		color0_ = Color4(255, 0, 0, 255);
		color1_ = Color4(0, 255, 0, 255);
		color2_ = Color4(0, 0, 255, 255);
    }
	

	void ToScreenCoordinates(int screenWidth, int screenHeight)
	{
		v0_[0] = float((v0_[0] + 1.0f) * 0.5f * screenWidth);
		v0_[1] = float((1.0f - v0_[1]) * 0.5f * screenHeight);

		v1_[0] = float((v1_[0] + 1.0f) * 0.5f * screenWidth);
		v1_[1] = float((1.0f - v1_[1]) * 0.5f * screenHeight);

		v2_[0] = float((v2_[0] + 1.0f) * 0.5f * screenWidth);
		v2_[1] = float((1.0f - v2_[1]) * 0.5f * screenHeight);
	}

	void SetColors(const Color4& color0, const Color4& color1, const Color4& color2)
	{
		color0_ = color0;
		color1_ = color1;
		color2_ = color2;
	}

    void SetColorsf(const math::vec3& color0, const math::vec3& color1, const math::vec3& color2)  
    {  
       color0_ = Color4(static_cast<unsigned char>(color0[0] * 255.0f),  
                        static_cast<unsigned char>(color0[1] * 255.0f),
                        static_cast<unsigned char>(color0[2] * 255.0f),
                        255);  

       color1_ = Color4(static_cast<unsigned char>(color1[0] * 255.0f),
                        static_cast<unsigned char>(color1[1] * 255.0f),
                        static_cast<unsigned char>(color1[2] * 255.0f),
                        255);  

       color2_ = Color4(static_cast<unsigned char>(color2[0] * 255.0f),
                        static_cast<unsigned char>(color2[1] * 255.0f),
                        static_cast<unsigned char>(color2[2] * 255.0f),
                        255);  
    }
	void SetColor0(const Color4& color) { color0_ = color; }
	void SetColor1(const Color4& color) { color1_ = color; }
	void SetColor2(const Color4& color) { color2_ = color; }

	Color4 FloatToColor4(const math::vec3& color)
	{
		return Color4(
			static_cast<unsigned char>(std::clamp(color[0] * 255.0f, 0.0f, 255.0f)),
			static_cast<unsigned char>(std::clamp(color[1] * 255.0f, 0.0f, 255.0f)),
			static_cast<unsigned char>(std::clamp(color[2] * 255.0f, 0.0f, 255.0f)),
			255
		);
	}

	bool isLeft(const math::vec2& v1, const math::vec2& v2, const math::vec2& p) const
	{
		return (v1[0] - v2[0]) * (p[1] - v1[1]) - (v1[1] - v2[1]) * (p[0] - v1[0]) < 0;
	}

	bool isInsideTopLeft(const math::vec2& p) const
	{
		float w0 = (v1_[0] - v0_[0]) * (p[1] - v0_[1]) - (v1_[1] - v0_[1]) * (p[0] - v0_[0]);
		float w1 = (v2_[0] - v1_[0]) * (p[1] - v1_[1]) - (v2_[1] - v1_[1]) * (p[0] - v1_[0]);
		float w2 = (v0_[0] - v2_[0]) * (p[1] - v2_[1]) - (v0_[1] - v2_[1]) * (p[0] - v2_[0]);

		// top-left edges detection
		int dx01 = (int)(v1_[0] - v0_[0]);
		int dy01 = (int)(v1_[1] - v0_[1]);
		int dx12 = (int)(v2_[0] - v1_[0]);
		int dy12 = (int)(v2_[1] - v1_[1]);
		int dx20 = (int)(v0_[0] - v2_[0]);
		int dy20 = (int)(v0_[1] - v2_[1]);

		bool t01 = (dy01 < 0 || (dy01 == 0 && dx01 > 0));
		bool t12 = (dy12 < 0 || (dy12 == 0 && dx12 > 0));
		bool t20 = (dy20 < 0 || (dy20 == 0 && dx20 > 0));

		return
			(w0 > 0 || (w0 == 0 && t01)) &&
			(w1 > 0 || (w1 == 0 && t12)) &&
			(w2 > 0 || (w2 == 0 && t20));
	}

	void ApplyProjection(const math::mat4x4& proj)
	{
		auto projectVertex = [&proj](math::vec3& v) {
			math::vec4 v4 = { v[0], v[1], v[2], 1.0f };
			math::vec4 transformed = math::transformed(proj, v4);

			// perspective divide
			if (transformed[3] != 0.0f)
			{
				transformed[0] /= transformed[3];
				transformed[1] /= transformed[3];
				transformed[2] /= transformed[3];
			}

			v = { transformed[0], transformed[1], transformed[2] };
			};

		projectVertex(v0_);
		projectVertex(v1_);
		projectVertex(v2_);
	}


	void drawTriangle(buffer::ColorBuffer& buffer, VertexProcessor& processor)
	{
	/*auto projectionMatrix = math::projection_matrix(90.0f, buffer.width_ /  buffer.height_, 0.1f, 100.0f);

		ApplyProjection(projectionMatrix);
		projectionMatrix.log();

		std::cout << "Projected vertices:\n";
		std::cout << "v0: " << v0_[0] << ", " << v0_[1] << ", " << v0_[2] << "\n";
		std::cout << "v1: " << v1_[0] << ", " << v1_[1] << ", " << v1_[2] << "\n";
		std::cout << "v2: " << v2_[0] << ", " << v2_[1] << ", " << v2_[2] << "\n";

		ToScreenCoordinates(buffer.width_, buffer.height_);*/

		processor.TriangleLocalToScreen(v0_, v1_, v2_, buffer.width_, buffer.height_);
		

		float minx = std::min({ v0_[0], v1_[0], v2_[0] });
		float maxx = std::max({ v0_[0], v1_[0], v2_[0] });
		float miny = std::min({ v0_[1], v1_[1], v2_[1] });
		float maxy = std::max({ v0_[1], v1_[1], v2_[1] });

		minx = std::fmaxf(minx, 0);
		maxx = std::fminf(maxx, buffer.GetWidth() - 1);
		miny = std::fmaxf(miny, 0);
		maxy = std::fminf(maxy, buffer.GetHeight() - 1);

		auto dx12 = (v1_[0] - v0_[0]);
		auto dy12 = (v1_[1] - v0_[1]);
		auto dx23 = (v2_[0] - v1_[0]);
		auto dy23 = (v2_[1] - v1_[1]);
		auto dx31 = (v0_[0] - v2_[0]);
		auto dy31 = (v0_[1] - v2_[1]);

		//Top-Left
		bool t01 = (dy12 < 0 || (dy12 == 0 && dx12 > 0));
		bool t12 = (dy23 < 0 || (dy23 == 0 && dx23 > 0));
		bool t20 = (dy31 < 0 || (dy31 == 0 && dx31 > 0));



		for (int i = minx; i <= maxx; i++) {

			for (int j = miny; j <= maxy; j++)
			{
				math::vec2 p = { i + 0.5f, j + 0.5f};
				if (isInsideTopLeft(p))
				{
					float denom = (v1_[1] - v2_[1]) * (v0_[0] - v2_[0]) + (v2_[0] - v1_[0]) * (v0_[1] - v2_[1]);
					float lambda1 = ((v1_[1] - v2_[1]) * (p[0] - v2_[0]) + (v2_[0] - v1_[0]) * (p[1] - v2_[1])) / denom;
					float lambda2 = ((v2_[1] - v0_[1]) * (p[0] - v2_[0]) + (v0_[0] - v2_[0]) * (p[1] - v2_[1])) / denom;
					float lambda3 = 1.0f - lambda1 - lambda2;

					float z = lambda1 * v0_[2] + lambda2 * v1_[2] + lambda3 * v2_[2];

					if (z > buffer.GetColorDepth(i, j)) {
						buffer.SetColorDepth(i, j, z);

						Color4 color;
						color[0] = (lambda1 * color0_[0] + lambda2 * color1_[0] + lambda3 * color2_[0]);
						color[1] = (lambda1 * color0_[1] + lambda2 * color1_[1] + lambda3 * color2_[1]);
						color[2] = (lambda1 * color0_[2] + lambda2 * color1_[2] + lambda3 * color2_[2]);
						color[3] = (lambda1 * color0_[3] + lambda2 * color1_[3] + lambda3 * color2_[3]);

						buffer.SetColor(i, j, color);
					}
				}
			}
		}
	}

	void drawTrianglePixelLight(buffer::ColorBuffer& buffer, VertexProcessor& processor, std::vector<std::shared_ptr<Light>> lights, std::vector<math::vec3> N)
	{
		processor.TriangleLocalToScreen(v0_, v1_, v2_, buffer.width_, buffer.height_);

		float minx = std::min({ v0_[0], v1_[0], v2_[0] });
		float maxx = std::max({ v0_[0], v1_[0], v2_[0] });
		float miny = std::min({ v0_[1], v1_[1], v2_[1] });
		float maxy = std::max({ v0_[1], v1_[1], v2_[1] });

		minx = std::fmaxf(minx, 0);
		maxx = std::fminf(maxx, buffer.GetWidth() - 1);
		miny = std::fmaxf(miny, 0);
		maxy = std::fminf(maxy, buffer.GetHeight() - 1);

		float denom = (v1_[1] - v2_[1]) * (v0_[0] - v2_[0]) + (v2_[0] - v1_[0]) * (v0_[1] - v2_[1]);

		for (int i = minx; i <= maxx; i++) {
			for (int j = miny; j <= maxy; j++) {
				math::vec2 p = { i + 0.5f, j + 0.5f };
				if (isInsideTopLeft(p))
				{
					float lambda1 = ((v1_[1] - v2_[1]) * (p[0] - v2_[0]) + (v2_[0] - v1_[0]) * (p[1] - v2_[1])) / denom;
					float lambda2 = ((v2_[1] - v0_[1]) * (p[0] - v2_[0]) + (v0_[0] - v2_[0]) * (p[1] - v2_[1])) / denom;
					float lambda3 = 1.0f - lambda1 - lambda2;

					float z = lambda1 * v0_[2] + lambda2 * v1_[2] + lambda3 * v2_[2];

					if (z > buffer.GetColorDepth(i, j)) {
						buffer.SetColorDepth(i, j, z);

						math::vec3 position = v0_ * lambda1 + v1_ * lambda2 + v2_ * lambda3;

						math::vec3 normal = N[0] * lambda1 + N[1] * lambda2 + N[2] * lambda3;

						math::vec3 color(0.0f, 0.0f, 0.0f);

						Fragment fragment(position, normal);
						for (auto& light : lights)
						{
							color += light->calculate(fragment, processor.eyePosition_);
						}

						color[0] = std::clamp(color[0], 0.0f, 255.0f);
						color[1] = std::clamp(color[1], 0.0f, 255.0f);
						color[2] = std::clamp(color[2], 0.0f, 255.0f);

						Color4 color4 = FloatToColor4(color);

						buffer.SetColor(i, j, color4);
					}
				}
			}
		}
	}

private:
	math::vec3 v0_;
	math::vec3 v1_;
	math::vec3 v2_;

	std::array<Vertex, 3> vertices_;



	Color4 color0_;
	Color4 color1_;
	Color4 color2_;
};
#endif // TRIANGLE_H