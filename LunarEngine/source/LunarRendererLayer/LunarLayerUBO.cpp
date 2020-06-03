#include "../../public/LunarRenderer.h"

namespace LunarRenderer {
    void LunarRenderer::CreateGeomUBO(int layer) {
        auto refLayer = layers[layer];
        for(auto& geom : refLayer.geometry) {
            VkDeviceSize bufferSize = sizeof(Geometry::Matrices);
            UBOMemory mem = {};
            mem.uniformBuffers.resize(swapChainImages.size());
            mem.uniformBuffersMemory.resize(swapChainImages.size());

            for (size_t i = 0; i < swapChainImages.size(); i++) {
                createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, mem.uniformBuffers[i], mem.uniformBuffersMemory[i]);
            }
            uboMem.push_back(mem);
            geom.uboMemIndex = uboMem.size() - 1;
        }
    }

    void LunarRenderer::setupDescriptors() {
        VkDescriptorSetLayoutBinding uboLayoutBinding{};
        uboLayoutBinding.binding = 0;
        uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        uboLayoutBinding.descriptorCount = 1;

        uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = 1;
        layoutInfo.pBindings = &uboLayoutBinding;

        if (vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) 
            throw std::runtime_error("failed to create descriptor set layout!");
    }

    void LunarRenderer::createDescriptorPool() {
        VkDescriptorPoolSize poolSize{};
        poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSize.descriptorCount = static_cast<uint32_t>(swapChainImages.size());


        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = 1;
        poolInfo.pPoolSizes = &poolSize;

        poolInfo.maxSets = static_cast<uint32_t>(swapChainImages.size());;

        if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS)
            throw std::runtime_error("failed to create descriptor pool!");
    }

    void LunarRenderer::createDescriptorSets() {

        for(auto layer : layers) {
            for(auto& geom : layer.geometry) {
                std::vector<VkDescriptorSetLayout> layouts(swapChainImages.size(), descriptorSetLayout);
                VkDescriptorSetAllocateInfo allocInfo{};
                allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
                allocInfo.descriptorPool = descriptorPool;
                allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImages.size());
                allocInfo.pSetLayouts = layouts.data();

                uboMem[geom.uboMemIndex].descriptorSets.resize(swapChainImages.size());
                if (vkAllocateDescriptorSets(device, &allocInfo, uboMem[geom.uboMemIndex].descriptorSets.data()) != VK_SUCCESS) {
                    throw std::runtime_error("failed to allocate descriptor sets!");
                }
                for (size_t i = 0; i < swapChainImages.size(); i++) {
                    VkDescriptorBufferInfo bufferInfo{};
                    bufferInfo.buffer = uboMem[geom.uboMemIndex].uniformBuffers[i];
                    bufferInfo.offset = 0;
                    bufferInfo.range = sizeof(Geometry::Matrices);  

                    VkWriteDescriptorSet descriptorWrite{};
                    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                    descriptorWrite.dstSet = uboMem[geom.uboMemIndex].descriptorSets[i];
                    descriptorWrite.dstBinding = 0;
                    descriptorWrite.dstArrayElement = 0;
                    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                    descriptorWrite.descriptorCount = 1;
                    descriptorWrite.pBufferInfo = &bufferInfo;             

                    vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);
                }
            }
        }
    }
}