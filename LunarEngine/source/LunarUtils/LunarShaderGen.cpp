#include "../../public/LunarShaderGen.h"

namespace LunarUtils {
	LunarShaderGenerator::LunarShaderGenerator() {
		outputStream << "#version 330 core" << std::endl;
	}

	LunarShaderGenerator::~LunarShaderGenerator() {

	}
	
	void LunarShaderGenerator::AddLayout(std::string layoutLocation, std::string layoutDataType, std::string layoutName) {
		outputStream << "layout (location = " << layoutLocation << ") in " << layoutDataType << " " << layoutName << ";" << std::endl;
		layouts.push_back(layoutName);
	}

	void LunarShaderGenerator::AddUniform(std::string uniformName, std::string dataType) {
		outputStream << "uniform" << " " << dataType << " " << uniformName << ";" << std::endl;
	}

	void LunarShaderGenerator::AddOutput(std::string outputName, std::string outputDataType) {
		outputStream << "out " << outputDataType << " " << outputName << ";" << std::endl;
	}

	void LunarShaderGenerator::AddInput(std::string inputName, std::string inputDataType) {
		outputStream << "in " << inputDataType << " " << inputName << ";" << std::endl;
	}

	void LunarShaderGenerator::SetVertexPosition(std::string variable) {
		mainStream << "vec4 vPosition = vec4(" << variable << ", 1.0);" << std::endl;
	}

	void LunarShaderGenerator::SetGlPosition(std::string expression) {
		mainStream << "gl_Position = " << expression << ";" << std::endl;
	}

	void LunarShaderGenerator::SetVariable(std::string targetVariable, std::string value) {
		mainStream << targetVariable << " = " << value << ";" << std::endl;
	}

	//glsl functions
	std::string LunarShaderGenerator::ShaderTexture(std::string tex, std::string tCoord) {
		std::stringstream tmp;

		tmp << "texture(" << tex << "," << tCoord << ")";
		return tmp.str();
	}

	std::string LunarShaderGenerator::GenShader() {
		std::stringstream shader_output;

		shader_output << outputStream.str() << std::endl;
		shader_output << "void main()" << std::endl;
		shader_output << "{" << std::endl;
		shader_output << mainStream.str() << std::endl;
		shader_output << "}" << std::endl;

		return shader_output.str();
	}
}