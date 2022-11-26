
// external libs
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// project headers
#include "input.hpp"
#include "shader.hpp"
#include "batch.hpp"
#include "window.hpp"
#include "random.hpp"

// std libs
#include <iostream>
#include <cmath>
#include <chrono>

using namespace Ogle;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;

const int MAX_BUNNIES = 50000;
typedef struct Bunny {
	glm::vec2 position;
	glm::vec2 speed;
	glm::vec4 color;
} Bunny;

int main() {

	// init glfw window
	Window::init(SCREEN_WIDTH, SCREEN_HEIGHT, "Ogle");

	// init various opengl components
	Shader shader = Shader("src/shaders/default.vert", "src/shaders/default.frag");
	Batch batch = Batch(1024 * 8);
	Texture texture = Texture("assets/wabbit_alpha.png");

	// setup projection matrix
	//   Here we swap the height-begin and
	//   height-end values to flip it as opengl is "upsidedown"
	glm::mat4 transform = glm::ortho(0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, 0.1f, 100.0f);
	shader.use();
	shader.setMatrix4fv("transform", transform);

	// setup bunnies
	std::vector<Bunny> bunnies = std::vector<Bunny>{};
	bunnies.reserve(MAX_BUNNIES * sizeof(Bunny));

	// setup fps measuring
	std::vector<int> fps_smoothing = std::vector<int>{};

	// game loop
	while(!glfwWindowShouldClose(Window::get()))
	{
		auto start_frametime = std::chrono::high_resolution_clock::now();

		Input::process(Window::get());

		glClearColor(0.4f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();

		// create bunnies when clicking
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

		// render bunnies
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

		batch.flush(); // forces remaining batched verts to be rendered

		glfwSwapBuffers(Window::get());
		glfwPollEvents();

		auto end_frametime = std::chrono::high_resolution_clock::now();
		auto frametime = std::chrono::duration_cast<std::chrono::microseconds>(end_frametime - start_frametime);

		if(fps_smoothing.size() >= 30)
			fps_smoothing.erase(fps_smoothing.begin());
		fps_smoothing.push_back(round(1.0f/((float)frametime.count() / 1000000.0f)));
		int average = 0;
		for(int i = 0; i < fps_smoothing.size(); i++)
		{
			average += fps_smoothing.at(i);
		}
		average /= fps_smoothing.size();
		std::cout << bunnies.size() << " Bunnies at " << average << " FPS" << std::endl;
	}

	glfwTerminate();
	return 0;
}

