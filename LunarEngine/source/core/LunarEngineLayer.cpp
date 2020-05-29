#include "../../public/core/LunarEngineLayer.h"

namespace LunarRenderingCore {
    LunarLayer* LunarLayer::layerInstance = nullptr;

    LunarLayer* LunarLayer::GetLayerInstance() {
        if(!layerInstance)
            layerInstance = new LunarLayer;
        
        return layerInstance;
    }

    void LunarLayer::SetupLayer(LunarDataTypes::LayerCamera cameraType, std::string vertFilePath, std::string fragFilePath) {
        prepareGeometry();
        prepareUniformBuffers();
        setupDescriptorSetLayout();
        preparePipelines();
        setupDescriptorPool();
        setupDescriptorSet();
        buildCommandBuffers();
    }

    bool LunarLayer::checkUpdateGeo() {
        return geomUpdated;
    }
}