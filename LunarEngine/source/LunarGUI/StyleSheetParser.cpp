#include "../../public/LunarGUI/StyleSheetParser.h"

namespace LunarGUI {
    StyleSheetParser::StyleSheetParser() {

    }

    StyleSheetParser::~StyleSheetParser() {

    }

    Stylesheet StyleSheetParser::Parse(std::string input) {
        this->input = input;

        characters = std::vector<char>(this->input.begin(), this->input.end());
        bool inDec = false;

        std::string styleName;
        std::vector<std::string> selectors;
        std::unordered_map<std::string, std::string> _rules;

        std::string ruleName;
        std::string ruleValue;
        bool rValue = false;

        std::vector<Rule> l_Rules;

        while(currPos < characters.size()) {
            char c = consumeChar();
            char nc = nextChar();

            std::string compound;
            compound += c;
            compound += nc;

            if(c == ' ' || c == '\n' || c == '\t' || compound == "\r\n")
                continue;
            else if(!inDec && c != '{')
                styleName += c;
            if(!inDec && c == ',') {
                selectors.push_back(styleName);
                styleName = "";
            }
            if(!inDec && c == '{') {
                inDec = true;
                selectors.push_back(styleName);
                styleName = "";
            }

            bool lTest = std::find(validLowerCaseChars.begin(), validLowerCaseChars.end(), c) != validLowerCaseChars.end();
            bool UTest = std::find(validUpperCase.begin(), validUpperCase.end(), c) != validUpperCase.end();
            bool nTest = std::find(validNumbers.begin(), validNumbers.end(), c) != validNumbers.end();
            if(inDec && (lTest || UTest || nTest)) {
                if(!rValue && c == ':')
                    rValue = true;
                if(!rValue && c != ':') {
                    ruleName += c;
                }
                else if(rValue && c != ':' && c != ';')
                    ruleValue += c;

                if(c == ';') {
                    _rules[ruleName] = ruleValue;

                    ruleName = "";
                    ruleValue = "";
                    rValue = false;
                }
            }

            if(inDec && c == '}') {
                inDec = false;

                Rule _rule = {};
                _rule.selectors = selectors;
                _rule.declarations = _rules;

                l_Rules.push_back(_rule);                
            }
        }

        Stylesheet _stylesheet = {};
        _stylesheet.rules = l_Rules;
        return _stylesheet;
    }

    char StyleSheetParser::nextChar() {
        int tmpPos = currPos + 1;
        if(tmpPos > characters.size() - 1)
            return 'EOF';

        return characters[tmpPos];
    }

    char StyleSheetParser::nnChar() {
        int tmpPos = currPos + 2;
        return characters[tmpPos];
    }

    char StyleSheetParser::consumeChar() {
        char retChar = characters[currPos];
        currPos++;

        return retChar;
    }
}