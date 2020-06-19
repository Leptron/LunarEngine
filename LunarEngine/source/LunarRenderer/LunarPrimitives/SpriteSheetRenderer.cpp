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

		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(this->VAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		position = glm::vec2(800.0f, 300.0f);
		size = glm::vec2(100.0f, 100.0f);
		rotate = 0.0f;
		color = glm::vec3(1.0f);
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
		this->spriteShader = spriteShader;
	}

	void SpriteSheetRenderer::UseSprite(int index) {
		baseIndex = getUVBox(index);
		float vertices[] = {
			0.5f,  0.5f,   baseIndex.x + baseIndex.z, baseIndex.y + baseIndex.w, // bottom right
			0.5f, -0.5f,   baseIndex.x + baseIndex.z, baseIndex.y, // top right
			-0.5f, -0.5f,  baseIndex.x, baseIndex.y, // top left
			-0.5f,  0.5f,  baseIndex.x, baseIndex.y + baseIndex.w  // bottom left 
		};

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		memcpy(ptr, vertices, sizeof(vertices));
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	void SpriteSheetRenderer::Draw(glm::mat4 projection, glm::mat4 view) {
		this->spriteShader->use();

		model = glm::translate(model, glm::vec3(position, 0.0f));

		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

		model = glm::scale(model, glm::vec3(size, 1.0f));

		this->spriteShader->SetMatrix4("model", model);
		this->spriteShader->SetMatrix4("view", view);
		this->spriteShader->SetMatrix4("projection", projection);
		//set color
		this->spriteShader->SetVector3f("spriteColor", color);

		spriteTexture.Use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}