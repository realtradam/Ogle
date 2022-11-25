
// external libs
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// project headers
#include "window.hpp"

// std libs
#include <iostream>

namespace Window {
	namespace { // private
		GLFWwindow* window;

		void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	}

	GLFWwindow* get()
	{
		return window;
	}

	int init(
			unsigned int width,
			unsigned int height,
			const char* title
			)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 4.6 is highest, but lets use 3.3 for compatability
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		
		glfwSwapInterval(1);

		window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to init GLAD" << std::endl;
			return -1;
		}

		glViewport(0, 0, width, height);

		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}
}
