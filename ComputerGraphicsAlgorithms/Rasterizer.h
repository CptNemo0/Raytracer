#ifndef RASTERIZER_H
#define RASTERIZER_H

#include<array>
#include<memory>

#include "aliasing.h"
#include "PixelBuffer.h"
#include "raytracer_math.h"
#include "Triangle.h"
#include "Vertex.h"

class Rasterizer
{
public:
	std::unique_ptr<PixelBuffer> framebuffer_;
	Rasterizer(const std::uint32_t width, const std::uint32_t height);
	void DrawTriangle(const Triangle& tri);
};

#endif // !RASTERIZER_H