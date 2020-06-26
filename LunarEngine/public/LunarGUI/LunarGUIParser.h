#pragma once

#include <string>

namespace LunarGUI {
    class Parser {
    public:
        Parser();
        ~Parser();

        void Parse(std::string input);

    private:

        char next_char();
        bool starts_with(std::string s);
        bool eof();

    private:
        size_t pos;
        std::string input;
    };
}