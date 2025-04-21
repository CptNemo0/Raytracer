#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif // !STB_IMAGE_WRITE_IMPLEMENTATION

#include <memory>

#include "Camera.h"
#include "InputOutput.h"
#include "PixelBuffer.h"
#include "Preprocessor.h"
#include "Rasterizer.h"

using namespace rtr;

int main(int argc, char** argv)
{
    io_utility::InputOutput io;
	if (io.Init("Rasterizer", 1280, 720)) return -1;

    auto preprocessor = std::make_shared<Preprocessor>(static_cast<float>(io.GetMode()->width), static_cast<float>(io.GetMode()->height));
    Rasterizer rasterizer(static_cast<std::uint32_t>(io.GetMode()->width), static_cast<std::uint32_t>(io.GetMode()->height), preprocessor);
    Camera camera(math::vec3(0.0f, 0.0f, 0.0f),
        math::vec3(0.0f, 0.0f, 1.0f),
        math::vec3(0.0f, 1.0f, 0.0f),
        static_cast<float>(io.GetMode()->width) / static_cast<float>(io.GetMode()->height),
        math::to_radians(90.0f),
        1000.0f,
        0.1f);

    preprocessor->view_matrix_ = camera.UpdateViewMatrix();
    preprocessor->projection_matrix_ = camera.ProjectionMatrix();
    preprocessor->model_matrix_ = math::mat4x4(1.0f);

    rasterizer.framebuffer_->ColorClear(color4(222, 121, 255, 255));
    rasterizer.framebuffer_->DepthClear(std::numeric_limits<float>::max());

    Triangle triangle1;
    triangle1.vertices_[0].position_ = math::vec3(-0.5f, -0.5f, 0.0f);
    triangle1.vertices_[1].position_ = math::vec3(0.0f, 0.5f, 0.0f);
    triangle1.vertices_[2].position_ = math::vec3(0.5f, -0.5f, 0.0f);

    Triangle triangle2;
    triangle2.vertices_[0].position_ = math::vec3(-0.5f, -0.5f, 0.0f);
    triangle2.vertices_[1].position_ = math::vec3(0.0f, 0.5f, 0.0f);
    triangle2.vertices_[2].position_ = math::vec3(0.5f, -0.5f, 0.0f);

    float time0 = 0;
	float time1 = 0;
	float dt = 0;
    float rotation = 0;
    float fps_idx = 100;

    while (!io.GetWindowShouldClose())
    {
        time1 = static_cast<float>(io.GetTime());
		dt = time1 - time0;
        time0 = time1;

        if (!fps_idx)
        {
            std::cout << 1.0f / dt << std::endl;
            fps_idx = 100;
        }
        fps_idx--;
		
		io.PollEvents();
		io.ClearGLBuffers();

		rasterizer.framebuffer_->ClearBuffers({12, 24, 64, 255}, std::numeric_limits<float>::max());
        
        preprocessor->model_matrix_ = math::mat4x4(1.0f);
        preprocessor->color_ = color4f(255.0f, 0.0f, 0.0f, 255.0f);
        rasterizer.DrawTriangle(triangle1);
        
        preprocessor->model_matrix_ = math::rotation_matrix_y_deg(rotation += dt * 30.0f);
        preprocessor->color_ = color4f(255.0f, 0.0f, 255.0f, 255.0f);
        rasterizer.DrawTriangle(triangle2);

        io.Draw(rasterizer.GetData(), GL_RGBA, GL_UNSIGNED_BYTE);
        
        if (io.GetKey(GLFW_KEY_W) == GLFW_PRESS)
        {
            camera.SetPosition(camera.position() + camera.forward() * dt * 10.0f);
            preprocessor->view_matrix_ = camera.UpdateViewMatrix();
        }

        if (io.GetKey(GLFW_KEY_S) == GLFW_PRESS)
        {
            camera.SetPosition(camera.position() - camera.forward() * dt * 10.0f);
            preprocessor->view_matrix_ = camera.UpdateViewMatrix();
        }

        if (io.GetKey(GLFW_KEY_A) == GLFW_PRESS)
        {
            camera.SetPosition(camera.position() - camera.right() * dt * 10.0f);
            preprocessor->view_matrix_ = camera.UpdateViewMatrix();
        }

        if (io.GetKey(GLFW_KEY_D) == GLFW_PRESS)
        {
            camera.SetPosition(camera.position() + camera.right() * dt * 10.0f);
            preprocessor->view_matrix_ = camera.UpdateViewMatrix();
        }

		io.SwapBuffers();  
    }

    rasterizer.framebuffer_->SaveColorToFile("image.bmp");

    return 0;
}