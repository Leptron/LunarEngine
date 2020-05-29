#include "../../../public/core/LunarEngineLayer.h"

//droid sans mono

namespace LunarRenderingCore {
    void LunarLayer::ReceiveVertexData(std::vector<LunarDataTypes::Vertex> verts) {
        LunarDataTypes::ObjectData appendageData = {};
        appendageData.vertices = verts;

        layerGeometry.push_back(appendageData);
    }

    uint32_t LunarLayer::getMemoryTypeIndex(uint32_t typeBits, VkMemoryPropertyFlags properties) {
        for(uint32_t i = 0; i < layerNeededVars.deviceMemoryProperties.memoryTypeCount; i++) {
            if((typeBits & 1) == 1) {
                if ((layerNeededVars.deviceMemoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
                    return i;
            }

            typeBits >>= 1;
        }

        throw "Could not find memory type";
    }

    void LunarLayer::prepareGeometry() {
        //iterate over and allocate memory
        std::vector<LunarDataTypes::Vertex> vertices;
        std::vector<uint32_t> indices;
        uint32_t indexBase = 0;

        for (uint32_t i = 0; i < layerGeometry.size(); i++) {
            layerGeometry[i].indexBase = indexBase;
            layerGeometry[i].indexCount = static_cast<uint32_t>(layerGeometry[i].indices.size());

            //vertices
            //Implement uv, color normals stuff like that

            const uint32_t vertexOffset = static_cast<uint32_t>(vertices.size());

            for(uint32_t v = 0; v < layerGeometry[i].vertices.size(); v++) {
                LunarDataTypes::Vertex vert = layerGeometry[i].vertices[v];
                vertices.push_back(vert);
            }

            //indices
            for(uint32_t f = 0; f < layerGeometry[i].indices.size(); f++) {
                indices.push_back(vertexOffset + layerGeometry[i].indices[f]);
            }

            indexBase += layerGeometry[i].indices.size();

            layerGeometry[i].vertices.clear();
            layerGeometry[i].indices.clear();
        }

        //create the buffers
        //we create only one index and vertex buffer for performance reasons
        size_t vertexDataSize = vertices.size() * sizeof(LunarDataTypes::Vertex);
        size_t indexDataSize = indices.size() * sizeof(uint32_t);

        struct StagingBuffer {
            VkDeviceMemory memory;
            VkBuffer buffer;
        };

        struct {
            StagingBuffer vertices;
            StagingBuffer indices;
        } stagingBuffers;

        struct {
            VkBuffer vertexBuffer;
            VkBuffer indexBuffer;
        } targetBuffer;

        //vertex buffer, staging buffer
        VkBufferCreateInfo vertexStagingBufferInfo = {};
        vertexStagingBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        vertexStagingBufferInfo.size = static_cast<uint32_t>(vertexDataSize);
        vertexStagingBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        
        // Create a host-visible buffer to copy the vertex data to (staging buffer)
        VK_CHECK_RESULT(vkCreateBuffer(layerNeededVars.passedDevice, &vertexStagingBufferInfo, nullptr, &stagingBuffers.vertices.buffer));

        //create memory backing up the buffer handle
        VkMemoryRequirements memReqs;
        VkMemoryAllocateInfo memAlloc = vks::initializers::memoryAllocateInfo();
        vkGetBufferMemoryRequirements(layerNeededVars.passedDevice, stagingBuffers.vertices.buffer, &memReqs);
        memAlloc.allocationSize = memReqs.size;
        //find a memory type index that fits the properties of the buffer
        memAlloc.memoryTypeIndex = getMemoryTypeIndex(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        VK_CHECK_RESULT(vkAllocateMemory(layerNeededVars.passedDevice, &memAlloc, nullptr, &stagingBuffers.vertices.memory));

        void *mapped;
        VK_CHECK_RESULT(vkMapMemory(layerNeededVars.passedDevice, stagingBuffers.vertices.memory, 0, memAlloc.allocationSize, 0, &mapped));
        memcpy(mapped, vertices.data(), vertexDataSize);
        vkUnmapMemory(layerNeededVars.passedDevice, stagingBuffers.vertices.memory);

        VK_CHECK_RESULT(vkBindBufferMemory(layerNeededVars.passedDevice, stagingBuffers.vertices.buffer, stagingBuffers.vertices.memory, 0));
    }

    void LunarLayer::cleanGeometry() {
        //free all the allocated memory that we used
        for(auto geometry : layerGeometry) {
            
        }

        layerGeometry.clear();
    }
}