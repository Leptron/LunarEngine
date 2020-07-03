#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <tuple>

#include "LunarGUIData.h"

namespace LunarGUI {
    class NodeStyler {
    public:
        NodeStyler();
        ~NodeStyler();

        StyledNode StyleNodes(Stylesheet _stylesheet, Node rootNode);

        std::vector<StyledNode> StyleNode(std::vector<Node> _nodes, std::vector<std::tuple<std::string, std::string>> _pAttrs);
    private:
        Stylesheet _stylesheet;
        Node rootNode;

        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> _attrValues;
        std::vector<StyledNode> nodes;
    private:
        bool check_key(std::string key);
    };
}