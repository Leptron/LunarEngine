#pragma once
#include "SpriteRenderer.h"
#include "../LunarShaderGen.h"
#include "../LuanarShader.h"
#include "../LunarLogger.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <iostream>
#include <tuple>
#include <string>

namespace Lunar2D {
	class SpriteManager {
	public:
		SpriteManager();
		~SpriteManager();

		void InitResources();
		void UpdateScreenDims(int width, int height);
		void CreateSprite(std::string id, std::string texture = "empty"); // add options

		void Draw();
	private:
		glm::mat4 projection;
		glm::mat4 view;
		//model implemented in sprite

		//camera
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		//sprite list
		std::vector<std::tuple<std::string, Sprite>> sprites;
		//shader
		LunarRenderer::LunarShader shader;
	};
}