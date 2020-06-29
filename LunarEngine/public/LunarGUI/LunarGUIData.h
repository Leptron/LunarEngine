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
        std::vector<Selector> selectors;
        std::vector<Declaration> declarations;
    };  

    struct Stylesheet {
        std::vector<Rule> rules;
    };
}