#pragma once
#include "glad/glad.h"

class Texture
{
	public:
		unsigned int id;
		Texture(const char* texture_path);
};
