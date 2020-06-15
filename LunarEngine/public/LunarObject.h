#pragma once

#include "../public/glad/glad.h"
#include <iostream>
#include <vector>
#include <array>

#include "LuanarShader.h"
#include "LunarImageLoader.h"

namespace LunarRenderer {
	class LunarOpenglObject {
	public:
		LunarOpenglObject();
		LunarOpenglObject(std::vector<float> verts, std::vector<unsigned int> indices, LunarShader* shader, std::string stexture="checker");

		virtual void Draw();
		virtual void Clean();
	protected:
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