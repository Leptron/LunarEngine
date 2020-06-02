#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <optional>
#include <set>
#include <algorithm>
#include <fstream>
#include <glm/glm.hpp>
#include <array>

#include "LunarBuffer.hpp"

namespace LunarRenderer {
    struct Vertex {
        glm::vec2 pos;
        glm::vec3 color;

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            return attributeDescriptions;
        }
    };

    struct LNPipeline {
        VkPipeline graphicsPipeline;
        VkRenderPass renderPass;
        VkPipelineLayout pipelineLayout;
    };

    struct Geometry { // tmp geom bffer
        std::vector<Vertex> Vertices; //gotten
        std::vector<uint32_t> Indices; //gotten

        uint32_t indexBase; //gotten
        uint32_t indexCount; //gotten

        glm::vec3 model; //implement push constants (faster)
        glm::vec3 view; // ^^
        glm::vec3 projection; // ^^
    };

    struct StagingBuffer {
		VkDeviceMemory memory;
		VkBuffer buffer;
	};

    struct GeometryLayer { // geom buffer
        std::vector<Geometry> geometry; //gotten

        std::vector<Vertex> Vertices; //gotten
        std::vector<uint32_t> Indices; //gotten

        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;

        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;
    };
}