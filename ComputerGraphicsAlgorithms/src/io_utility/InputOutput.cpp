#include "io_utility/InputOutput.h"

namespace io_utility
{
    int InputOutput::InitGLFW(std::string_view  window_name, std::optional<int> width, std::optional<int> height)
    {
        int return_value = 0;

        if (!glfwInit())
        {
            return_value = -1;
        }

        monitor_ = glfwGetPrimaryMonitor();
        mode_ = (GLFWvidmode*)glfwGetVideoMode(monitor_);

        if (width.has_value())
        {
            mode_->width = width.value();
        }
		if (height.has_value())
		{
			mode_->height = height.value();
		}

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
        glfwWindowHint(GLFW_RED_BITS, mode_->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode_->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode_->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode_->refreshRate);
        
        if (width.has_value() || height.has_value())
        {
            window_ = glfwCreateWindow(mode_->width, mode_->height, window_name.data(), nullptr, nullptr);
        }
        else
        {
            window_ = glfwCreateWindow(mode_->width, mode_->height, window_name.data(), monitor_, nullptr);
        }

        if (window_ == nullptr)
        {
            glfwTerminate();
            return_value = -1;
        }

        glfwMakeContextCurrent(window_);
        
        // VSYNC
        glfwSwapInterval(0);    // OFF
        //glfwSwapInterval(1);  // ON
        return return_value;
    }

    int InputOutput::InitGlad()
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

    InputOutput::~InputOutput()
    {
		glfwDestroyWindow(window_);
		glfwTerminate();
    }
}