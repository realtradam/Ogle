
// external libs
#include "GLFW/glfw3.h"

// project headers
#include "input.hpp"

namespace Ogle
{
	namespace Input
	{
		namespace {
			int mouse_x;
			int mouse_y;
			bool mouse_click;
		}
		void process(GLFWwindow *window)
		{
			if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
			else
			{
				double _mouse_x, _mouse_y;
				glfwGetCursorPos(window, &_mouse_x, &_mouse_y);
				mouse_x = (int)_mouse_x;
				mouse_y = (int)_mouse_y;
				if(GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
					mouse_click = true;
				else
					mouse_click = false;
			}
		}

		int get_mouse_x()
		{
			return mouse_x;
		}
		int get_mouse_y()
		{
			return mouse_y;
		}
		bool get_mouse_click()
		{
			return mouse_click;
		}
	}
}
