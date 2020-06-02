#include "../../public/LunarRenderer.h"

namespace LunarRenderer {
    int LunarRenderer::AddGeometry(Geometry addGeometry) {
        this->tmpGeometryBuffer.push_back(addGeometry);
        return tmpGeometryBuffer.size() - 1;
    }

    int LunarRenderer::FlushGeometry() {
        //bases
        uint32_t indexBase = 0;
        //create our layer
        GeometryLayer newLayer = {};
        std::vector<Geometry> flushGeometry;

        for(auto Geom : tmpGeometryBuffer) {
            Geometry flushGeo = {};
            flushGeo.indexBase = indexBase;
            flushGeo.indexCount = static_cast<uint32_t>(Geom.Indices.size());
            flushGeo.Vertices = Geom.Vertices;
            flushGeo.Indices = Geom.Indices;

            for(auto v : Geom.Vertices)
                newLayer.Vertices.push_back(v);
                
            for(auto i : Geom.Indices)
                newLayer.Indices.push_back(i);

            flushGeometry.push_back(flushGeo);
            indexBase += static_cast<uint32_t>(Geom.Indices.size());
        }

        tmpGeometryBuffer.clear();
        newLayer.geometry = flushGeometry;

        uint32_t vertexBufferSize = static_cast<uint32_t>(newLayer.Vertices.size());
        uint32_t indexBufferSize = static_cast<uint32_t>(newLayer.Indices.size());

        VkMemoryAllocateInfo memAlloc = {};
		memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		VkMemoryRequirements memReqs;

		void *data;

        VkBufferCreateInfo vertexBufferInfo = {};
        vertexBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        vertexBufferInfo.size = vertexBufferSize;
        // Buffer is used as the copy source
		vertexBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        // Create a host-visible buffer to copy the vertex data to (staging buffer)
        VK_CHECK_RESULT(vkCreateBuffer(device, &vertexBufferInfo, nullptr, &newLayer.stagingBuffers.vertices.buffer));
        vkGetBufferMemoryRequirements(device, newLayer.stagingBuffers.vertices.buffer, &memReqs);
        memAlloc.allocationSize = memReqs.size;
        // Request a host visible memory type that can be used to copy our data do
		// Also request it to be coherent, so that writes are visible to the GPU right after unmapping the buffer
        memAlloc.memoryTypeIndex = getMemoryTypeIndex(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        VK_CHECK_RESULT(vkAllocateMemory(device, &memAlloc, nullptr, &newLayer.stagingBuffers.vertices.memory));
        //map and copy
        VK_CHECK_RESULT(vkMapMemory(device, newLayer.stagingBuffers.vertices.memory, 0, memAlloc.allocationSize, 0, &data));
        memcpy(data, newLayer.Vertices.data(), vertexBufferSize);
        vkUnmapMemory(device, newLayer.stagingBuffers.vertices.memory);
        VK_CHECK_RESULT(vkBindBufferMemory(device, newLayer.stagingBuffers.vertices.buffer, newLayer.stagingBuffers.vertices.memory, 0));

        //create a device local buffer which the vertex data will be copied to
        vertexBufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        VK_CHECK_RESULT(vkCreateBuffer(device, &vertexBufferInfo, nullptr, &newLayer.vertexBuffer.buffer));
        vkGetBufferMemoryRequirements(device, newLayer.vertexBuffer.buffer, &memReqs);
        memAlloc.allocationSize = memReqs.size;
        memAlloc.memoryTypeIndex = getMemoryTypeIndex(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        VK_CHECK_RESULT(vkAllocateMemory(device, &memAlloc, nullptr, &newLayer.vertexBuffer.memory));
        VK_CHECK_RESULT(vkBindBufferMemory(device, newLayer.vertexBuffer.buffer, newLayer.vertexBuffer.memory, 0));

        //index buffer
        VkBufferCreateInfo indexbufferInfo = {};
        indexbufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        indexbufferInfo.size = indexBufferSize;
        indexbufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        // Copy index data to a buffer visible to the host (staging buffer)
        VK_CHECK_RESULT(vkCreateBuffer(device, &indexbufferInfo, nullptr, &newLayer.stagingBuffers.indices.buffer));
        vkGetBufferMemoryRequirements(device, newLayer.stagingBuffers.indices.buffer, &memReqs);
        memAlloc.allocationSize = memReqs.size;
        memAlloc.memoryTypeIndex = getMemoryTypeIndex(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        VK_CHECK_RESULT(vkAllocateMemory(device, &memAlloc, nullptr, &newLayer.stagingBuffers.indices.memory));
        VK_CHECK_RESULT(vkMapMemory(device, newLayer.stagingBuffers.indices.memory, 0, indexBufferSize, 0, &data));
        memcpy(data, newLayer.Indices.data(), indexBufferSize);
        vkUnmapMemory(device, newLayer.stagingBuffers.indices.memory);
        VK_CHECK_RESULT(vkBindBufferMemory(device, newLayer.stagingBuffers.indices.buffer, newLayer.stagingBuffers.indices.memory, 0));

        //create destination buffer
        indexbufferInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        VK_CHECK_RESULT(vkCreateBuffer(device, &indexbufferInfo, nullptr, &newLayer.indexBuffer.buffer));
        vkGetBufferMemoryRequirements(device, newLayer.indexBuffer.buffer, &memReqs);
        memAlloc.allocationSize = memReqs.size;
        memAlloc.memoryTypeIndex = getMemoryTypeIndex(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        VK_CHECK_RESULT(vkAllocateMemory(device, &memAlloc, nullptr, &newLayer.indexBuffer.memory));
        VK_CHECK_RESULT(vkBindBufferMemory(device, newLayer.indexBuffer.buffer, newLayer.indexBuffer.memory, 0));

        //buffer copies need to be submitted to a queue
        VkCommandBuffer copyCmd = getLayerCommandBuffer(true);
        VkBufferCopy copyRegion = {};
        
        //vertex buffer
        copyRegion.size = vertexBufferSize;
        vkCmdCopyBuffer(copyCmd, newLayer.stagingBuffers.vertices.buffer, newLayer.vertexBuffer.buffer, 1, &copyRegion);
        //index buffer
        copyRegion.size = indexBufferSize;
        vkCmdCopyBuffer(copyCmd, newLayer.stagingBuffers.indices.buffer, newLayer.indexBuffer.buffer, 1, &copyRegion);

        //flush command buffer
        layerFlushCommandBuffer(copyCmd);

        //destroy staging buffers
        vkDestroyBuffer(device, newLayer.stagingBuffers.vertices.buffer, nullptr);
        vkFreeMemory(device, newLayer.stagingBuffers.vertices.memory, nullptr);
        vkDestroyBuffer(device, newLayer.stagingBuffers.indices.buffer, nullptr);
        vkFreeMemory(device, newLayer.stagingBuffers.indices.memory, nullptr);
    
        this->layer.push_back(newLayer);
        return this->layer.size() - 1;
    }

    void LunarRenderer::cleanAllLayers() {
        for(auto l : this->layer) {
            vkDestroyBuffer(device, l.vertexBuffer.buffer, nullptr);
            vkFreeMemory(device, l.vertexBuffer.memory, nullptr);

            vkDestroyBuffer(device, l.indexBuffer.buffer, nullptr);
            vkFreeMemory(device, l.indexBuffer.memory, nullptr);
        }
    }

    uint32_t LunarRenderer::getMemoryTypeIndex(uint32_t typeBits, VkMemoryPropertyFlags properties) {
        for (uint32_t i = 0; i < deviceMemoryProperties.memoryTypeCount; i++) {
            if ((typeBits & 1) == 1) {
                if ((deviceMemoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
                    return i;
            }

            typeBits >>= 1;
        }

        throw "Could not find a suitable memory type!";
    }

    VkCommandBuffer LunarRenderer::getLayerCommandBuffer(bool begin) {
        VkCommandBuffer cmdBuffer;

        VkCommandBufferAllocateInfo cmdBufAllocateInfo = {};
        cmdBufAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        cmdBufAllocateInfo.commandPool = commandPool;
        cmdBufAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        cmdBufAllocateInfo.commandBufferCount = 1;

        VK_CHECK_RESULT(vkAllocateCommandBuffers(device, &cmdBufAllocateInfo, &cmdBuffer));

        if(begin) {
            VkCommandBufferBeginInfo cmdBufInfo = {};
            cmdBufInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            VK_CHECK_RESULT(vkBeginCommandBuffer(cmdBuffer, &cmdBufInfo));
        }

        return cmdBuffer;
    }

    void LunarRenderer::layerFlushCommandBuffer(VkCommandBuffer commandBuffer) {
        assert(commandBuffer != VK_NULL_HANDLE);

        VK_CHECK_RESULT(vkEndCommandBuffer(commandBuffer));

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        VkFenceCreateInfo fenceCreateInfo = {};
        fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceCreateInfo.flags = 0;
        VkFence fence;
        VK_CHECK_RESULT(vkCreateFence(device, &fenceCreateInfo, nullptr, &fence));  

        //submit to the queue
        VK_CHECK_RESULT(vkQueueSubmit(graphicsQueue, 1, &submitInfo, fence));
        // Wait for the fence to signal that command buffer has finished executing
        VK_CHECK_RESULT(vkWaitForFences(device, 1, &fence, VK_TRUE, 100000000000));

        vkDestroyFence(device, fence, nullptr);
        vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
    }

    void LunarRenderer::FlushToCommandBuffer(int index) {
        
    }
}