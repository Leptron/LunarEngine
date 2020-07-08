#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <optional>
#include <tuple>

namespace LunarGUI {
    struct ElementData {
        std::string TagName;
        std::unordered_map<std::string, std::string> attribues;
    };

    enum ConsumeType {
        WhiteSpace,
        Characters,
        Text,
        OpenQuote,
        ValidIdentifierChar,
        Float
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
        std::string nodeType;
        std::vector<Node> children;

        bool textNode;
        std::string text;
        std::unordered_map<std::string, std::string> attributes;
    };

    struct SimpleSelector {
        std::optional<std::string> tag_name;
        std::optional<std::string> id;
        std::vector<std::string> _class;
    };

    enum Unit {
        Px,
        None,
    };
    
    struct Color {
        int r;
        int g;
        int b;
        int a;
    };  

    struct Specifity {
        size_t x;
        size_t y;
        size_t z;
    };

    struct Value {
        std::string Keyword;
        std::tuple<float, Unit> length;
        Color color_value;
    };

    struct Declaration {
        std::string name;
        Value value;
    };

    struct Selector {
        SimpleSelector Simple;
    };

    struct Rule {
        std::vector<std::string> selectors;
        std::unordered_map<std::string, std::string> declarations;
    };  

    struct Stylesheet {
        std::vector<Rule> rules;
    };

    enum Display {
        Inline,
        Block,
        NoneD,
    };

    struct StyledNode {
        Node* node;
        Display _displayType;

        std::vector<std::tuple<std::string, std::string>> _properties;
        std::vector<StyledNode> children;
        std::string nodeName;
    };

    enum BoxTypeE {
        BlockNode,
        InlineNode,
        AnonymousBlock
    };

    struct BoxTypeS {
        BoxTypeE _boxType;
        StyledNode* _node;
    };

    struct EdgeSizes {
        float left;
        float right;
        float top;
        float bottom;
    };

    struct Rect {
        float x;
        float y;
        float width;
        float height;
    };

    struct Dimensions {
        Rect content;

        EdgeSizes padding;
        EdgeSizes border;
        EdgeSizes margin;
    };

    struct LayoutBox {
        Dimensions dimensions;
        BoxTypeS box_type;
        bool anonBox;

        std::vector<LayoutBox> children;
        std::string nodeName;
        std::vector<std::tuple<std::string, std::string>> _properties;
    };
}