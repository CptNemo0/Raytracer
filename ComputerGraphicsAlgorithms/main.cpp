#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif // !STB_IMAGE_WRITE_IMPLEMENTATION

#include "PixelBuffer.h"
#include "Rasterizer.h"

int main(int argc, char** argv)
{
    Rasterizer rasterizer(1000, 1000);
    rasterizer.framebuffer_->ColorClear(color4(222, 121, 255, 255));

    Triangle triangle;
    triangle.vertices[0].position = math::vec3(0.0, -1.10f, 0.0f);
    triangle.vertices[1].position = math::vec3(-1.0f, 1.0f, 0.0f);
    triangle.vertices[2].position = math::vec3(1.0f, 1.0f, 0.0f);

    triangle.vertices[0].color = color4f(255.0f, 0.0f, 0.0f, 255.0f);
    triangle.vertices[1].color = color4f(0.0f, 255.0f, 0.0f, 255.0f);
    triangle.vertices[2].color = color4f(0.0f, 0.0f, 255.0f, 255.0f);
    
    rasterizer.DrawTriangle(triangle);

    rasterizer.framebuffer_->SaveColorToFile("image.bmp");
    return 0;
}