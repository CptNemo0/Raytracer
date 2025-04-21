#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H
#include <optional>
#include <string>

#include "glad.h"
#include <GLFW/glfw3.h>

namespace io_utility
{	
	class InputOutput
	{
	private:
		GLFWwindow* window_;
		GLFWmonitor* monitor_;
		GLFWvidmode* mode_;
	public:
		InputOutput() = default;
		~InputOutput();
		int InitGLFW(const std::string& window_name, std::optional<int> width = std::nullopt, std::optional<int> height = std::nullopt);
		int InitGlad();

		inline GLFWwindow* GetWindow() 
		{
			return window_;
		}
		inline GLFWmonitor* GetMonitor() 
		{
			return monitor_;
		}
		inline GLFWvidmode* GetMode() 
		{
			return mode_;
		}

		inline void SwapBuffers()
		{
			glfwSwapBuffers(window_);
		}

		inline void PollEvents() const
		{
			glfwPollEvents();
		}

		inline bool GetWindowShouldClose() const
		{
			return glfwWindowShouldClose(window_);
		}

		inline float GetTime() const 
		{
			return static_cast<float>(glfwGetTime());
		}

		inline int GetKey(int key) const
		{
			return glfwGetKey(window_, key);
		}

		inline void Draw(const void* buffer, const int mode, const int type) const
		{
			glDrawPixels(mode_->width,
						 mode_->height,
						 mode,
					     type,
						 buffer);
		}

		inline void ClearGLBuffers() const
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	};
}

#endif // !INPUT_OUTPUT_H

