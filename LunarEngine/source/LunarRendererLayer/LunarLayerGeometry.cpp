#include "../../public/LunarRenderer.h"

namespace LunarRenderer {
    int LunarRenderer::AddGeometry(Geometry addGeometry) {
        this->tmpGeometryBuffer.push_back(addGeometry);
        return tmpGeometryBuffer.size() - 1;
    }

    int LunarRenderer::FlushGeometry() {
        GeometryLayer layer = {};
        std::vector<Geometry> unflushedGeom = tmpGeometryBuffer;
        tmpGeometryBuffer.clear();

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        uint32_t indexBase = 0;

        for(auto unflushedGeo : unflushedGeom) {
            auto appGeo = unflushedGeo;
            appGeo.indexBase = indexBase;

            for(auto vert : unflushedGeo.Vertices)
                vertices.push_back(vert);
            for(auto index : unflushedGeo.Indices)
                indices.push_back(index);

            layer.geometry.push_back(appGeo);
        }

        layer.Vertices = vertices;
        layer.Indices = indices;

        createVertexBuffer(vertices, layer);
        createIndexBuffer(indices, layer);

        layers.push_back(layer);

        return 0;
    }

    void LunarRenderer::cleanAllLayers() {
        for (auto layer : layers) {
            vkDestroyBuffer(device, layer.indexBuffer, nullptr);
            vkFreeMemory(device, layer.indexBufferMemory, nullptr);

            vkDestroyBuffer(device, layer.vertexBuffer, nullptr);
            vkFreeMemory(device, layer.vertexBufferMemory, nullptr);
        }
    }



    void LunarRenderer::FlushToCommandBuffer() {
        //gen the command buffers
        commandBuffers.resize(swapChainFrameBuffers.size());

        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

        if(vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
            throw std::runtime_error("Failed to allocate the command buffers");

        for(size_t i = 0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo = {};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = 0; // Optional
            beginInfo.pInheritanceInfo = nullptr; // Optional
            
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

            for(auto layer : layers) {
                

                VkBuffer vertexBuffers[] = {
                    layer.vertexBuffer
                };
                VkDeviceSize offsets[] = {0};

                vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, &layer.vertexBuffer, offsets);
                vkCmdBindIndexBuffer(commandBuffers[i], layer.indexBuffer, 0, VK_INDEX_TYPE_UINT32);

                for (auto mesh : layer.geometry) {
                    vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, materialIndex[mesh.materialIndex].pipeline);
                    vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, materialIndex[mesh.materialIndex].pipelineLayout, 0, 1, &uboMem[mesh.uboMemIndex].descriptorSets[i], 0, nullptr);
                    vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t>(mesh.Indices.size()), 1, 0, mesh.indexBase, 0);
                }
            }

            vkCmdEndRenderPass(commandBuffers[i]);

            if(vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
                throw std::runtime_error("failed to record command buffer");
        }
    }
}