#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif // !STB_IMAGE_WRITE_IMPLEMENTATION

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // !STB_IMAGE_IMPLEMENTATION

#ifndef STBI_NO_STDIO
#define STBI_NO_STDIO
#endif // !STBI_NO_STDIO


#include <memory>

#include "Camera.h"
#include "io_utility/InputOutput.h"
#include "PixelBuffer.h"
#include "Preprocessor.h"
#include "Rasterizer.h"
#include "mesh/Cone.h"
#include "mesh/Sphere.h"
#include "mesh/Torus.h"
#include "Texture.h"
using namespace rtr;

int main(int argc, char** argv)
{  
    io_utility::InputOutput io;
    if (io.Init("Rasterizer", 1280, 720)) return -1;

    auto preprocessor = std::make_shared<Preprocessor>(static_cast<float>(io.GetMode()->width), static_cast<float>(io.GetMode()->height));
    Rasterizer rasterizer(static_cast<std::uint32_t>(io.GetMode()->width), static_cast<std::uint32_t>(io.GetMode()->height), preprocessor);
    Camera camera(math::vec3(0.0f, 0.0f, -10.0f),
        math::vec3(0.0f, 0.0f, 1.0f),
        math::vec3(0.0f, 1.0f, 0.0f),
        static_cast<float>(io.GetMode()->width) / static_cast<float>(io.GetMode()->height),
        math::to_radians(45.0f),
        1000.0f,
        0.1f);

    preprocessor->view_matrix_ = camera.UpdateViewMatrix();
    preprocessor->projection_matrix_ = camera.ProjectionMatrix();
    preprocessor->model_matrix_ = math::mat4x4(1.0f);

    rasterizer.framebuffer_->ColorClear(color4(0, 0, 0, 255));
    rasterizer.framebuffer_->DepthClear(std::numeric_limits<float>::max());

    auto plight = std::make_shared<PointLight>(math::vec3(0.0f, 0.0f, -5.0f), 8.5f, math::vec3(165.0f, 50, 50.0f), [](float d) {return 1.0f / (0.5f * d + 1.0f); });
    auto dlight = std::make_shared<DirectionalLight>(math::vec3(1.0f, 0.0f, 0.0f), 8.5f, math::vec3(50.0f, 50.0f, 165.0f), [](float d) {return 1.0f / (0.25f * d + 1.0f); });
    rasterizer.lights_.push_back(plight);
    rasterizer.lights_.push_back(dlight);

    auto green_texture = std::make_unique<Texture>("green_texture.jpg");
    
    auto red_texture = std::make_unique<Texture>("red_texture.jpg");
    auto blue_texture = std::make_unique<Texture>("blue_texture.jpg");

    int precision = 25;

    mesh::Cone cone(2.25f, 2.0f, precision);
    cone.GenerateMesh();

    mesh::Torus torus(2.5f, 0.4f, precision, precision);
    torus.GenerateMesh();

    mesh::Sphere sphere(2.0f, precision, precision);
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

        rotation += dt * 20.0f;

        io.PollEvents();
        io.ClearGLBuffers();

        rasterizer.framebuffer_->ClearBuffers({ 0, 0, 0, 255 }, std::numeric_limits<float>::max());
        preprocessor->view_matrix_ = camera.UpdateViewMatrix();
        preprocessor->eye_position = camera.position();
        auto rotation_matrix = math::matmul(math::rotation_matrix_x_deg(rotation), math::rotation_matrix_y_deg(rotation));
        auto rrotation_matrix = math::matmul(math::rotation_matrix_x_deg(-rotation), math::rotation_matrix_y_deg(-rotation));

        preprocessor->model_matrix_ = math::matmul(math::translation_matrix(0.0f, 3.0f, 0.0f), rotation_matrix);
        preprocessor->ti_model_matrix = math::transposed(math::inverse(preprocessor->model_matrix_));
        rasterizer.DrawMeshLightPixel(sphere);

        preprocessor->model_matrix_ = math::matmul(math::translation_matrix(-6.0f, 3.0f, 0.0f), rotation_matrix);
        preprocessor->ti_model_matrix = math::transposed(math::inverse(preprocessor->model_matrix_));
        rasterizer.DrawMeshLightPixel(torus);

        preprocessor->model_matrix_ = math::matmul(math::translation_matrix(6.0f, 3.0f, 0.0f), rotation_matrix);
        preprocessor->ti_model_matrix = math::transposed(math::inverse(preprocessor->model_matrix_));
        rasterizer.DrawMeshLightPixel(cone);

        preprocessor->model_matrix_ = math::matmul(math::translation_matrix(0.0f, -3.0f, 0.0f), rrotation_matrix);
        preprocessor->ti_model_matrix = math::transposed(math::inverse(preprocessor->model_matrix_));
        rasterizer.DrawMeshLightVertex(sphere);

        preprocessor->model_matrix_ = math::matmul(math::translation_matrix(-6.0f, -3.0f, 0.0f), rrotation_matrix);
        preprocessor->ti_model_matrix = math::transposed(math::inverse(preprocessor->model_matrix_));
        rasterizer.DrawMeshLightVertex(torus);

        preprocessor->model_matrix_ = math::matmul(math::translation_matrix(6.0f, -3.0f, 0.0f), rrotation_matrix);
        preprocessor->ti_model_matrix = math::transposed(math::inverse(preprocessor->model_matrix_));
        rasterizer.DrawMeshLightVertex(cone);

        
        preprocessor->model_matrix_ = math::matmul(math::translation_matrix(0.0f, -9.0f, 0.0f), rotation_matrix);
        preprocessor->ti_model_matrix = math::transposed(math::inverse(preprocessor->model_matrix_));
        preprocessor->texture_ = red_texture.get();
        rasterizer.DrawMeshLightPixelTextured(sphere);

        preprocessor->model_matrix_ = math::matmul(math::translation_matrix(-6.0f, -9.0f, 0.0f), rotation_matrix);
        preprocessor->ti_model_matrix = math::transposed(math::inverse(preprocessor->model_matrix_));
        preprocessor->texture_ = blue_texture.get();
        rasterizer.DrawMeshLightPixelTextured(torus);

        preprocessor->model_matrix_ = math::matmul(math::translation_matrix(6.0f, -9.0f, 0.0f), rotation_matrix);
        preprocessor->ti_model_matrix = math::transposed(math::inverse(preprocessor->model_matrix_));
        preprocessor->texture_ = green_texture.get();
        rasterizer.DrawMeshLightPixelTextured(cone);

        preprocessor->model_matrix_ = math::matmul(math::translation_matrix(0.0f, -15.0f, 0.0f), rrotation_matrix);
        preprocessor->ti_model_matrix = math::transposed(math::inverse(preprocessor->model_matrix_));
        preprocessor->texture_ = red_texture.get();
        rasterizer.DrawMeshTextured(sphere);

        preprocessor->model_matrix_ = math::matmul(math::translation_matrix(-6.0f, -15.0f, 0.0f), rrotation_matrix);
        preprocessor->ti_model_matrix = math::transposed(math::inverse(preprocessor->model_matrix_));
        preprocessor->texture_ = blue_texture.get();
        rasterizer.DrawMeshTextured(torus);

        preprocessor->model_matrix_ = math::matmul(math::translation_matrix(6.0f, -15.0f, 0.0f), rrotation_matrix);
        preprocessor->ti_model_matrix = math::transposed(math::inverse(preprocessor->model_matrix_));
        preprocessor->texture_ = green_texture.get();
        rasterizer.DrawMeshTextured(cone);

        io.Draw(rasterizer.GetData(), GL_RGBA, GL_UNSIGNED_BYTE);

#pragma region Steering

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

#pragma endregion Steering

        io.SwapBuffers();
    }

    rasterizer.framebuffer_->SaveColorToFile("image.bmp");

    return 0;
}
