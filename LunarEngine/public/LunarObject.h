#pragma once

#include "../public/glad/glad.h"
#include <iostream>
#include <vector>
#include <array>

#include "LuanarShader.h"

namespace LunarRenderer {
	class LunarOpenglObject {
	public:
		LunarOpenglObject(std::vector<float> verts, std::vector<unsigned int> indices, LunarShader* shader);

		void Draw();
		void Clean();
	private:
		unsigned int VBO, VAO, EBO;
		int indexCount;

		LunarShader* shader;
	};
}