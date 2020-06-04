#include "../../public/LunarLayerManager.h"

namespace LunarRenderer {
    void LayerManager::allocateBufferMemory(BufferLayer& m_buf) {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        for(auto object : m_buf.objects) {
            for(auto vert : object.vertices)
                vertices.push_back(vert);
            for(auto index : object.indices)
                indices.push_back(index);
        }

        m_buf.vertices = vertices;
        m_buf.indices = indices; //safety

        VkDeviceSize vertexBufferSize = sizeof(vertices[0]) * vertices.size();
        VkBuffer vertexStagingBuffer;
        VkDeviceMemory vertexStagingBufferMemory;

        createBuffer(vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertexStagingBuffer, vertexStagingBufferMemory);

        void *vData;
        vkMapMemory(device, vertexStagingBufferMemory, 0, vertexBufferSize, 0, &vData);
            memcpy(vData, vertices.data(), (size_t)vertexBufferSize);
        vkUnmapMemory(device, vertexStagingBufferMemory);

        createBuffer(vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_buf.vertexBuffer, m_buf.vertexBufferMemory);
        copyBuffer(vertexStagingBuffer, m_buf.vertexBuffer, vertexBufferSize);

        vkDestroyBuffer(device, vertexStagingBuffer, nullptr);
        vkFreeMemory(device, vertexStagingBufferMemory, nullptr);

        VkDeviceSize indexBufferSize = sizeof(indices[0]) * indices.size();

        VkBuffer indexStagingBuffer;
        VkDeviceMemory indexStagingBufferMemory;
        createBuffer(indexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, indexStagingBuffer, indexStagingBufferMemory);

        void *iData;
        vkMapMemory(device, indexStagingBufferMemory, 0, indexBufferSize, 0, &iData);
            memcpy(iData, indices.data(), (size_t)indexBufferSize);
        vkUnmapMemory(device, indexStagingBufferMemory);

        createBuffer(indexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_buf.indexBuffer, m_buf.indexBufferMemory);

        copyBuffer(indexStagingBuffer, m_buf.indexBuffer, indexBufferSize);

        vkDestroyBuffer(device, indexStagingBuffer, nullptr);
        vkFreeMemory(device, indexStagingBufferMemory, nullptr); 
    }

    void LayerManager::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize Dsize) {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

            VkBufferCopy copyRegion{};
            copyRegion.size = Dsize;
            vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(graphicsQueue);

        vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
    }
}