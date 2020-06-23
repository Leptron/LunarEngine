#pragma once

#include "../LunarLogger.h"
#include "../LunarShaderGen.h"
#include "../LuanarShader.h"
#include "../glad/glad.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <vector>
#include <sstream>

namespace LunarBatching {
	struct BatchedQuad {
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
	};

	struct LunarBatchedColor {
		glm::vec3 lColor;
		glm::vec3 lTColor;
		glm::vec3 rColor;
		glm::vec4 rTColor;
	};

	class StaticSquareBatch {
	public:
		StaticSquareBatch();
		~StaticSquareBatch();

		void CreateQuad(glm::vec2 position, glm::vec2 size, float rot);
		void UpdateOrtho(glm::mat4 orthoProjection);

		void Batch();
		void Draw(glm::mat4 viewMat = glm::mat4(1));
	private:
		const unsigned int INDEX_INCREMENT = 4;
		unsigned int currIndexIncrement = 0;

		std::vector<BatchedQuad> objects;
		bool instantiated = false;

		unsigned int VBO, VAO, EBO;
		int indexCount;
		
		//projection
		glm::mat4 orthoProjection;

		//shader
		LunarRenderer::LunarShader shader;
	};
}
