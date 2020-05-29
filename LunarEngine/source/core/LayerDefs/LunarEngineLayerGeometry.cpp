#include "../../../public/core/LunarEngineLayer.h"

namespace LunarRenderingCore {
    void LunarLayer::ReceiveVertexData(std::vector<LunarDataTypes::Vertex> verts) {
        LunarDataTypes::ObjectData appendageData = {};
        appendageData.vertices = verts;

        layerGeometry.push_back(appendageData);
    }

    void LunarLayer::prepareGeometry() {
        //iterate over and allocate memory
        for(LunarDataTypes::ObjectData geometry : layerGeometry) {
            uint32_t vertexBufferSize = static_cast<uint32_t>(geometry.vertices.size()) * sizeof(LunarDataTypes::Vertex);

            //set up indicies
            geometry.indexCount = static_cast<uint32_t>(geometry.indices.size());
            uint32_t indexBufferSize = geometry.indexCount * sizeof(uint32_t);
        }
    }

    void LunarLayer::cleanGeometry() {
        //free all the allocated memory that we used
        for(auto geometry : layerGeometry) {
            
        }

        layerGeometry.clear();
    }
}