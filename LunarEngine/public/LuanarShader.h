#pragma once

#include "../public/glad/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "LunarShaderGen.h"

namespace LunarRenderer {
	class LunarShader {
	public:
		unsigned int ID;

		LunarShader(const char* vertexPath, const char* fragmentPath);
		LunarShader(LunarUtils::LunarShaderGenerator vertexShader, LunarUtils::LunarShaderGenerator fragmentShader);
		//use the shader
		void use();
		//uniform functions
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		//clean shader
		void Clean();
	};
}