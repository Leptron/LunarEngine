#include "../../../public/LunarPrimitives/SpriteRenderer.h"

namespace Lunar2D {
	Sprite::Sprite() {
		model = glm::mat4(1.0f);

		float vertices[] = {
			0.5f,  0.5f,   1.0f, 1.0f, // top right
			0.5f, -0.5f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f,  0.0f, 0.0f, // bottom left (Index 0)
			-0.5f,  0.5f,  0.0f, 1.0f  // top left
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

		position = glm::vec2(500.0f, 300.0f);
		size = glm::vec2(300.0f, 300.0f);
		rotate = 0.0f;
		color = glm::vec3(1.0f);
	}

	void Sprite::PassShader(LunarRenderer::LunarShader* spriteShader) {
		this->spriteShader = spriteShader;
		spriteShader->use();
		spriteShader->setInt("image", 0);
	}

	void Sprite::Draw(glm::mat4 projection, glm::mat4 view) {
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

		this->spriteTexture.Use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void Sprite::UseSprite(std::string spriteLoc) {
		if (spriteLoc == "empty") {
			//checkerboard sprite
			spriteTexture.LoadTexture();
		}
		else {
			spriteTexture.LoadTexture(spriteLoc);
		}
	}
}