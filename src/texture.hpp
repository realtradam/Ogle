#pragma once
#include "glad/glad.h"

class Texture
{
	public:
		unsigned int id, VAO, VBO;
		Texture(const char* texturePath, unsigned int VAO, unsigned int VBO);
		void draw(float x, float y, float width, float height);
};
