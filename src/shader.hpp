#pragma once

// external libs
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// std libs
#include <string>

namespace Ogle
{
	class Shader
	{
		public:
			// id of the shader program
			unsigned int ID;

			Shader(const char* vertexPath, const char* fragmentPath);

			// activate the shader
			void use();

			// utility setter functions for uniforms
			void setBool(const std::string &name, bool value) const;
			void setInt(const std::string &name, int value) const;
			void set1f(const std::string &name, float value) const;
			void set4f(
					const std::string &name,
					float value0,
					float value1,
					float value2,
					float value3
					) const;
			void setMatrix4fv(const std::string &name, glm::mat4 matrix);
	};
}
