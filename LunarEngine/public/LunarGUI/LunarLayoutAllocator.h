#pragma once
#include "LunarLayout.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <math.h>
#include <iostream>
#include <tuple>
#include <sstream>

namespace LunarGUI {
    enum BlockType {
        _INLINE,
        _ANON,
        _BLOCK
    };

    struct BlockAllocDims {
        int width;
        int height;
    };

    struct offset {
        int width;
        int height;
        int blockID;
    };

    struct Dims {
        int x, y;
    };

    struct LBlock {
        int width, height;
        Dims _dims;

        std::vector<LBlock> _children;
        std::string nodeName;
    };

    class LayoutAllocater {
    public:
        LayoutAllocater();
        ~LayoutAllocater();

        LBlock AllocateBlock(LayoutBox _box, LBlock _parent);
        
    private:
        int CalculateBlockWidth(LayoutBox _box, LBlock _parentBox);
        Dims CaluculateBlockPosition(LayoutBox _box, LBlock _parentBox);

        int currBlockId = 0;

        int sWidth = 1280;
        int sHeight = 720;
    };
}