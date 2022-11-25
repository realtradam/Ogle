#include "input.hpp"
#include "GLFW/glfw3.h"

namespace Input
{
	void process(GLFWwindow *window)
	{
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}
}
