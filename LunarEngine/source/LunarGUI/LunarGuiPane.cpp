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
        
        CreateNodeList(fileContents);
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

    Node GUIPane::text(std::string data) {
        Node _node = {};

        NodeType _type = {};
        _type.Text = data;
        
        std::vector<Node> _child;
        _node.children = _child;
        _node.node_type = _type;
    }

    Node GUIPane::elem(std::string name, std::unordered_map<std::string, std::string> attributes, std::vector<Node> children) {
        Node _node = {};
        _node.children = children;

        ElementData _elemData = {};
        _elemData.TagName = name;
        _elemData.attribues = attributes;

        NodeType _type = {};
        _type.Element = _elemData;
        _node.node_type = _type;

        return _node;
    }

    void GUIPane::PushStack(int attribIndex) {
        
    }

    void GUIPane::CreateLayout() {
        
    }

    void GUIPane::CreateDrawCommands() {
        //cmdBuffer.clear();
        
    }
}