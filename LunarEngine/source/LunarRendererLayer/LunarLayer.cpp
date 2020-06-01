#include "../../public/LunarLayer.h"

namespace LunarRenderer {
    LunarLayer::LunarLayer() {
        
    }

    LunarLayer::LunarLayer(LunarLayerConstructInfo constructInfo) {
        this->construct = constructInfo;
    }

    LunarLayer::~LunarLayer() {

    }
}