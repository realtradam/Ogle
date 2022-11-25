#pragma once

// external libs
#include "GLFW/glfw3.h"

namespace Input {
	void process(GLFWwindow *window);
	int get_mouse_x();
	int get_mouse_y();
	bool get_mouse_click();
}
