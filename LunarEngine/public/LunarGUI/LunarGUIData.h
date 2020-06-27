#pragma once

#include <vector>
#include <string>
#include <unordered_map>

namespace LunarGUI {
    struct ElementData {
        std::string TagName;
        std::unordered_map<std::string, std::string> attribues;
    };

    struct NodeType {
        std::string Text;
        ElementData Element;
    };

    enum DrawPrimitive {
        Box
    };

    enum BasicColor {
        White,
        Black
    };

    struct Node {
        std::vector<Node> children;
        NodeType node_type;
    };
}