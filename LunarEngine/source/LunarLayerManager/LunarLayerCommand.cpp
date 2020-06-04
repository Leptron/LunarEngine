#include "../../public/LunarLayerManager.h"

namespace LunarRenderer {
    void LayerManager::FlushCommandBuffer(std::vector<VkCommandBuffer>& commandBuffers) {
        commandBuffers.resize(swapChainFrameBuffers.size());

        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

        if(vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
            throw std::runtime_error("failed to allocate command buffers");

        for(size_t i = 0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo = {};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if(vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
                throw std::runtime_error("failed to begin recording command buffer");
            
            VkClearValue clearValues[2];
            clearValues[0].color = {0.0f, 0.0f, 0.0f, 1.0f};
            clearValues[1].depthStencil = { 1.0f, 0 };

            VkRenderPassBeginInfo renderPassInfo = {};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = renderPass;
            renderPassInfo.framebuffer = swapChainFrameBuffers[i];
            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = swapChainExtent;
            renderPassInfo.clearValueCount = 2;
            renderPassInfo.pClearValues = clearValues;

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            for(auto layer : buffers) {
                VkDeviceSize offsets[] = {0};

                vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, &layer.vertexBuffer, offsets);
                vkCmdBindIndexBuffer(commandBuffers[i], layer.indexBuffer, 0, VK_INDEX_TYPE_UINT32);

                for(auto object : layer.objects) {
                    VkPipeline bPipeline = materials[object.materialIndex].pipeline;
                    VkPipelineLayout bPipelineLayout = materials[object.materialIndex].pipelineLayout;

                    vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, bPipeline);
                    vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, bPipelineLayout, 0, 1, &object.descriptorSet, 0, nullptr);
                    vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t>(object.indices.size()), 1, 0, object.indexBase, 0);
                }
            }

            vkCmdEndRenderPass(commandBuffers[i]);
            if(vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
                throw std::runtime_error("failed to record command buffer");
        }        
    }
}