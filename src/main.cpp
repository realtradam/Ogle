#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "input.hpp"
#include "shader.hpp"
#include "batch.hpp"
#include "window.hpp"
#include "random.hpp"

#include <iostream>
#include <cmath>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef struct Bunny {
	glm::vec2 position;
	glm::vec2 speed;
	glm::vec4 color;
} Bunny;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;


int main() {
	Window::init(SCREEN_WIDTH, SCREEN_HEIGHT, "Ogle");

	Shader shader = Shader("src/shaders/default.vert", "src/shaders/default.frag");
	Batch batch = Batch(1024 * 8);
	Texture texture = Texture("assets/wabbit_alpha.png");

	glm::mat4 transform = glm::ortho(0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, 0.1f, 100.0f);
	shader.use();
	shader.setMatrix4fv("transform", transform);

	auto start = std::chrono::high_resolution_clock::now();
	auto stop = std::chrono::high_resolution_clock::now();

	std::vector<Bunny> bunnies = std::vector<Bunny>{};
	const int MAX_BUNNIES = 50000;

	// game loop
	while(!glfwWindowShouldClose(Window::get()))
	{
		start = std::chrono::high_resolution_clock::now();
		Input::process(Window::get());

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();

		if(Input::get_mouse_click())
		{
			Bunny new_bunny;
			for (int i =0; i < 100; i++)
			{
				if (bunnies.size() < MAX_BUNNIES)
				{
					new_bunny = (Bunny){
						glm::vec2(Input::get_mouse_x(), Input::get_mouse_y()),
							glm::vec2((float)Random::get_value(-250, 250)/60.0f, (float)Random::get_value(-250, 250)/60.0f),
							glm::vec4(
									Random::get_value(50, 240) / 255.0,
									Random::get_value(50, 240) / 255.0,
									Random::get_value(100, 240) / 255.0,
									1.0f
									)
					};
					bunnies.push_back(new_bunny);
				}
			}
			//batch.drawRectangle(100,100,50.0,50.0,glm::vec4(0.3,0.3,1.0,1.0));
		}

		// move bunnies
		for (int i = 0; i < bunnies.size(); i++)
		{
			bunnies.at(i).position.x += bunnies.at(i).speed.x;
			bunnies.at(i).position.y += bunnies.at(i).speed.y;

			if (((bunnies.at(i).position.x) > SCREEN_WIDTH) || ((bunnies.at(i).position.x) < 0))
				bunnies.at(i).speed.x *= -1;
			if (((bunnies.at(i).position.y) > SCREEN_HEIGHT) || ((bunnies.at(i).position.y) < 0))
				bunnies.at(i).speed.y *= -1;
		}

		for (int i = 0; i < bunnies.size(); i++)
		{
			batch.drawTexture(
					texture,
					bunnies.at(i).position.x,
					bunnies.at(i).position.y,
					32,
					32,
					bunnies.at(i).color
					);
		}
		//batch.drawTexture(texture,0.0,0.0,1.0,1.0,glm::vec4(1.0,1.0,1.0,0.5));

		batch.flush_batch(); // does the drawing


		glfwSwapBuffers(Window::get());
		glfwPollEvents();
		stop = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

		std::cout << bunnies.size();
		std::cout << " Bunnies at ";
		std::cout << round(1.0f/((float)duration.count() / 10000000.0f))/10.0;
		std::cout << " FPS";
		std::cout << std::endl;
	}

	glfwTerminate();
	return 0;
}

