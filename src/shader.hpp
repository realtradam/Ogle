#pragma once

#include <string>

#include "glad/glad.h"

class Shader
{
	public:
		// id of the shader program
		unsigned int ID;

		Shader(const char* vertexPath, const char* fragmentPath);

		// activate the shader
		void use();

		// utility functions for uniforms
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
};
