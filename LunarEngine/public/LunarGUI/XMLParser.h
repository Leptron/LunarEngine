#pragma once

#include "LunarGUIData.h"

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>

namespace LunarGUI {
    class XMLParser {
    public:
        XMLParser();
        ~XMLParser();

        Node Parse(std::string input);

    private:
        std::vector<Node> parseNodes();
        bool _break = false;

        Node parseNode();
        Node parseText();
    private:
        //utility
        char nextChar();
        char nnChar();
        char consumeChar();

        bool whitespace();
        bool tagname();
        
        std::string consumeTagName();
        std::string consumeText();
        void consumeEndTag();
        void consumeWhiteSpace();
    private:
        std::vector<char> validLowerCaseChars = {
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
            'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
        };

        std::vector<char> validUpperCase = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
        };

        std::vector<char> validNumbers = {
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
        };
    private:
        std::string input;

        std::vector<char> characters;
        int currPos = 0;
    };
}