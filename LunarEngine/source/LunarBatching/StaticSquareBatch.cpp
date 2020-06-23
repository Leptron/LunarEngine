#include "../../public/LunarBatching/StaticSquareBatch.h"

namespace LunarBatching {
	StaticSquareBatch::StaticSquareBatch() {

	}

	StaticSquareBatch::~StaticSquareBatch() {

	}

	void StaticSquareBatch::CreateQuad(glm::vec2 position, glm::vec2 size, float rot) {
		if (!instantiated) {
			glm::mat4 _tmpModel = glm::mat4(1.0f);

			_tmpModel = glm::translate(_tmpModel, glm::vec3(position, 0.0f));

			_tmpModel = glm::translate(_tmpModel, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
			_tmpModel = glm::rotate(_tmpModel, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
			_tmpModel = glm::translate(_tmpModel, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

			_tmpModel = glm::scale(_tmpModel, glm::vec3(size, 1.0f));

			glm::vec2 bottomRightVertices;
			glm::vec2 topRightVertices;
			glm::vec2 topLeftVertices;
			glm::vec2 bottomLeftVertices;

			glm::vec4 finalBottomRight;
			glm::vec4 finalTopRight;
			glm::vec4 finalTopLeft;
			glm::vec4 finalBottomLeft;

			bottomRightVertices.x = 1.0f;
			bottomRightVertices.y = 1.0f;

			topRightVertices.x = 1.0f;
			topRightVertices.y = -1.0f;

			topLeftVertices.x = -1.0f;
			topLeftVertices.y = -1.0f;

			bottomLeftVertices.x = -1.0f;
			bottomLeftVertices.y = 1.0f;

			finalBottomRight = _tmpModel * glm::vec4(bottomRightVertices, 0.0f, 1.0f);
			finalTopRight = _tmpModel * glm::vec4(topRightVertices, 0.0f, 1.0f);
			finalTopLeft = _tmpModel * glm::vec4(topLeftVertices, 0.0f, 1.0f);
			finalBottomLeft = _tmpModel * glm::vec4(bottomLeftVertices, 0.0f, 1.0f);

			std::vector<float> verts = {
				finalBottomRight.x, finalBottomRight.y, 1.0f, 1.0f,
				finalTopRight.x, finalTopRight.y, 1.0f, 0.0f,
				finalTopLeft.x, finalTopLeft.y, 0.0f, 0.0f,
				finalBottomLeft.x, finalBottomLeft.y, 0.0f, 1.0f
			};

			std::vector<int> indexs = {
				currIndexIncrement, currIndexIncrement + 1, currIndexIncrement + 3,
				currIndexIncrement + 1, currIndexIncrement + 2, currIndexIncrement + 3
			};

			currIndexIncrement += INDEX_INCREMENT;

			BatchedQuad _batch = {};
			_batch.vertices = verts;
			_batch.indices = indexs;
			objects.push_back(_batch);
		}
	}

	void StaticSquareBatch::Batch() {
		instantiated = true;

		std::vector<float> unbatchedVerts;
		std::vector<int> unbatchedIndicies;
		for (auto object : objects) {
			//loop over floats and ints
			for (auto vert : object.vertices)
				unbatchedVerts.push_back(vert);
			for (auto index : object.indices)
				unbatchedIndicies.push_back(index);
		}

		std::stringstream messageStream;
		messageStream << "Created a Sprite Batch with " << unbatchedVerts.size() << " vertices" << std::endl;
		LunarLogger::Logger::getInstance()->log(messageStream.str(), "Static Batch", "red");

		//create the ubo stuff
		indexCount = unbatchedIndicies.size();

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		//bind the vertex array object
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, unbatchedVerts.size() * sizeof(float), unbatchedVerts.data(), GL_STATIC_DRAW);

		//indices data
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, unbatchedIndicies.size() * sizeof(int), unbatchedIndicies.data(), GL_STATIC_DRAW);

		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//now create a shader
		LunarUtils::LunarShaderGenerator vertShaderGen;
		
		vertShaderGen.AddLayout("0", "vec4", "vertex");
		vertShaderGen.AddOutput("TexCoords", "vec2");

		vertShaderGen.AddUniform("view", "mat4");
		vertShaderGen.AddUniform("projection", "mat4");

		vertShaderGen.SetVariable("TexCoords", "vertex.zw");
		vertShaderGen.SetGlPosition("projection * view * vec4(vertex.xy, 0.0, 1.0)");
		//frag shader
		LunarUtils::LunarShaderGenerator fragShaderGen;

		fragShaderGen.AddInput("TexCoords", "vec2");
		fragShaderGen.AddOutput("color", "vec4");

		fragShaderGen.AddUniform("spriteColor", "vec3");
		fragShaderGen.SetVariable("color", "vec4(spriteColor, 1.0)");

		shader = LunarRenderer::LunarShader(&vertShaderGen, &fragShaderGen);
	}
}