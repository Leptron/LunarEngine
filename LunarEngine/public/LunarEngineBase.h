#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fstream>
#include <vector>
#include <exception>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vulkan/vulkan.h>
#include "vulkanexamplebase.h"

// Set to "true" to enable Vulkan's validation layers (see vulkandebug.cpp for details)
#define ENABLE_VALIDATION true
// Set to "true" to use staging buffers for uploading vertex and index data to device local memory
// See "prepareVertices" for details on what's staging and on why to use it
#define USE_STAGING true


namespace LunarEngine {
	class LunarEngineRenderer : public VulkanExampleBase {
		public:
		//vertex layout	
		struct Vertex {
			float position[3];
			float color[3];
		};
		
		//vertex buffer
		struct {
			VkDeviceMemory memory;
			VkBuffer buffer;
		} vertices;
		
		//index buffer
		struct {
			VkDeviceMemory memory;
			VkBuffer buffer;
			uint32_t count;
		} indices;

		//uniform buffer block object
		struct {
			VkDeviceMemory memory;
			VkBuffer buffer;
			VkDescriptorBufferInfo descriptor;
		} uniformBufferVS;

		//same block layout as in shader
		//meant so we can just memocpy to the shader
		struct {
			glm::mat4 projectionMatrix;
			glm::mat4 modelMatrix;
			glm::mat4 viewMatrix;
		} uboVS;

		//pipeline layout used to access the descriptor sets
		VkPipelineLayout pipelineLayout;

		//pipeline that the entire state is baked into
		//needs multiple pipelines per state requested
		VkPipeline pipeline;

		VkDescriptorSetLayout descriptorSetLayout;

		VkDescriptorSet descriptorSet;

		VkSemaphore presentCompleteSemaphore;
		VkSemaphore renderCompleteSemaphore;

		std::vector<VkFence> waitFences;

        LunarEngineRenderer();
        ~LunarEngineRenderer();

        uint32_t getMemoryTypeIndex(uint32_t typeBits, VkMemoryPropertyFlags properties);
        void prepareSynchronizationPrimitives();
        VkCommandBuffer getCommandBuffer(bool begin);
        void flushCommandBuffer(VkCommandBuffer commandBuffer);
        void buildCommandBuffers();
        void draw();
        void prepareVertices(bool useStagingBuffers);
		void setupDescriptorPool();
		void setupDescriptorSetLayout();
		void setupDescriptorSet();
		void setupDepthStencil();
		void setupFrameBuffer();
		void setupRenderPass();
		VkShaderModule loadSPIRVShader(std::string filename);
		void preparePipelines();
		void prepareUniformBuffers();
		void updateUniformBuffers();
		void prepare();

		virtual void render();
		virtual void viewChanged();
	};
}
