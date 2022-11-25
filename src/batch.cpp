
// external libs
#include "glad/glad.h"

// project headers
#include "batch.hpp"
#include "texture.hpp"

// std libs
#include <vector>
#include <iostream>


Batch::Batch(unsigned int batch_limit)
{
	this->batch_limit = batch_limit;

	glGenBuffers(1, &VBO); // generate the buffer
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO); // generate array

	glBindVertexArray(VAO); // bind array to apply "settings" to it
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind(activate) the buffer to the ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// position attribute
	GLsizei stride = 10 * sizeof(float);
	glVertexAttribPointer(
			0, // index
			3, // size(number of elements)
			GL_FLOAT,
			GL_FALSE,
			stride, // stride(distance to reach next one)
			(void*)0); // pointer(offset from start)
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			stride,
			(void*)(3 * sizeof(float))); // configure how the vertex array looks
	glEnableVertexAttribArray(1);

	//texture coordinates
	glVertexAttribPointer(
			2,
			2,
			GL_FLOAT,
			GL_FALSE,
			stride,
			(void*)(7 * sizeof(float))); // configure how the vertex array looks
	glEnableVertexAttribArray(2);

	//texture id
	glVertexAttribPointer(
			3,
			1,
			GL_FLOAT,
			GL_FALSE,
			stride,
			(void*)(9 * sizeof(float))); // configure how the vertex array looks
	glEnableVertexAttribArray(3);
}

int Batch::drawTexture(
		Texture texture,
		float x,
		float y,
		float width,
		float height,
		glm::vec4 color
		)
{
	float h_height = height / 2.0;
	float h_width = width / 2.0;
	return this->primativeDrawQuad(
			texture.id,
			glm::vec3(x+h_height,y+h_width, -1.0f), // top right
			glm::vec3(x+h_height, y-h_width, -1.0f), // bottom right
			glm::vec3(x-h_height, y-h_width, -1.0f), // bottom left
			glm::vec3(x-h_height, y+h_height, -1.0f), // top left 
			color
			);
}


int Batch::drawRectangle(
		float x,
		float y,
		float width,
		float height,
		glm::vec4 color
		)
{
	float h_height = height / 2.0;
	float h_width = width / 2.0;
	return this->primativeDrawQuad(
			0,
			glm::vec3(x+h_height,y+h_width, -1.0f), // top right
			glm::vec3(x+h_height, y-h_width, -1.0f), // bottom right
			glm::vec3(x-h_height, y-h_width, -1.0f), // bottom left
			glm::vec3(x-h_height, y+h_height, -1.0f), // top left 
			color
			);
}

int Batch::primativeDrawQuad(
		unsigned int texture_id,
		glm::vec3 a,
		glm::vec3 b,
		glm::vec3 c,
		glm::vec3 d,
		glm::vec4 color
		)
{
	// if no assigned texture, attempt to assign it
	if(texture_id == 0)
		last_texture = texture_id;
	// if surpassing batch limit
	// or if texture is different
	if((size >= batch_limit) || ((last_texture != texture_id) && (texture_id != 0)))
		this->flush(); last_texture = texture_id;


	float verts[] = {
		// top right	
		a.x,  a.y, a.z, // position
		color.r, color.g, color.b, color.a, // colors
		1.0f, 1.0f, // tex coords
		(float)texture_id, // tex id(0 means none)

		// bottom right
		b.x, b.y, b.z,
		color.r, color.g, color.b, color.a,
		1.0f, 0.0f,
		(float)texture_id,

		// bottom left
		c.x, c.y, c.z,
		color.r, color.g, color.b, color.a,
		0.0f, 0.0f,
		(float)texture_id,  

		// top left 
		d.x,  d.y, d.z,
		color.r, color.g, color.b, color.a,
		0.0f, 1.0f,
		(float)texture_id  
	};
	unsigned int inds[] = {
		(size * 4) + 0, (size * 4) + 1, (size * 4) + 3,  // first triangle
		(size * 4) + 1, (size * 4) + 2, (size * 4) + 3,  // second triangle
	};
	vertices.reserve(sizeof(verts));
	indices.reserve(sizeof(inds));
	vertices.insert(vertices.end(), std::cbegin(verts), std::cend(verts));
	indices.insert(indices.end(), std::cbegin(inds), std::cend(inds));
	size += 1;

	return 0;
}

void Batch::flush()
{
	glBindVertexArray(VAO);

	// we already binded this in the VAO during initialization
	// so no need to do it again
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData( // uploading vertices
			GL_ARRAY_BUFFER,
			vertices.size() * sizeof(float),
			vertices.data(),
			GL_DYNAMIC_DRAW
			);

	// we already binded this in the VAO during initialization
	// so no need to do it again
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData( // uploading indices
			GL_ELEMENT_ARRAY_BUFFER,
			indices.size() * sizeof(unsigned int),
			indices.data(),
			GL_DYNAMIC_DRAW
			);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, last_texture);
	glDrawElements(GL_TRIANGLES, 6 * size, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0); // unbind the VAO

	last_texture = 0;
	size = 0;
	vertices.clear();
	indices.clear();
}
