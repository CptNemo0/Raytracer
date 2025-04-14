#ifndef RASTERIZER_H
#define RASTERIZER_H

#include<array>
#include<memory>

#include "aliasing.h"
#include "PixelBuffer.h"
#include "raytracer_math.h"
#include "Triangle.h"
#include "Vertex.h"
#include "Preprocessor.h"

class Rasterizer
{
public:
	std::unique_ptr<PixelBuffer> framebuffer_;
	std::shared_ptr<Preprocessor> preprocessor_;
	Rasterizer(const std::uint32_t width, const std::uint32_t height, std::shared_ptr<Preprocessor> preprocessor);
	void DrawTriangle(const Triangle& tri);
};

#endif // !RASTERIZER_H