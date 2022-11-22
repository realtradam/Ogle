#include "texture.hpp"

#include <iostream>
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture(const char* texturePath, unsigned int VAO, unsigned int VBO)
{
	this->VAO = VAO;
	this->VBO = VBO;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void Texture::draw(float x, float y, float width, float height)
{
	float vertices[] = {
		// positions				// colors           // texture coords
		x-width,  y+height, 0.0f,	1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		x-width, y, 0.0f,			0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		x, y, 0.0f,					0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		x, y+height, 0.0f,			1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind(activate) the buffer to the ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW); // upload the data
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
