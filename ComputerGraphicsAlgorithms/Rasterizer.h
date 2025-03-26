#ifndef RASTERIZER_H
#define RASTERIZER_H

#include<memory>
#include "PixelBuffer.h"
class Rasterizer
{
	std::unique_ptr<PixelBuffer> framebuffer_;

public:
	void DrawTriangle();
};

#endif // !RASTERIZER_H