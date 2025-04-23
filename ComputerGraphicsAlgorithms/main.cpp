#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif // !STB_IMAGE_WRITE_IMPLEMENTATION

#include <memory>

#include "Camera.h"
#include "io_utility/InputOutput.h"
#include "PixelBuffer.h"
#include "Preprocessor.h"
#include "Rasterizer.h"
#include "mesh/Cone.h"
#include "mesh/Sphere.h"

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
        math::to_radians(45.0f),
        1000.0f,
        0.1f);

    preprocessor->view_matrix_ = camera.UpdateViewMatrix();
    preprocessor->projection_matrix_ =  camera.ProjectionMatrix();
    preprocessor->model_matrix_ = math::mat4x4(1.0f);

    rasterizer.framebuffer_->ColorClear(color4(222, 121, 255, 255));
    rasterizer.framebuffer_->DepthClear(std::numeric_limits<float>::max());

    mesh::Cone cone(2.0f, 3.0f, 15);
    cone.GenerateMesh();

	mesh::Sphere sphere(3.0f, 25, 25);
	sphere.GenerateMesh();

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
		
        rotation += 0.0f;// dt * 20.0f;

		io.PollEvents();
		io.ClearGLBuffers();

		rasterizer.framebuffer_->ClearBuffers({12, 24, 64, 255}, std::numeric_limits<float>::max());

        preprocessor->view_matrix_ = camera.UpdateViewMatrix();
        
        auto rotation_matrix = math::matmul(math::rotation_matrix_x_deg(-24.0f), math::rotation_matrix_y_deg(16.0f));

		preprocessor->model_matrix_ = math::matmul(math::translation_matrix(4.0f, 2.0f, 0.0f), rotation_matrix);
        rasterizer.DrawMesh(cone);

        preprocessor->model_matrix_ = math::matmul(math::translation_matrix(-4.0f, -2.0f, 0.0f), rotation_matrix);
        rasterizer.DrawMesh(sphere);

        io.Draw(rasterizer.GetData(), GL_RGBA, GL_UNSIGNED_BYTE);
        
        if (io.GetKey(GLFW_KEY_W) == GLFW_PRESS)
        {
            camera.SetPosition(camera.position() + camera.forward() * dt * 10.0f);
            std::cout << camera.position() << std::endl;
        }

        if (io.GetKey(GLFW_KEY_S) == GLFW_PRESS)
        {
            camera.SetPosition(camera.position() - camera.forward() * dt * 10.0f);
            std::cout << camera.position() << std::endl;
        }

        if (io.GetKey(GLFW_KEY_A) == GLFW_PRESS)
        {
            camera.SetPosition(camera.position() - camera.right() * dt * 10.0f);
            std::cout << camera.position() << std::endl;
        }

        if (io.GetKey(GLFW_KEY_D) == GLFW_PRESS)
        {
            camera.SetPosition(camera.position() + camera.right() * dt * 10.0f);
            std::cout << camera.position() << std::endl;
        }

        if (io.GetKey(GLFW_KEY_Q) == GLFW_PRESS)
        {
            camera.SetPosition(camera.position() + camera.up() * dt * 10.0f);
            std::cout << camera.position() << std::endl;
            
        }

        if (io.GetKey(GLFW_KEY_E) == GLFW_PRESS)
        {
            camera.SetPosition(camera.position() - camera.up() * dt * 10.0f);
            std::cout << camera.position() << std::endl;
        }

        if (io.GetKey(GLFW_KEY_F) == GLFW_PRESS)
        {
            camera.SetPosition(camera.position() - camera.up() * dt * 10.0f);
            std::cout << "position: " << camera.position() << std::endl;
            std::cout << "right: " << camera.right() << std::endl;
            std::cout << "forward: " << camera.forward() << std::endl;
            std::cout << "up: " << camera.up() << std::endl;
        }

		io.SwapBuffers();  
    }

    rasterizer.framebuffer_->SaveColorToFile("image.bmp");

    return 0;
}