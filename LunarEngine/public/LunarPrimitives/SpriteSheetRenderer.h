#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "../LuanarShader.h"
#include "LunarTexture.h"

namespace Lunar2D {
	class SpriteSheetRenderer {
	public:
		SpriteSheetRenderer();
		~SpriteSheetRenderer();

		void SpriteDims(int x = 2, int y = 2);
		void InitResources(std::string spriteSheet = "empty");
		void PassShader(LunarRenderer::LunarShader* spriteShader);

		void UseSprite(int index);
		void Draw(glm::mat4 projection, glm::mat4 view);

	private:
		//model stuff
		unsigned int VBO, VAO, EBO;
		LunarRenderer::LunarShader* spriteShader;

		//sprite texture
		LunarTexture spriteTexture;

		glm::mat4 model;

		glm::vec2 position;
		glm::vec2 size;
		glm::vec3 color;
		float rotate;

		//sprite sheet uv
		glm::ivec2 spriteDims;
		glm::vec4 baseIndex;

	private:
		glm::vec4 getUVBox(int index);
	};
}