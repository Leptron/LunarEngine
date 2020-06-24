#include "../../public/LunarGUI/LunarGuiPane.h"

namespace LunarGUI {
    GUIPane::GUIPane() {

    }

    GUIPane::~GUIPane() {

    }

    void GUIPane::CreatePane(std::string loc) {
        std::string fileContents;

        std::FILE *fp = std::fopen(loc.c_str(), "rb");
        if(fp) {
            std::string contents;
            std::fseek(fp, 0, SEEK_END);
            contents.resize(std::ftell(fp));

            std::rewind(fp);
            std::fread(&contents[0], 1, contents.size(), fp);
            std::fclose(fp);
            fileContents = contents;
        }

        
    }
}