#include "../../public/LunarGUI/LunarLayoutState.h"

namespace LunarGUI {
    LayoutState* LayoutState::instance = 0;

    LayoutState* LayoutState::getInstance() {
        if(instance == 0)
            instance = new LayoutState();

        return instance;
    }

    void LayoutState::CreateSpaceAllocation(std::string type, int width, int height, int nodeIndex) {
        SpaceAlloc _alloc = {};
        _alloc.nodeIndex = nodeIndex;
        _alloc.spaceWidth = width;
        _alloc.spaceHeight = height;
        _alloc.type = type;
    }

    LayoutState::LayoutState() {

    }
}