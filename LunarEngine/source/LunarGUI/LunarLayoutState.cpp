#include "../../public/LunarGUI/LunarLayoutState.h"

namespace LunarGUI {
    LayoutState* LayoutState::instance = 0;

    LayoutState* LayoutState::getInstance() {
        if(instance == 0)
            instance = new LayoutState();

        return instance;
    }

    void LayoutState::CreateSpaceAllocation(std::string type, int width, int height, int nodeIndex) {
        std::cout << "Creating Layout : " << type << std::endl;

        SpaceAlloc _alloc = {};
        _alloc.nodeIndex = nodeIndex;
        _alloc.spaceWidth = width;
        _alloc.spaceHeight = height;
        _alloc.type = type;

        Offsets _offsetBasic = {};
        _offsetBasic.offsetHeight = "100p";
        _offsetBasic.offsetWidth  = "0";

        std::vector<SpaceObject> _objects;
        
        std::vector<Offsets> _offsets;
        _offsets.push_back(_offsetBasic);

        _alloc.offsets = _offsets;
        _alloc.objects = _objects;

        allocations.push_back(_alloc);
    }

    void LayoutState::RequestObject(std::string reqWidth, std::string reqHeight, int nodeIndex) {

    }

    void LayoutState::UpdateDims(int width, int height) {
        this->width = width;
        this->height = height;
    }

    LayoutState::LayoutState() {

    }
}