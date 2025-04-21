#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif // !STB_IMAGE_WRITE_IMPLEMENTATION

#include "PixelBuffer.h"
#include "Rasterizer.h"
#include "Camera.h"
#include "Preprocessor.h"
#include <memory>
#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

using namespace rtr;


int InitGLFW(GLFWwindow*& window, GLFWmonitor*& monitor, GLFWvidmode*& mode, const std::string& window_name)
{
    int return_value = 0;
    if (!glfwInit())
    {
        return_value = -1;
    }

    monitor = glfwGetPrimaryMonitor();
    mode = (GLFWvidmode*)glfwGetVideoMode(monitor);

    //SET CUSTOM RESOLUTION
    mode->width = 1280;
    mode->height = 720;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    window = glfwCreateWindow(mode->width, mode->height, window_name.c_str(), nullptr, nullptr);

    if (window == nullptr)
    {
        glfwTerminate();
        return_value = -1;
    }

    glfwMakeContextCurrent(window);
     glfwSwapInterval( 0 );
    // VSYNC
    // glfwSwapInterval(1);
    return return_value;
}

inline int InitGlad()
{
    int return_value = 0;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEBUG_OUTPUT);
    glRasterPos2i(-1, -1); // Lower-left corner in NDC
    //glDebugMessageCallback(MessageCallback, 0);
    return return_value;
}

int main(int argc, char** argv)
{
	GLFWwindow* window; 
	GLFWmonitor* monitor;
    GLFWvidmode* mode;

	InitGLFW(window, monitor, mode, "Rasterizer");
	InitGlad();

    auto preprocessor = std::make_shared<Preprocessor>(static_cast<float>(mode->width), static_cast<float>(mode->height));
    Rasterizer rasterizer(static_cast<std::uint32_t>(mode->width), static_cast<std::uint32_t>(mode->height), preprocessor);
    Camera camera(math::vec3(0.0f, 0.0f, 0.0f),
        math::vec3(0.0f, 0.0f, 1.0f),
        math::vec3(0.0f, 1.0f, 0.0f),
        1.0f,
        math::to_radians(90.0f),
        1000.0f,
        0.1f);

    preprocessor->view_matrix_ = camera.UpdateViewMatrix();
    preprocessor->projection_matrix_ = camera.ProjectionMatrix();
    preprocessor->model_matrix_ = math::mat4x4(1.0f);

    rasterizer.framebuffer_->ColorClear(color4(222, 121, 255, 255));
    rasterizer.framebuffer_->DepthClear(std::numeric_limits<float>::max());

    Triangle triangle1;
    triangle1.vertices[0].position = math::vec3(-0.5f, -0.5f, 0.0f);
    triangle1.vertices[1].position = math::vec3(0.0f, 0.5f, 0.0f);
    triangle1.vertices[2].position = math::vec3(0.5f, -0.5f, 0.0f);

    Triangle triangle2;
    triangle2.vertices[0].position = math::vec3(-0.5f, -0.5f, 0.0f);
    triangle2.vertices[1].position = math::vec3(0.0f, 0.5f, 0.0f);
    triangle2.vertices[2].position = math::vec3(0.5f, -0.5f, 0.0f);

    float time0 = 0;
	float time1 = 0;
	float dt = 0;

    float rotation = 0;

    float fps_idx = 100;

    while (!glfwWindowShouldClose(window))
    {
        time0 = time1;
        time1 = static_cast<float>(glfwGetTime());
		dt = time1 - time0;


		rotation += dt * 10.0f;
        
        if (!fps_idx)
        {
            std::cout << 1.0f / dt << std::endl;
            fps_idx = 100;
        }
        fps_idx--;
		
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		rasterizer.framebuffer_->ClearBuffers({12, 24, 64, 255}, std::numeric_limits<float>::max());
        
        preprocessor->model_matrix_ = math::mat4x4(1.0f);
        preprocessor->color_ = color4f(255.0f, 0.0f, 0.0f, 255.0f);
        rasterizer.DrawTriangle(triangle1);
        
        preprocessor->model_matrix_ = math::rotation_matrix_y_deg(rotation);
        preprocessor->color_ = color4f(255.0f, 0.0f, 255.0f, 255.0f);
        rasterizer.DrawTriangle(triangle2);

        glDrawPixels(rasterizer.framebuffer_->Width(),
                          rasterizer.framebuffer_->Height(), 
                          GL_RGBA, 
                          GL_UNSIGNED_BYTE, 
                          reinterpret_cast<void*>(const_cast<color4*>(rasterizer.framebuffer_->ColorBuffer().data()))
        );
        
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camera.SetPosition(camera.position() + camera.forward() * dt * 10.0f);
            preprocessor->view_matrix_ = camera.UpdateViewMatrix();
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            camera.SetPosition(camera.position() - camera.forward() * dt * 10.0f);
            preprocessor->view_matrix_ = camera.UpdateViewMatrix();
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            camera.SetPosition(camera.position() - camera.right() * dt * 10.0f);
            preprocessor->view_matrix_ = camera.UpdateViewMatrix();
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            camera.SetPosition(camera.position() + camera.right() * dt * 10.0f);
            preprocessor->view_matrix_ = camera.UpdateViewMatrix();
        }

        glfwSwapBuffers(window);
    }


    rasterizer.framebuffer_->SaveColorToFile("image.bmp");

    return 0;
}