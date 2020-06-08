#include "../../public/LunarIMGUI.h"

namespace LunarEditor {
    void LunarEditorGUI::initResources(VkRenderPass renderPass, VkQueue copyQueue, const std::string& shadersPath) {
        ImGuiIO& io = ImGui::GetIO();

        //create font texture
        unsigned char* fontData;
        int texWidth, texHeight;
        io.Fonts->GetTexDataAsRGBA32(&fontData, &texWidth, &texHeight);
        VkDeviceSize uploadSize = texWidth * texHeight * 4 * sizeof(char);

        //create target
        VkImageCreateInfo imageInfo = {};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
        imageInfo.extent.width = texWidth;
        imageInfo.extent.height = texHeight;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        if (vkCreateImage(device, &imageInfo, nullptr, &fontImage) != VK_SUCCESS)
            throw std::runtime_error("Failed to create image for texture");

        VkMemoryRequirements memReqs;
        vkGetImageMemoryRequirements(device, fontImage, &memReqs);
        VkMemoryAllocateInfo memAllocInfo = {};
        memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memAllocInfo.allocationSize = memReqs.size;
        memAllocInfo.memoryTypeIndex = manager->findMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        if (vkAllocateMemory(device, &memAllocInfo, nullptr, &fontMemory) != VK_SUCCESS)
            throw std::runtime_error("Failed to allocate font memory");
        if (vkBindImageMemory(device, fontImage, fontMemory, 0) != VK_SUCCESS)
            throw std::runtime_error("failed to bind font memory");

        //image view
        VkImageViewCreateInfo viewInfo = {};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = fontImage;
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
        viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        viewInfo.subresourceRange.levelCount = 1;
        viewInfo.subresourceRange.layerCount = 1;
        if (vkCreateImageView(device, &viewInfo, nullptr, &fontView) != VK_SUCCESS)
            throw std::runtime_error("failed to create imgui image view");

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;

        createBuffer(uploadSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(device, stagingBufferMemory, 0, uploadSize, 0, &data);
        memcpy(data, fontData, (size_t)uploadSize);
        vkUnmapMemory(device, stagingBufferMemory);

        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = manager->commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        VkImageSubresourceRange subresourceRange = {};
        subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        subresourceRange.baseMipLevel = 0;
        subresourceRange.levelCount = 1;
        subresourceRange.layerCount = 1;
        setImageLayout(commandBuffer, fontImage, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, subresourceRange, VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);

        VkBufferImageCopy bufferCopyRegion = {};
        bufferCopyRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        bufferCopyRegion.imageSubresource.layerCount = 1;
        bufferCopyRegion.imageExtent.width = texWidth;
        bufferCopyRegion.imageExtent.height = texHeight;
        bufferCopyRegion.imageExtent.depth = 1;

        vkCmdCopyBufferToImage(
            commandBuffer,
            stagingBuffer,
            fontImage,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            1,
            &bufferCopyRegion
        );

        VkImageSubresourceRange subresourceRangeTwo = {};
        subresourceRangeTwo.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        subresourceRangeTwo.baseMipLevel = 0;
        subresourceRangeTwo.levelCount = 1;
        subresourceRangeTwo.layerCount = 1;
        setImageLayout(commandBuffer, fontImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, subresourceRangeTwo, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);

        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        //create fence
        VkFenceCreateInfo fenceInfo = {};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = 0;

        VkFence fence;
        if (vkCreateFence(device, &fenceInfo, nullptr, &fence) != VK_SUCCESS)
            throw std::runtime_error("failed to create imgui fence");
        //submit to the queue
        if (vkQueueSubmit(manager->graphicsQueue, 1, &submitInfo, fence));
        // Wait for the fence to signal that command buffer has finished executing
        if (vkWaitForFences(device, 1, &fence, VK_TRUE, 100000000000) != VK_SUCCESS)
            throw std::runtime_error("failed to wait for fence");
        vkDestroyFence(device, fence, nullptr);
        vkFreeCommandBuffers(device, manager->commandPool, 1, &commandBuffer);

        vkDestroyBuffer(device, stagingBuffer, nullptr);
        vkFreeMemory(device, stagingBufferMemory, nullptr);

        //font texture sampler
        VkSamplerCreateInfo samplerInfo = {};
        samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerInfo.maxAnisotropy = 1.0f;
        samplerInfo.magFilter = VK_FILTER_LINEAR;
        samplerInfo.minFilter = VK_FILTER_LINEAR;
        samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
        if (vkCreateSampler(device, &samplerInfo, nullptr, &sampler) != VK_SUCCESS)
            throw std::runtime_error("failed to create sampler");

        //descriptor pool
        std::vector<VkDescriptorPoolSize> poolSizes = {
            descriptorPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1)
        };

        VkDescriptorPoolCreateInfo descriptorPoolInfo = {};
        descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        descriptorPoolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
        descriptorPoolInfo.pPoolSizes = poolSizes.data();
        descriptorPoolInfo.maxSets = 2;
        if (vkCreateDescriptorPool(device, &descriptorPoolInfo, nullptr, &descriptorPool) != VK_SUCCESS)
            throw std::runtime_error("failed to create descriptor pool");

        //descriptor set layout
        VkDescriptorSetLayoutBinding setLayoutBindingS = {};
        setLayoutBindingS.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        setLayoutBindingS.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
        setLayoutBindingS.binding = 0;
        setLayoutBindingS.descriptorCount = 1;

        std::vector<VkDescriptorSetLayoutBinding> setLayoutBinding = {
            setLayoutBindingS
        };

        VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo = {};
        descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        descriptorSetLayoutCreateInfo.pBindings = setLayoutBinding.data();
        descriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(setLayoutBinding.size());
        if (vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCreateInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
            throw std::runtime_error("failed to create descriptor layout");

        //descriptor set
        VkDescriptorSetAllocateInfo zallocInfo = {};
        zallocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        zallocInfo.descriptorPool = descriptorPool;
        zallocInfo.pSetLayouts = &descriptorSetLayout;
        zallocInfo.descriptorSetCount = 1;
        if (vkAllocateDescriptorSets(device, &zallocInfo, &descriptorSet) != VK_SUCCESS)
            throw std::runtime_error("failed to allocate descriptor sets");

        VkDescriptorImageInfo fontDescriptor = {};
        fontDescriptor.sampler = sampler;
        fontDescriptor.imageView = fontView;
        fontDescriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

        VkWriteDescriptorSet writeDescriptorSet = {};
        writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writeDescriptorSet.dstSet = descriptorSet;
        writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        writeDescriptorSet.dstBinding = 0;
        writeDescriptorSet.pImageInfo = &fontDescriptor;
        writeDescriptorSet.descriptorCount = 1;

        std::vector<VkWriteDescriptorSet> writeDescriptorSets = {
            writeDescriptorSet,
        };
        vkUpdateDescriptorSets(device, static_cast<uint32_t>(writeDescriptorSets.size()), writeDescriptorSets.data(), 0, nullptr);

        //pipeline cache
        VkPipelineCacheCreateInfo pipelineCacheCreateInfo = {};
        pipelineCacheCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
        if (vkCreatePipelineCache(device, &pipelineCacheCreateInfo, nullptr, &pipelineCache) != VK_SUCCESS)
            throw std::runtime_error("failed to create pipeline cahce");

        //pipeline layout
        // Push constants for UI rendering parameters
        VkPushConstantRange pushConstantRange = {};
        pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
        pushConstantRange.offset = 0;
        pushConstantRange.size = sizeof(pushConstBlock);

        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
        pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutCreateInfo.setLayoutCount = 1;
        pipelineLayoutCreateInfo.pSetLayouts = &descriptorSetLayout;
        pipelineLayoutCreateInfo.pushConstantRangeCount = 1;
        pipelineLayoutCreateInfo.pPushConstantRanges = &pushConstantRange;
        if (vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
            throw std::runtime_error("failed to create pipeline layout");

        //setup graphics pipeline for ui rendering
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyState = {};
        inputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssemblyState.flags = 0;
        inputAssemblyState.primitiveRestartEnable = VK_FALSE;

        VkPipelineRasterizationStateCreateInfo rasterState = {};
        rasterState.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterState.polygonMode = VK_POLYGON_MODE_FILL;
        rasterState.cullMode = VK_CULL_MODE_NONE;
        rasterState.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterState.flags = 0;
        rasterState.depthClampEnable = VK_FALSE;
        rasterState.lineWidth = 1.0f;

        //enable blending
        VkPipelineColorBlendAttachmentState blendAttachmentState = {};
        blendAttachmentState.blendEnable = VK_TRUE;
        blendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        blendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        blendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        blendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
        blendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        blendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        blendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;

        VkPipelineColorBlendStateCreateInfo colorBlendState = {};
        colorBlendState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlendState.attachmentCount = 1;
        colorBlendState.pAttachments = &blendAttachmentState;

        VkPipelineDepthStencilStateCreateInfo depthStencilState = {};
        depthStencilState.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depthStencilState.depthTestEnable = VK_FALSE;
        depthStencilState.depthWriteEnable = VK_FALSE;
        depthStencilState.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
        depthStencilState.back.compareOp = VK_COMPARE_OP_ALWAYS;

        VkPipelineViewportStateCreateInfo viewportState = {};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.scissorCount = 1;
        viewportState.flags = 0;

        VkPipelineMultisampleStateCreateInfo multisampleState = {};
        multisampleState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampleState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        multisampleState.flags = 0;

        std::vector<VkDynamicState> dynamicStateEnables = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR
        };
        VkPipelineDynamicStateCreateInfo dynamicState = {};
        dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicState.pDynamicStates = dynamicStateEnables.data();
        dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStateEnables.size());
        dynamicState.flags = 0;

        std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages = {};

        VkGraphicsPipelineCreateInfo pipelineCreateInfo = {};
        pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineCreateInfo.layout = pipelineLayout;
        pipelineCreateInfo.renderPass = manager->renderPass;
        pipelineCreateInfo.flags = 0;
        pipelineCreateInfo.basePipelineIndex = -1;
        pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;

        pipelineCreateInfo.pInputAssemblyState = &inputAssemblyState;
        pipelineCreateInfo.pRasterizationState = &rasterState;
        pipelineCreateInfo.pColorBlendState = &colorBlendState;
        pipelineCreateInfo.pMultisampleState = &multisampleState;
        pipelineCreateInfo.pViewportState = &viewportState;
        pipelineCreateInfo.pDepthStencilState = &depthStencilState;
        pipelineCreateInfo.pDynamicState = &dynamicState;
        pipelineCreateInfo.stageCount = static_cast<uint32_t>(shaderStages.size());
        pipelineCreateInfo.pStages = shaderStages.data();

        //vertex bindings an attributes based on ImGui vertex definitions
    }
}