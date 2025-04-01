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
    Rasterizer rasterizer(400, 300);
    rasterizer.framebuffer_->ColorClear(color4(222, 121, 255, 255));

    triangle tri;
    tri.vertices[0] = math::vec3(-1.1f, -1.0f, 0.0f);
    tri.vertices[1] = math::vec3(-1.0f, 1.0f, 0.0f);
    tri.vertices[2] = math::vec3(1.0f, 1.0f, 0.0f);
    rasterizer.DrawTriangle(tri);

    rasterizer.framebuffer_->SaveColorToFile("image.bmp");
    return 0;
}