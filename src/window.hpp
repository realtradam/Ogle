
// external libs
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Window {
	GLFWwindow* get();
	int init(
			unsigned int width,
			unsigned int height,
			const char* title
			);
}
