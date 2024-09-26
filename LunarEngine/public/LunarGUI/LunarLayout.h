#pragma once

#include "LunarGUIData.h"
#include <iostream>

namespace LunarGUI {
    class LayoutManager {
    public:
        LayoutManager();
        ~LayoutManager();

        LayoutBox BuildLayoutTree(StyledNode _sNode);

    private:
        LayoutBox* get_inline_container(LayoutBox& root);
    };
}