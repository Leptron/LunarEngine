#pragma once

#include <vector>
#include <string>
#include <sstream>

namespace LunarUtils {

	enum LunarDataType {
		vec3,
		vec2,
		sampler2D,
	};

	class LunarShaderGenerator {
	public:
		LunarShaderGenerator();
		~LunarShaderGenerator();

		void AddLayout(std::string layoutLocation, std::string layoutDataType, std::string layoutName);
		void AddUniform(std::string uniformName, std::string dataType);

		void AddOutput(std::string outputName, std::string outputDataType);
		void AddInput(std::string inputName, std::string inputDataType);

		void SetVertexPosition(std::string variable);
		void SetVariable(std::string targetVariable, std::string value);

		//glsl functions
		std::string ShaderTexture(std::string tex, std::string tCoord);

		std::string GenShader();
	private:
		std::vector<std::string> layouts;

		//output file
		std::stringstream outputStream;
		std::stringstream mainStream;
	};
}