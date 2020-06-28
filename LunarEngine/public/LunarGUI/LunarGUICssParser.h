#pragma once

#include "LunarGUIData.h"
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <string>

#include <sstream>


namespace LunarGUI {
    enum ConsumeType {
        WhiteSpace,
        Characters,
        Text,
        OpenQuote,
        ValidIdentifierChar,
        Float
    };

    class CssParser {
    public:
        CssParser();
        ~CssParser();

        void Parse(std::string input);
    private:
        char next_char();
        bool starts_with(std::string s);
        bool eof();
        bool valid_identifier_char(char c);


        char consume_char();

        std::string consume_while(ConsumeType consuming);
        bool consume_while_consume(ConsumeType consuming);
        std::string parse_identifier();

        void consume_whitespace();

        SimpleSelector parse_simple_selector();
        Specifity specificity(SimpleSelector _simple);

        std::vector<Selector> parse_selectors();

        Rule parse_rule();
        std::vector<Rule> parse_rules();

        std::vector<Declaration> parse_declarations();
        Declaration parse_declaration();

        Value parse_value();
        Value parse_length();
        Value parse_color();

        float parse_float();
        Unit parse_unit();
        int parse_hex_pair();
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