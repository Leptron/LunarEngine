#include "../../public/LunarGUI/LunarGuiPane.h"

namespace LunarGUI {
    GUIPane::GUIPane() {

    }

    GUIPane::~GUIPane() {

    }

    void GUIPane::CreatePane(std::string loc, int width, int height) {
        std::string cssLoc = "shaders/style.css";
        
        std::string fileContents;
        std::string cssContents;

        this->width = width;
        this->height = height;

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

        std::FILE *fpp = std::fopen(cssLoc.c_str(), "rb");
        if(fpp) {
            std::string contents;
            std::fseek(fpp, 0, SEEK_END);
            contents.resize(std::ftell(fpp));

            std::rewind(fpp);
            std::fread(&contents[0], 1, contents.size(), fpp);
            std::fclose(fpp);
            cssContents = contents;
        }

        XMLParser _parser;
        rootNode = _parser.Parse(fileContents);
        
        StyleSheetParser _styleSheetParser;
        _stylesheet = _styleSheetParser.Parse(cssContents);

        NodeStyler _styler;
        _styledNodes = _styler.StyleNodes(_stylesheet, rootNode);

        LayoutManager lManager;
        _layoutTree = lManager.BuildLayoutTree(_styledNodes.children[0]);

        LayoutAllocater _allocator;
        _allocator.AllocateBlock(_layoutTree, {});
    }

    void GUIPane::UpdateScreenDims(int width, int height) {
        this->width = width;
        this->height = height;

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