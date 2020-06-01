#include "../../public/LunarLayer.h"

namespace LunarRenderer {
    int LunarLayer::AddGeometry(Geometry addGeometry) {
        tmpGeometryBuffer.push_back(addGeometry);
        
        if(geomIndex == 0) {
            return geomIndex;
        } else {
            return geomIndex += 1;
        }
    }

    int LunarLayer::FlushGeometry() {
        //allocate stuff
        GeometryBuffer geomBuffer = {};
        geomBuffer.geometry = tmpGeometryBuffer;
        tmpGeometryBuffer.clear();
        geomIndex++;

        //allocation jazz
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        uint32_t indexBase = 0;

        for (Geometry& allocGeom : geomBuffer.geometry) {
            allocGeom.indexBase = indexBase;
            allocGeom.indexCount = allocGeom.Indices.size();

            const uint32_t vertexOffset = static_cast<uint32_t>(vertices.size());   

            for(uint32_t v = 0; v < allocGeom.Vertices.size(); v++) {
                vertices.push_back(allocGeom.Vertices[v]);
            }

            for(uint32_t f = 0; f < allocGeom.Indices.size(); f++)
                indices.push_back(allocGeom.Indices[f] + vertexOffset);

            indexBase += allocGeom.Indices.size();
        }

        //create buffers
        size_t vertexDataSize = vertices.size() * sizeof(Vertex);
		size_t indexDataSize = indices.size() * sizeof(uint32_t);

        VkMemoryAllocateInfo memAlloc = {};
        memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        VkMemoryRequirements memReqs;

        void *data;

        struct StagingBuffer {
			VkDeviceMemory memory;
			VkBuffer buffer;
		};

		struct {
			StagingBuffer vertices;
			StagingBuffer indices;
		} stagingBuffers;

        //vertex buffer


        if(currGeomLayer == 0) {
            return currGeomLayer;
        } else {
            return currGeomLayer += 1;
        }
    }
}