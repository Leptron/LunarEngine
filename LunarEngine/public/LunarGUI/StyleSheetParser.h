#pragma once

#include "LunarGUIData.h"

#include <string>
#include <vector>
#include <iostream>

namespace LunarGUI {
    class StyleSheetParser {
    public:
        StyleSheetParser();
        ~StyleSheetParser();

        //TODO : Set the return of a stylesheet element
        Stylesheet Parse(std::string input);
    private:
        std::string input;
        std::vector<char> characters;
        int currPos = 0;

        std::vector<char> validLowerCaseChars = {
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
            'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
        };

        std::vector<char> validUpperCase = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
        };

        std::vector<char> validNumbers = {
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '#', ':', ';', '-'
        };
    private:
        //utility
        char nextChar();
        char nnChar();
        char consumeChar();
    };
}