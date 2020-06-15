#include "../../public/LunarShaderManager.h"

namespace LunarUtils {
	ShaderManager::ShaderManager() {

	}

	ShaderManager::~ShaderManager() {

	}

	void ShaderManager::CreateShader(std::string id, LunarUtils::LunarShaderGenerator* vertShader, LunarUtils::LunarShaderGenerator* fragShader) {
		//TODO set gl Position with mvp if requested
		vertShader->SetGlPosition("vPosition");

		shaderMap[id] = LunarRenderer::LunarShader(vertShader, fragShader);
	}

	LunarRenderer::LunarShader* ShaderManager::GetShader(std::string id) {
		return &shaderMap[id];
	}
}