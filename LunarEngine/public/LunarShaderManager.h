#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "LuanarShader.h"
#include "LunarShaderGen.h"

namespace LunarUtils {
	class ShaderManager {
	public:
		ShaderManager();
		~ShaderManager();

		void CreateShader(std::string id, LunarUtils::LunarShaderGenerator* vertShader, LunarUtils::LunarShaderGenerator* fragShader);
		LunarRenderer::LunarShader* GetShader(std::string id);
	private:
		std::unordered_map<std::string, LunarRenderer::LunarShader> shaderMap;
	};
}