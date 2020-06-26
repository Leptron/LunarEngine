#pragma once

namespace LunarGUI {
    struct Node {
        std::vector<Node> children;
        NodeType node_type;
    };

    struct NodeType {
        std::string Text;
        ElementData Element;
    };

    struct ElementData {
        std::string TagName;
        std::unordered_map<std::string, std::string> attribues;
    };

    enum DrawPrimitive {
        Box
    };

    enum BasicColor {
        White,
        Black
    };

    struct DrawCommand {
        DrawPrimitive cmd;
        BasicColor clearColor;

        int width, height;
        int xPos, yPos;
    };
}