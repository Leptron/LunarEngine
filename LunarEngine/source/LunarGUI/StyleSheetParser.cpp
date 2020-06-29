#include "../../public/LunarGUI/StyleSheetParser.h"

namespace LunarGUI {
    StyleSheetParser::StyleSheetParser() {

    }

    StyleSheetParser::~StyleSheetParser() {

    }

    void StyleSheetParser::Parse(std::string input) {
        this->input = input;
    }
}