#pragma once
#include "SpriteRenderer.h"
#include "SpriteSheetRenderer.h"

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
		void UpdateTiledTile(std::string id, int index);

		void CreateSprite(std::string id, std::string texture = "empty"); // add options
		void CreateTiledSprite(std::string id, std::string texture = "empty", int xDim = 2, int yDim = 2);

		void Draw();
	private:
		glm::mat4 projection;
		glm::mat4 view;
		//model implemented in sprite

		//camera
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		//sprite list
		std::vector<std::tuple<std::string, Sprite>> sprites;
		std::vector<std::tuple<std::string, SpriteSheetRenderer>> spriteSheetSprites;
		//shader
		LunarRenderer::LunarShader shader;
	};
}