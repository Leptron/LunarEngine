#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>

#include "../LuanarShader.h"
#include "LunarTexture.h"

namespace Lunar2D {
	class Sprite {
	public:
		Sprite();

		void Draw(glm::mat4 projection, glm::mat4 view);
		void PassShader(LunarRenderer::LunarShader* spriteShader);
		void UseSprite(std::string spriteLoc = "empty");
	private:
		glm::mat4 model;

		glm::vec2 position;
		glm::vec2 size;
		glm::vec3 color;
		float rotate;


		//model stuff
		unsigned int VBO, VAO, EBO;
		LunarRenderer::LunarShader* spriteShader;

		//sprite texture
		LunarTexture spriteTexture;
	};
}