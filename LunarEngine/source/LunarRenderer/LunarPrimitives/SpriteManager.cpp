#include "../../../public/LunarPrimitives/SpriteManager.h"

namespace Lunar2D {
	SpriteManager::SpriteManager() {
	}

	SpriteManager::~SpriteManager() {

	}

	void SpriteManager::InitResources() {
		LunarLogger::Logger::getInstance()->log("Created Sprite Manager Instance", "Sprite Manager", "red");
		LunarUtils::LunarShaderGenerator vertShader;

		vertShader.AddLayout("0", "vec4", "vertex");
		vertShader.AddOutput("TexCoords", "vec2");

		vertShader.AddUniform("model", "mat4");
		vertShader.AddUniform("view", "mat4");
		vertShader.AddUniform("projection", "mat4");
		vertShader.AddUniform("texCoordShift", "vec2");

		vertShader.SetVariable("TexCoords", "vertex.zw + texCoordShift");
		
		vertShader.SetGlPosition("projection * model * vec4(vertex.xy, 0.0, 1.0)");

		LunarUtils::LunarShaderGenerator fragShader;

		fragShader.AddInput("TexCoords", "vec2");
		fragShader.AddOutput("color", "vec4");

		fragShader.AddUniform("image", "sampler2D");
		fragShader.AddUniform("spriteColor", "vec3");

		fragShader.SetVariable("color", "vec4(spriteColor, 1.0) * texture(image, TexCoords)");

		shader = LunarRenderer::LunarShader(&vertShader, &fragShader);

		//set the default glm
		view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
						   glm::vec3(0.0f, 0.0f, 0.0f),
						   glm::vec3(0.0f, 1.0f, 0.0f));

		shader.use();
		shader.SetMatrix4("projection", projection);
		shader.SetMatrix4("view", view);
	}

	void SpriteManager::UpdateScreenDims(int width, int height) {
		projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
	}

	void SpriteManager::CreateSprite(std::string id, std::string texture) {
		Sprite n_Sprite;

		n_Sprite.PassShader(&shader);
		if (texture == "empty")
			n_Sprite.UseSprite();
		else
			n_Sprite.UseSprite(texture);

		auto n_tuple = std::make_tuple(id, n_Sprite);
		sprites.push_back(n_tuple);

		LunarLogger::Logger::getInstance()->log("Created Sprite with id of " + id, "Sprite Manager", "red");
	}

	void SpriteManager::CreateTiledSprite(std::string id, std::string texture, int xDim, int yDim) {
		SpriteSheetRenderer n_Sprite;
		
		n_Sprite.SpriteDims(xDim, yDim);
		n_Sprite.PassShader(&shader);
		n_Sprite.InitResources(texture);

		auto n_tupe = std::make_tuple(id, n_Sprite);
		spriteSheetSprites.push_back(n_tupe);

		LunarLogger::Logger::getInstance()->log("Created Tiled Sprite with id of " + id, "Sprite Manager", "red");
	}

	void SpriteManager::Draw() {
		for (auto sprite : sprites) {
			auto n_sprite = std::get<1>(sprite);
			n_sprite.Draw(projection, view);
		}

		for (auto sprite : spriteSheetSprites) {
			auto n_sprite = std::get<1>(sprite);
			n_sprite.Draw(projection, view);
		}
	}
}