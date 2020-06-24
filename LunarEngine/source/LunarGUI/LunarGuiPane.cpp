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

        fileContents.erase(std::remove(fileContents.begin(), fileContents.end(), '\n'), fileContents.end());
        fileContents.erase(std::remove(fileContents.begin(), fileContents.end(), '\t'), fileContents.end());
        
        CreateNodeList(fileContents);
    }

    void GUIPane::CreateNodeList(std::string contents) {
        std::string tmpNode;
        bool startTag = false;

        for(std::string::size_type i = 0; i < contents.size(); i++) {
            if(contents[i] == '<') {
                startTag = true;
                continue;
            }
            if(contents[i] == '>') {
                startTag = false;

                GUINode _node = {};
                _node.nodeName = tmpNode;
                if(tmpNode[0] == '/')
                    _node.endTag = true;
                else
                    _node.endTag = false;
                nodeList.push_back(_node);

                tmpNode = "";
                continue;
            }
                
            if(!startTag && contents[i] == ' ')
                continue;
            if(startTag)
                tmpNode += contents[i];
        }

        for(auto _node : nodeList) {
            std::stringstream ss(_node.nodeName);
            
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;

            std::vector<std::string> attributes(begin, end);
            
            if(attributes.size() > 1) {
                attributes.erase(attributes.begin());
                std::cout << attributes[0] << std::endl;
                std::vector<std::tuple<std::string, std::string>> _tmpAttributes;

                GUINodeAttrib _nodeAttrib = {};
                _nodeAttrib.hasAttrib = true;
                _nodeAttrib.endTag = _node.endTag;

                _nodeAttrib.nodeName = _node.nodeName;
                _nodeAttrib.attributes = _tmpAttributes;
            } else {
                GUINodeAttrib _nodeAttrib = {};
                _nodeAttrib.endTag = _node.endTag;
                _nodeAttrib.hasAttrib = false;

                _nodeAttrib.nodeName = _node.nodeName;
            }
        }
    }
}