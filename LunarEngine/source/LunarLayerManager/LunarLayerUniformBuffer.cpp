#include "../../public/LunarLayerManager.h"

namespace LunarRenderer {
    void LayerManager::createDescriptorSetLayout() {
        VkDescriptorSetLayoutBinding uboLayoutBinding = {};
        uboLayoutBinding.binding = 0;
        uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        uboLayoutBinding.descriptorCount = 1;
        uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutCreateInfo layoutInfo = {};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = 1;
        layoutInfo.pBindings = &uboLayoutBinding;

        if(vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
            throw std::runtime_error("failed to create a descriptor set layout");
    }

    void LayerManager::createUniformBuffers(ThreeDObject& object) {
        VkDeviceSize bufferSize = sizeof(ProjectionMatricies);

        object.uniformBuffers.resize(swapChainImages.size());
        object.uniformBuffersMemory.resize(swapChainImages.size());

        for(size_t i = 0; i < 1; i++) {
            createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, object.uniformBuffers[i], object.uniformBuffersMemory[i]);
        }
    }

    void LayerManager::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to create buffer!");
        }

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate buffer memory!");
        }

        vkBindBufferMemory(device, buffer, bufferMemory, 0);
    }

    uint32_t LayerManager::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }

        throw std::runtime_error("failed to find suitable memory type!");
    }

    void LayerManager::createDescriptorPool() {
        VkDescriptorPool descriptorPool;

        VkDescriptorPoolSize poolSize{};
        poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSize.descriptorCount = static_cast<uint32_t>(BLOCK_COUNT + 1);

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = 1;
        poolInfo.pPoolSizes = &poolSize;

        poolInfo.maxSets = static_cast<uint32_t>(BLOCK_COUNT);

        if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }

        descriptorPools.push_back(descriptorPool);
    }

    void LayerManager::createDescirptorSets(BufferLayer& m_buf) {
        for(auto& object : m_buf.objects) {
            VkDescriptorSetAllocateInfo allocateInfo{};
            allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
            allocateInfo.descriptorPool = descriptorPools[m_buf.poolIndex];
            allocateInfo.descriptorSetCount = 1;
            allocateInfo.pSetLayouts = &descriptorSetLayout;
            if(vkAllocateDescriptorSets(device, &allocateInfo, &object.descriptorSet) != VK_SUCCESS)
                throw std::runtime_error("failed to alloc descriptor set");

            for(size_t i = 0; i < 1; i++) {
                VkDescriptorBufferInfo bufferInfo = {};
                bufferInfo.buffer = object.uniformBuffers[i];
                bufferInfo.offset = 0;
                bufferInfo.range = sizeof(ProjectionMatricies);

                std::array<VkWriteDescriptorSet, 1> writeDescriptorSets = {};
                writeDescriptorSets[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                writeDescriptorSets[0].dstSet = object.descriptorSet;
                writeDescriptorSets[0].dstBinding = 0;
                writeDescriptorSets[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                writeDescriptorSets[0].descriptorCount = 1;
                writeDescriptorSets[0].pBufferInfo = &bufferInfo;

                vkUpdateDescriptorSets(device, static_cast<uint32_t>(writeDescriptorSets.size()), writeDescriptorSets.data(), 0, nullptr);
            }
        }
    }

    void LayerManager::updateUniformBuffer() {
        for(auto layer : buffers) {
            for(auto& object : layer.objects) {
                auto id = object.ID;
                //get proj matricies 
                ProjectionMatricies ubo = objectProjectionID[id];
                ubo.view = cameraView;
                ubo.proj[1][1] *= -1;

                void* data;
                vkMapMemory(device, object.uniformBuffersMemory[0], 0, sizeof(ubo), 0, &data);
                    memcpy(data, &ubo, sizeof(ubo));
                vkUnmapMemory(device, object.uniformBuffersMemory[0]);
            }
        }
    }
}