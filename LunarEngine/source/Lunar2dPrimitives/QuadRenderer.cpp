#include "../../public/Lunar2dRendering/QuadRenderer.h"

namespace Lunar2DPrimitives {
    Quad::Quad() {

    }

    Quad::~Quad() {

    }

    void Quad::AttachLayerManager(LunarRenderer::LayerManager* Lmanager) {
        this->layerManager = Lmanager;
        
    }
}