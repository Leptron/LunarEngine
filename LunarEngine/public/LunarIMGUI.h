#pragma once
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <imgui.h>

#include "LunarLayerManager.h"

namespace LunarEditor {
    class LunarEditorGUI {
    private:
        //member variables
        VkSampler sampler;
        
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;

        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;

        int32_t vertexCount = 0;
        int32_t indexCount = 0;

        VkDeviceMemory fontMemory = VK_NULL_HANDLE;
        VkImage fontImage = VK_NULL_HANDLE;
        VkImageView fontView = VK_NULL_HANDLE;

        VkPipelineCache pipelineCache;
        VkPipelineLayout pipelineLayout;
        VkPipeline pipeline;
        VkDescriptorPool descriptorPool;
        VkDescriptorSetLayout descriptorSetLayout;
	    VkDescriptorSet descriptorSet;

        VkDevice device;
        LunarRenderer::LayerManager *manager;

    public:
        struct PushConstants {
            glm::vec2 scale;
            glm::vec2 translate;
        } pushConstBlock;

        LunarEditorGUI(LunarRenderer::LayerManager *manager);
        ~LunarEditorGUI();
    };
}