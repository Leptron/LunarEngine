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
    struct LNPipeline {
        VkPipeline graphicsPipeline;
        VkRenderPass renderPass;
        VkPipelineLayout pipelineLayout;
    };

    struct GeometryLayer {
        std::vector<GeometryBuffer> GeometryList;
    };

    struct Vertex {
        glm::vec3 pos;
        glm::vec3 color;
    };

    struct GeometryBuffer {
        std::vector<Geometry> geometry;

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

    struct Geometry {
        std::vector<Vertex> Vertices;
        std::vector<uint32_t> Indices;

        uint32_t indexBase;
        uint32_t indexCount;

        struct Matrices {
			glm::mat4 projection;
			glm::mat4 view;
			glm::mat4 model;
		} matrices;

        VkDescriptorSet descriptorSet;
        LunarBuffer uniformBuffer;
        glm::vec3 pos; //implement push constants (faster)
        glm::vec3 rot; // ^^
    };  
}