#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vulkan/vulkan.h>

#include "../../../base/VulkanBuffer.hpp"
//#include "../../../base/VulkanTexture.hpp"

namespace LunarDataTypes {
    struct Vertex {
        float position[3];
        float color[3];
        // float uv[2]; : TODO Implement UV's later
    };

    enum LayerCamera {
            TwoDimensional,
            ThreeDimensional
    };

    struct MVPMatrixUniform {
        glm::mat4 projectionMatrix;
        glm::mat4 modelMatrix;
        glm::mat4 viewMatrix;
    };

    struct ObjectData {
        std::vector<Vertex> vertices; //cleared after loaded into gpu

        //Index data
        std::vector<uint32_t> indices; // cleared after loaded into gpu
        uint32_t indexCount;

        uint32_t indexBase;
    };

    struct LayerMarshalData {
        VkDevice passedDevice;
        VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
    };
}