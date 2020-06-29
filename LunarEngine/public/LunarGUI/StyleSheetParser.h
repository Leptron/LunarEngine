#pragma once

#include "LunarGUIData.h"

#include <string>
#include <vector>

namespace LunarGUI {
    class StyleSheetParser {
    public:
        StyleSheetParser();
        ~StyleSheetParser();

        //TODO : Set the return of a stylesheet element
        void Parse(std::string input);
    private:
        std::string input;
        std::vector<char> characters;
    };
}