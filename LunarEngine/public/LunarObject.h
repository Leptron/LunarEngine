#pragma once

#include "../public/glad/glad.h"
#include <iostream>
#include <vector>
#include <array>

#include "LuanarShader.h"

namespace LunarRenderer {
	class LunarOpenglObject {
	public:
		LunarOpenglObject();
		LunarOpenglObject(std::vector<float> verts, std::vector<unsigned int> indices, LunarShader* shader, std::string stexture="checker");

		void Draw();
		void Clean();
	private:
		unsigned int VBO, VAO, EBO;
		int indexCount;

		//texture
		std::string textureLoc = "";
		unsigned int texture;

		LunarShader* shader;
	};

	struct LayerObject {
		std::string id;
		LunarOpenglObject object;
	};
}