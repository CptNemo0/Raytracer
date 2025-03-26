#ifndef RASTERIZER_H
#define RASTERIZER_H

#include<array>
#include<memory>
#include "PixelBuffer.h"
#include "vec.h"
struct triangle
{
	std::array<math::vec3, 3> vertices;
};

class Rasterizer
{
public:
	std::unique_ptr<PixelBuffer> framebuffer_;
	Rasterizer(const std::uint32_t width, const std::uint32_t height);
	void DrawTriangle(const triangle& tri);
};

#endif // !RASTERIZER_H