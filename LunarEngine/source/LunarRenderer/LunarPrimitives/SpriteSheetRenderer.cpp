#include "../../../public/LunarPrimitives/SpriteSheetRenderer.h"
#include "..\..\..\public\LunarPrimitives\SpriteSheetRenderer.h"

namespace Lunar2D {
	SpriteSheetRenderer::SpriteSheetRenderer() {
	}

	SpriteSheetRenderer::~SpriteSheetRenderer() {

	}

	void SpriteSheetRenderer::SpriteDims(int x, int y) {
		spriteDims = glm::ivec2(x, y);
	}

	void SpriteSheetRenderer::InitResources(std::string spriteSheet) {
		model = glm::mat4(1.0f);
		baseIndex = getUVBox(0);

		float vertices[] = {
			0.5f,  0.5f,   baseIndex.x + baseIndex.z, baseIndex.y + baseIndex.w, // bottom right
			0.5f, -0.5f,   baseIndex.x + baseIndex.z, baseIndex.y, // top right
			-0.5f, -0.5f,  baseIndex.x, baseIndex.y, // top left
			-0.5f,  0.5f,  baseIndex.x, baseIndex.y + baseIndex.w  // bottom left 
		};
	}

	glm::vec4 SpriteSheetRenderer::getUVBox(int index) {
		int xTile = index % spriteDims.x;
		int yTile = index / spriteDims.x;

		glm::vec4 uvBox;
		uvBox.x = xTile / (float)spriteDims.x;
		uvBox.y = yTile / (float)spriteDims.y;
		uvBox.z = 1.0f / spriteDims.x;
		uvBox.w = 1.0f / spriteDims.y;

		return uvBox;
	}

	void SpriteSheetRenderer::PassShader(LunarRenderer::LunarShader* spriteShader) {

	}

	void SpriteSheetRenderer::UseSprite(int index) {

	}

	void SpriteSheetRenderer::Draw() {

	}
}