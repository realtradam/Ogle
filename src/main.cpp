#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "input.hpp"
#include "shader.hpp"
#include "batch.hpp"

#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 4.6 is highest
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Ogle", NULL, NULL);
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

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader shader = Shader("src/shaders/default.vert", "src/shaders/default.frag");


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode

	Batch batch = Batch();
	Texture texture = Texture("assets/awesomeface.png");
	shader.use();

	float pi = 2.0f * acos(0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// game loop
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		shader.use();

		batch.drawRectangle(
				-0.5,
				-0.5,
				1.0,
				1.0,
				glm::vec4(0.3,0.3,1.0,1.0)
				);
		batch.drawRectangle(
				0.5,
				0.5,
				1.0,
				1.0,
				glm::vec4(1.0,0.3,0.3,1.0)
				);
		batch.drawRectangle(
				-0.5,
				0.5,
				1.0,
				1.0,
				glm::vec4(1.0,0.3,1.0,1.0)
				);
		batch.drawRectangle(
				0.5,
				-0.5,
				1.0,
				1.0,
				glm::vec4(1.0,1.0,0.3,1.0)
				);
		batch.drawTexture(
				texture,
				-0.5,
				-0.5,
				1.0,
				1.0,
				glm::vec4(1.0,1.0,1.0,0.3)
				);
		batch.drawTexture(
				texture,
				0.5,
				0.5,
				1.0,
				1.0,
				glm::vec4(1.0,1.0,1.0,0.3)
				);
		batch.drawTexture(
				texture,
				-0.5,
				0.5,
				1.0,
				1.0,
				glm::vec4(1.0,1.0,1.0,0.3)
				);
		batch.drawTexture(
				texture,
				0.5,
				-0.5,
				1.0,
				1.0,
				glm::vec4(1.0,1.0,1.0,0.3)
				);
		batch.drawTexture(
				texture,
				0.0,
				0.0,
				1.0,
				1.0,
				glm::vec4(1.0,1.0,1.0,0.5)
				);

		batch.flush_batch(); // does the drawing


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

