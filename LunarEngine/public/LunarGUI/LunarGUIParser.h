#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <tuple>
#include <iostream>

#include "LunarGUIData.h"

namespace LunarGUI {
    enum ConsumeType {
        WhiteSpace,
        Characters,
        Text,
        OpenQuote
    };

    class Parser {
    public:
        Parser();
        ~Parser();

        Node Parse(std::string input);

    private:

        char next_char();
        bool starts_with(std::string s);
        bool eof();


        char consume_char();

        std::string consume_while(ConsumeType consuming);
        bool consume_while_consume(ConsumeType consuming);

        void consume_whitespace();
        std::string parse_tag_name();

        Node parse_text();
        Node parse_element();

        Node text(std::string data);

        std::unordered_map<std::string, std::string> parse_attributes();
        std::tuple<std::string, std::string> parse_attr();
        std::string parse_attr_value();

        std::vector<Node> parse_nodes();
        Node parse_node();
        Node elem(std::string name, std::unordered_map<std::string, std::string> attributes, std::vector<Node> children);
    private:
        size_t pos;
        std::string input;

        std::vector<char> lowerCase = {
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
            't', 'u', 'v', 'w', 'x', 'y', 'z',
        };

        std::vector<char> upperCase = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
        };

        std::vector<char> numerics = {
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'  
        };
    };
}