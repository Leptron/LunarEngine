#pragma once
#include <string>
#include "../glad/glad.h"
#include "../LunarImageLoader.h"

namespace Lunar2D {
	class LunarTexture {
	public:
		LunarTexture();
		~LunarTexture();

		void LoadTexture(std::string textureLoc = "textures/checkerboard.png");
		void Use();
	private:
		unsigned int texture;
	};
}