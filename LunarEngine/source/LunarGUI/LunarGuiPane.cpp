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

        CreateDrawCommands();
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
                _node.index = nodeList.size();

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
                std::string aNodeName = attributes[0];
                attributes.erase(attributes.begin());
                std::vector<std::tuple<std::string, std::string>> _tmpAttributes;

                //attribute
                std::string attribName;
                std::string attribValue;
                bool attribValueBol = false;

                for(auto attrib : attributes) {
                    for(std::string::size_type i = 0; i < attrib.size(); i++) {
                        if(attrib[i] == '=') {
                            attribValueBol = true;
                            continue;
                        }
                        
                        if(!attribValueBol)
                            attribName += attrib[i];
                        if(attribValueBol)
                            attribValue += attrib[i];
                    }

                    auto _attrib = std::make_tuple(attribName, attribValue);
                    _tmpAttributes.push_back(_attrib);

                    attribName = "";
                    attribValue = "";
                    attribValueBol = false;
                }

                GUINodeAttrib _nodeAttrib = {};
                _nodeAttrib.hasAttrib = true;
                _nodeAttrib.endTag = _node.endTag;
                _nodeAttrib.index = _node.index;

                _nodeAttrib.nodeName = aNodeName;
                _nodeAttrib.attributes = _tmpAttributes;
                nodeAttribList.push_back(_nodeAttrib);
            } else {
                GUINodeAttrib _nodeAttrib = {};
                _nodeAttrib.endTag = _node.endTag;
                _nodeAttrib.hasAttrib = false;
                _nodeAttrib.index = _node.index;

                _nodeAttrib.nodeName = _node.nodeName;
                nodeAttribList.push_back(_nodeAttrib);
            }
        }

        for(int i = 0; i < nodeAttribList.size() ; i++) { 
            if(nodeAttribList[i].endTag)
                continue;
            PushStack(i);
        }

        CreateLayout();
        CreateDrawCommands();
    }

    void GUIPane::PushStack(int attribIndex) {
        int duplicateCount = 0;
        auto _node = nodeAttribList[attribIndex];
        std::string endNodeConstruct = '/' + _node.nodeName;

        for(int i = attribIndex + 1; i != nodeAttribList.size(); i++) {
            auto _tNode = nodeAttribList[i];
            if(_tNode.nodeName == _node.nodeName)
                duplicateCount++;
            if(_tNode.endTag && duplicateCount != 0 && _tNode.nodeName == endNodeConstruct)
                duplicateCount -= 1;

            if(_tNode.endTag && duplicateCount == 0 && _tNode.nodeName == endNodeConstruct) {
                Stack _stack = {};
                _stack.startNode = attribIndex;
                _stack.endNode = i;
                _stack.stackElem = _node.nodeName;
                _stack.attributes = _node.attributes;

                stack.push_back(_stack);
                break;
            }
        }
    }

    void GUIPane::CreateLayout() {
        std::unordered_map<int, int> calculatedWidths;
        std::unordered_map<int, int> calculatedHeights;
        std::string layout = "block";


        for(int i = 0; i < stack.size(); i++) {
            auto _stack = stack[i];
            bool hasChild = false;

            for(auto _pChild : stack) {
                if(_stack.startNode <= _pChild.startNode && _pChild.startNode <= _stack.endNode && _stack.startNode != _pChild.startNode) {
                    hasChild = true;
                }
            }

            if(hasChild)
                LayoutState::getInstance()->CreateSpaceAllocation(layout, this->width, this->height, i);
        }
    }

    void GUIPane::CreateDrawCommands() {
        cmdBuffer.clear();
        
    }
}