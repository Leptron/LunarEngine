#include "../../public/LunarGUI/LunarLayoutAllocator.h"

namespace LunarGUI {
    LayoutAllocater::LayoutAllocater() {

    }

    LayoutAllocater::~LayoutAllocater() {

    }

    LBlock LayoutAllocater::AllocateBlock(LayoutBox _box, LBlock _parent) {
        LBlock _retBox;

        BoxTypeE _bType = _box.box_type._boxType;
        if(_bType == BoxTypeE::BlockNode && _parent.nodeName.empty() && _box.nodeName == "GUIPane") {
            _retBox.width = sWidth;
            _retBox._dims = {0, 0};

            for (auto _child : _box.children) {
                _retBox._children.push_back(AllocateBlock(_child, _retBox));
            }
        } else {
            _retBox.width = CalculateBlockWidth(_box, _parent);
            
            for (auto _child : _box.children) {
                _retBox._children.push_back(AllocateBlock(_child, _retBox));
            }
        }

        return _retBox;
    }

    int LayoutAllocater::CalculateBlockWidth(LayoutBox _box, LBlock _parentBox) {
        auto _properties = _box._properties;
        std::string pxIdentifier = "px";
        std::string percentIndentifer = "%";

        std::string unparsedWidth = "auto";
        int width = 0;

        for(auto _prop : _properties) {
            auto key = std::get<0>(_prop);
            auto val = std::get<1>(_prop);

            if(key == "width")
                unparsedWidth = val;
        }

        if(unparsedWidth != "auto") {
            char l = unparsedWidth.back();
            if(l == 'x') {
                size_t pos = unparsedWidth.find(pxIdentifier);
                if(pos != std::string::npos)
                    unparsedWidth.erase(pos, pxIdentifier.length());

                std::stringstream w(unparsedWidth);
                w >> width;
            } else if(l == '%') {
                size_t pos = unparsedWidth.find(percentIndentifer);
                if(pos != std::string::npos)
                    unparsedWidth.erase(pos, percentIndentifer.length());

                std::stringstream p(unparsedWidth);
                int percentage = 0;

                p >> percentage;
                width = _parentBox.width / percentage;
            }
        }

        auto total = width;
        if(unparsedWidth != "auto" && total > _parentBox.width) {
            //implement later
        }

        int underflow = _parentBox.width - total;
        if(unparsedWidth == "auto") {
            if(underflow >= 0) {
                width = underflow;
            }
        }

        return width;
    }

    Dims LayoutAllocater::CaluculateBlockPosition(LayoutBox _box, LBlock _parentBox) {
        Dims _retDims = {};

        return _retDims;
    }
}