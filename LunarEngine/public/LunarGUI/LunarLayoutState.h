#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace LunarGUI {
    struct SpaceObject {
        int height, width;
        int xPos, yPos;
    };

    struct Offsets {
        int offsetHeight, offsetWidth;
    };

    struct SpaceAlloc {
        std::string type;

        int spaceWidth, spaceHeight;
        int nodeIndex;

        std::vector<SpaceObject> objects;
        std::vector<Offsets> offsets;
    };

    class LayoutState {
    private:
        static LayoutState* instance;
        LayoutState();
    public:
        static LayoutState* getInstance();

        //member methods
        void CreateSpaceAllocation(std::string type, int width, int height, int nodeIndex);

    private:
        std::vector<SpaceAlloc> allocations;
    };
}