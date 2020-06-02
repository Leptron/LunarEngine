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
        glm::vec3 pos;
        glm::vec3 color;
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

        struct {
			StagingBuffer vertices; //finished doing this bufferve
			StagingBuffer indices;
		} stagingBuffers;

        struct {
            VkDeviceMemory memory;
            VkBuffer buffer;
        } vertexBuffer;

        struct {
            VkDeviceMemory memory;
            VkBuffer buffer;
            uint32_t count;
        } indexBuffer;


    };
}