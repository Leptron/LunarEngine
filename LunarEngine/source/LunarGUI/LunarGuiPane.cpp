#include "../../public/LunarGUI/LunarGuiPane.h"

namespace LunarGUI {
    GUIPane::GUIPane() {

    }

    GUIPane::~GUIPane() {

    }

    void GUIPane::CreatePane(std::string loc, int width, int height) {
        std::string fileContents;

        this->width = width;
        this->height = height;
        LayoutState::getInstance()->UpdateDims(this->width, this->height);

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

        fileContents.erase(std::remove(fileContents.begin(), fileContents.end(), '\n'), fileContents.end());
        fileContents.erase(std::remove(fileContents.begin(), fileContents.end(), '\t'), fileContents.end());
        
        Parser _parser;
        Node rootNode = _parser.Parse(fileContents);
    }

    void GUIPane::UpdateScreenDims(int width, int height) {
        this->width = width;
        this->height = height;

        LayoutState::getInstance()->UpdateDims(this->width, this->height);
        CreateDrawCommands();
    }

    void GUIPane::CreateNodeList(std::string contents) {
                

        CreateLayout();
        CreateDrawCommands();
    }

    void GUIPane::PushStack(int attribIndex) {
        
    }

    void GUIPane::CreateLayout() {
        
    }

    void GUIPane::CreateDrawCommands() {
        //cmdBuffer.clear();
        
    }
}