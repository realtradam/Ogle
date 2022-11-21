#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input.h"
#include "shader.hpp"

#include <iostream>
#include <cmath>
//#include <unistd.h> // use to print working directory
//#include <stdio.h>

float vertices[] = {
	// positions		// colors
	0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // top right
	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};  

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main() {
	//printf("Current working dir: %s\n", get_current_dir_name());
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

	unsigned int VBO, VAO, EBO;
	glGenBuffers(1, &VBO); // generate the buffer
	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO); // generate array
	glBindVertexArray(VAO); // bind array to apply "settings" to it

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind(activate) the buffer to the ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // upload the data

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // configure how the vertex array looks
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // configure how the vertex array looks
	glEnableVertexAttribArray(1);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode

	//{
	//	int nrAttributes;
	//	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	//	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	//}

	// game loop
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//glUseProgram(shaderProgram); // this will activate the shader and use them for all subsequent shader and render calls
		shader.use();

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUniform4f(vertexColorLocation, 1.0f - greenValue, greenValue, (greenValue / 2.0f) + 0.25f, 1.0f);
		shader.set4f("ourColor", 1.0f - greenValue, greenValue, (greenValue / 2.0f) + 0.25f, 1.0f);

		glBindVertexArray(VAO); // activate the preconfigured settings
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // :)
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

