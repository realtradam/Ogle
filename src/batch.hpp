#pragma once

// external libs
#include "glad/glad.h"
#include "glm/glm.hpp"

// project headers
#include "texture.hpp"

// std libs
#include <vector>

class Batch
{
	public:
		unsigned int VAO, VBO, EBO;
		std::vector<float> vertices = {};
		std::vector<unsigned int> indices = {};
		unsigned int size, batch_limit;
		unsigned int last_texture = 0;

		Batch(unsigned int batch_limit = 8192);
		int drawTexture(
				Texture texture,
				float x,
				float y,
				float width,
				float height,
				glm::vec4 color
				);
		int drawRectangle(
				float x,
				float y,
				float width,
				float height,
				glm::vec4 color
				);
		void flush();
	private:
		int primativeDrawQuad(
				unsigned int texture_id,
				glm::vec3 a,
				glm::vec3 b,
				glm::vec3 c,
				glm::vec3 d,
				glm::vec4 color
				);
};
