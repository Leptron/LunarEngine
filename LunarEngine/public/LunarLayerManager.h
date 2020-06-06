#pragma once
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
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
#include <tuple>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <map>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstdint>

#include "LunarVkDatatypes.h"

namespace LunarRenderer {

    #define BLOCK_COUNT 16

    struct ThreeDObject {
        std::vector<Vertex> vertices; //gotten
        std::vector<uint32_t> indices; //gotten

        int bufferLayerIndex;

        int materialIndex; //gotten
        std::string matID; // gotten

        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;
        VkDescriptorSet descriptorSet;

        //needs index base
        uint32_t indexBase; 
        uint32_t indexCount;

        bool singular;

        std::string ID;
    };

    struct BufferLayer {
        std::vector<ThreeDObject> objects;

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;

        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;

        int poolIndex;
    };

    struct LayerMaterial {
        std::string matID;
        VkPipeline pipeline;
        VkPipelineLayout pipelineLayout;
    };

    struct ProjectionMatricies {
        alignas(16) glm::mat4 model;
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 proj;
    };

    struct LunarLayerConstruction {
        VkDevice device;
        VkExtent2D swapChainExtent;
        VkRenderPass renderPass;
        std::vector<VkImage> swapChainImages;
        VkPhysicalDevice physicalDevice;
        VkCommandPool commandPool;
        VkQueue graphicsQueue;
        std::vector<VkFramebuffer> swapChainFrameBuffers;
    };

    class LayerManager {
    public:
        LayerManager();
        LayerManager(LunarLayerConstruction *construction);

        ~LayerManager();

    public:
        void CreateObject(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::string requestedMaterial, bool singular, std::string id);
        void AllocateObjects();
        void FlushCommandBuffer(std::vector<VkCommandBuffer>& commandBuffers);
        void updateUniformBuffer();

        //cleaning commands
        void CleanMaterials();
        void CleanAllStorageBuffers();
        void CleanAllUBO();

        //rebuilding commands
        void RebuildMaterials(VkRenderPass* rPass);
        void RecreateUBO();

        void ReAttachComponents(LunarLayerConstruction *construction);

        //update specific uniforms
        void UpdateObjectUniform(ProjectionMatricies newMatricies, std::string id);
        VkExtent2D swapChainExtent;
    private:
        VkDevice device;
        VkRenderPass renderPass;
        std::vector<VkImage> swapChainImages;
        VkPhysicalDevice physicalDevice;
        std::vector<VkDescriptorPool> descriptorPools;
        VkCommandPool commandPool;
        VkQueue graphicsQueue;
        std::vector<VkFramebuffer> swapChainFrameBuffers;

        std::vector<BufferLayer> buffers;
        std::vector<ThreeDObject> objects;

        std::vector<LayerMaterial> materials;
        std::vector<std::string> matidList;

        std::map<std::string, ProjectionMatricies> objectProjectionID;

        //camera projection
        glm::mat4 cameraView;

    protected:
        VkDescriptorSetLayout descriptorSetLayout;

    private:
        //helper functions
        void createDescriptorSetLayout();
        void createDescriptorPool();
        void createDescirptorSets(BufferLayer& m_buf);

        

        void allocateBufferMemory(BufferLayer& m_buf);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize Dsize);

        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        //per object uniforms
        void createUniformBuffers(ThreeDObject& object);

        void createRequestedMaterial(std::string requestedMaterial);
        //shaders
        static std::vector<char> readFile(const std::string& filename);
        VkShaderModule createShaderModule(const std::vector<char>& code);

        //flush
        
    };
}