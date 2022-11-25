#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "input.hpp"
#include "shader.hpp"
#include "batch.hpp"
#include "window.hpp"

#include <iostream>
#include <cmath>


int main() {
	Window::init(800, 600, "Ogle");

	Shader shader = Shader("src/shaders/default.vert", "src/shaders/default.frag");
	Batch batch = Batch();
	Texture texture = Texture("assets/awesomeface.png");

	// game loop
	while(!glfwWindowShouldClose(Window::get()))
	{
		Input::process(Window::get());

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();

		batch.drawRectangle(-0.5,-0.5,1.0,1.0,glm::vec4(0.3,0.3,1.0,1.0));
		batch.drawRectangle(0.5,0.5,1.0,1.0,glm::vec4(1.0,0.3,0.3,1.0));
		batch.drawRectangle(-0.5,0.5,1.0,1.0,glm::vec4(1.0,0.3,1.0,1.0));
		batch.drawRectangle(0.5,-0.5,1.0,1.0,glm::vec4(1.0,1.0,0.3,1.0));
		batch.drawTexture(texture,-0.5,-0.5,1.0,1.0,glm::vec4(1.0,1.0,1.0,0.3));
		batch.drawTexture(texture,0.5,0.5,1.0,1.0,glm::vec4(1.0,1.0,1.0,0.3));
		batch.drawTexture(texture,-0.5,0.5,1.0,1.0,glm::vec4(1.0,1.0,1.0,0.3));
		batch.drawTexture(texture,0.5,-0.5,1.0,1.0,glm::vec4(1.0,1.0,1.0,0.3));
		batch.drawTexture(texture,0.0,0.0,1.0,1.0,glm::vec4(1.0,1.0,1.0,0.5));

		batch.flush_batch(); // does the drawing


		glfwSwapBuffers(Window::get());
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

