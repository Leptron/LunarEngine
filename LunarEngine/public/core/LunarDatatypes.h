#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vulkan/vulkan.h>
#include <string>

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

    //for view and projection
    struct VPMatrixUniform {
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
    };

    //for model
    struct MMatrixUniform {
        glm::mat4 *modelMatrix = nullptr;
    };

    struct ObjectData {
        std::vector<Vertex> vertices; //cleared after loaded into gpu

        //Index data
        std::vector<uint32_t> indices; // cleared after loaded into gpu
        uint32_t indexCount;

        uint32_t indexBase;

        LunarShader material;
        //needs material but that depends on shader
    };

    struct LayerMarshalData {
        VkDevice passedDevice;
        VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
        VkCommandPool cmdPool;
        VkQueue queue;
        VkPhysicalDevice physicalDevice;
    };

    struct LunarShaderRequest {
        std::string      shader;
    };

    struct LunarShader {
        VkPipelineLayout      pipelineLayout;
        VkPipeline            pipeline;
        VkDescriptorSet       descriptorSet;
        VkDescriptorSetLayout descriptorSetLayout;

        VkBuffer              uniformBuffer;
        VkDeviceMemory        uniformMemory;
    };
}