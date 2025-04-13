#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif // !STB_IMAGE_WRITE_IMPLEMENTATION

#include "PixelBuffer.h"
#include "Rasterizer.h"
#include "Camera.h"

int main(int argc, char** argv)
{
	Camera camera;
	camera.SetPosition(math::vec3(0.0f, 0.0f, 0.0f));
    camera.LookAt(math::vec3(0.0f, 0.0f, 0.0f), math::vec3(0.0f, 1.0f, 0.0f));
    const auto view_matrix = camera.UpdateViewMatrix();

    Rasterizer rasterizer(2000, 2000);
    rasterizer.framebuffer_->ColorClear(color4(222, 121, 255, 255));
    rasterizer.framebuffer_->DepthClear(std::numeric_limits<float>::max());
    Triangle triangle1;
    triangle1.vertices[0].position = math::vec3(0.0f, -0.5f, 0.0f);
    triangle1.vertices[1].position = math::vec3(-0.5f, 0.0f, 0.0f);
    triangle1.vertices[2].position = math::vec3(0.0f, 0.5f, 0.0f);

    triangle1.vertices[0].color = color4f(0.0f, 0.0f, 255.0f, 255.0f);
    triangle1.vertices[1].color = color4f(0.0f, 255.0f, 0.0f, 255.0f);
    triangle1.vertices[2].color = color4f(0.0f, 0.0f, 255.0f, 255.0f);
    
    Triangle triangle2;
    triangle2.vertices[0].position = math::vec3(0.0f, -0.50f, 0.0f);
    triangle2.vertices[1].position = math::vec3(0.0f, 0.5f, 0.0f);
    triangle2.vertices[2].position = math::vec3(0.5f, 0.0f, 0.0f);

    triangle2.vertices[0].color = color4f(255.0f, 0.0f, 0.0f, 255.0f);
    triangle2.vertices[1].color = color4f(255.0f, 0.0f, 0.0f, 255.0f);
    triangle2.vertices[2].color = color4f(0.0f, 255.0f, 0.0f, 255.0f);

    Triangle triangle3;
    triangle3.vertices[0].position = math::vec3(0.5f, 0.0f, 0.0f);
    triangle3.vertices[1].position = math::vec3(0.0f, 0.5f, 0.0f);
    triangle3.vertices[2].position = math::vec3(1.0f, 0.5f, 0.0f);

    triangle3.vertices[0].color = color4f(0.0f, 0.0f, 255.0f, 255.0f);
    triangle3.vertices[1].color = color4f(0.0f, 0.0f, 255.0f, 255.0f);
    triangle3.vertices[2].color = color4f(0.0f, 255.0f, 0.0f, 255.0f);

    Triangle triangle4;
    triangle4.vertices[0].position = math::vec3(-0.5f, 0.0f, 0.0f);
    triangle4.vertices[1].position = math::vec3(-1.0f, 0.5f, 0.0f);
    triangle4.vertices[2].position = math::vec3(0.0f, 0.5f, 0.0f);

    triangle4.vertices[0].color = color4f(255.0f, 0.0f, 255.0f, 255.0f);
    triangle4.vertices[1].color = color4f(255.0f, 0.0f, 255.0f, 255.0f);
    triangle4.vertices[2].color = color4f(255.0f, 255.0f, 0.0f, 255.0f);

    Triangle triangle5;
    triangle5.vertices[0].position = math::vec3(-0.3f, 0.0f, -5.0f);
    triangle5.vertices[1].position = math::vec3(-0.8f, 0.7f, 5.0f);
    triangle5.vertices[2].position = math::vec3(0.2f, 0.7f, 0.0f);

    triangle5.vertices[0].color = color4f(0.0f, 255.0f, 255.0f, 255.0f);
    triangle5.vertices[1].color = color4f(0.0f, 255.0f, 255.0f, 255.0f);
    triangle5.vertices[2].color = color4f(0.0f, 255.0f, 0.0f, 255.0f);

    rasterizer.DrawTriangle(triangle5, view_matrix);
    rasterizer.DrawTriangle(triangle1, view_matrix);
    rasterizer.DrawTriangle(triangle2, view_matrix);
    rasterizer.DrawTriangle(triangle3, view_matrix);
    rasterizer.DrawTriangle(triangle4, view_matrix);

    rasterizer.framebuffer_->SaveColorToFile("image.bmp");
    return 0;
}