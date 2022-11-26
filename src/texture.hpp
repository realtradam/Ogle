#pragma once

// external libs
#include "glad/glad.h"

namespace Ogle
{
	class Texture
	{
		public:
			unsigned int id;
			Texture(const char* texture_path);
	};
}
