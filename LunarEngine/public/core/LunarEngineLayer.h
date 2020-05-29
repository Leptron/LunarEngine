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
#include "./LunarDatatypes.h"

#include "../../../base/VulkanTools.h"

namespace LunarRenderingCore {

    struct VertexBuffer {
        VkBuffer buffer;
        VkDeviceMemory memory;
    };


    
    class LunarLayer {    
    private:
        //singleton instance
        static LunarLayer *layerInstance;
        bool geomUpdated = false;

        LunarLayer();
        ~LunarLayer();
        VkShaderModule loadSPIRVShader(std::string filename);

        //preps
        void prepareUniformBuffers();
        void setupDescriptorSetLayout();
        void setupDescriptorPool();
		void setupDescriptorSet();
        void buildCommandBuffers();
        void prepareGeometry();
        void preparePipelines();

        void cleanGeometry();

        //buffer helpers
        uint32_t getMemoryTypeIndex(uint32_t typeBits, VkMemoryPropertyFlags properties);

        std::vector<LunarDataTypes::ObjectData> layerGeometry; // todo implement an entity system so this is all streamlined but i would have to do alloc in the layer
        LunarDataTypes::LayerMarshalData layerNeededVars;

        VkPipelineLayout pipelineLayout;
        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorSet descriptorSet;
        VkPipeline pipeline;

        vks::Buffer vertexBuffer;
        vks::Buffer indexBuffer;
    public:
    
        static LunarLayer *GetLayerInstance();

        void ReceiveVertexData(std::vector<LunarDataTypes::Vertex> verts);
        void SetupLayer(LunarDataTypes::LayerCamera cameraType, std::string vertFilePath, std::string fragFilePath); // does all the allocation
        //get render buffer command
        bool checkUpdateGeo();
    };
}