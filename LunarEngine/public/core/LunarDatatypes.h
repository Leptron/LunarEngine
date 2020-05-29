#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vulkan/vulkan.h>

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
        std::vector<Vertex> vertices;
        VkBuffer vertexBuffer; // Handle to the Vulkan buffer object that the memory is bound to
        VkDeviceMemory vertexBufferMemory; // Handle to the device memory for this buffer

        //Index data
        std::vector<uint32_t> indices;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;
        uint32_t indexCount;
    };

    struct LayerMarshalData {
        VkDevice passedDevice;
    };
}