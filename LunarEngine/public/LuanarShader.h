#pragma once

#include "../public/glad/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "LunarShaderGen.h"

namespace LunarRenderer {
	class LunarShader {
	public:
		unsigned int ID;

		LunarShader();
		LunarShader(const char* vertexPath, const char* fragmentPath);
		LunarShader(LunarUtils::LunarShaderGenerator* vertexShader, LunarUtils::LunarShaderGenerator* fragmentShader);
		//use the shader
		void use();
		//uniform functions
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		//matrix and vectors
		void SetMatrix4(const char* name, const glm::mat4& matrix);
		void SetVector3f(const char* name, const glm::vec3& value);
		//clean shader
		void Clean();
	};
}