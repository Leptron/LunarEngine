#include "../../public/LunarGUI/LunarGUICssParser.h"

namespace LunarGUI {
    CssParser::CssParser() {

    }

    CssParser::~CssParser() {

    }

    void CssParser::Parse(std::string input) {
        this->input = input;
    }

    char CssParser::next_char() {
        return input.at(pos + 1);
    }

    bool CssParser::starts_with(std::string s) {
        return input.rfind(s, pos);
    }

    bool CssParser::eof() {
        return pos >= input.length();
    }

    char CssParser::consume_char() {
        char cur_char = input.at(pos + 1);
        pos += 1;

        return cur_char;
    }

    bool CssParser::consume_while_consume(ConsumeType consuming) {
        if(consuming == ConsumeType::WhiteSpace) {
            //TODO Implement
            char nChar = next_char();
            return nChar == ' ';
        } else if (consuming == ConsumeType::Characters) {
            char nChar = next_char();

            bool lCaseTest = std::find(lowerCase.begin(), lowerCase.end(), nChar) != lowerCase.end();
            bool uCaseTest = std::find(upperCase.begin(), upperCase.end(), nChar) != upperCase.end();
            bool nTest = std::find(numerics.begin(), numerics.end(), nChar) != numerics.end();

            bool compare = lCaseTest | uCaseTest | nTest;
            return compare;
        } else if (consuming == ConsumeType::Text) {
            char nChar = next_char();
            return nChar != '<';
        } else if (consuming == ConsumeType::OpenQuote) {
            char nChar = next_char();
            return nChar != '"';
        } else if (consuming == ConsumeType::ValidIdentifierChar) {
            bool lCaseTest = std::find(lowerCase.begin(), lowerCase.end(), c) != lowerCase.end();
            bool uCaseTest = std::find(upperCase.begin(), upperCase.end(), c) != upperCase.end();
            bool nTest = std::find(numerics.begin(), numerics.end(), c) != numerics.end();

            bool uTest = c == '-' || c == '_';

            bool compare = lCaseTest | uCaseTest | nTest | uTest;
            return compare;
        }
    }

    void CssParser::consume_whitespace() {
        consume_while(ConsumeType::WhiteSpace);
    }

    std::string CssParser::consume_while(ConsumeType consuming) {
        std::string result;
        while(!eof() && consume_while_consume(consuming)) {
            result += consume_char();
        }

        return result;
    }

    std::string CssParser::parse_identifier() {
        return consume_while(ConsumeType::ValidIdentifierChar);
    }

    SimpleSelector CssParser::parse_simple_selector() {
        SimpleSelector selector = {};
        selector.tag_name = std::nullopt;
        selector.id = std::nullopt;
        
        std::vector<std::string> _class;
        selector._class = _class;
        while(!eof()) {
            char nChar = next_char();
            if(nChar == '#') {
                consume_char();
                selector.id = parse_identifier();
            } else if(nChar == '.') {
                consume_char();
                selector._class.push_back(parse_identifier());
            } else if (nChar == '*') {
                consume_char();
            } else if(valid_identifier_char(nChar)) {
                selector.tag_name = parse_identifier();
            } else {
                break;
            }
        }

        return selector;
    }

    bool CssParser::valid_identifier_char(char c) {
        bool lCaseTest = std::find(lowerCase.begin(), lowerCase.end(), c) != lowerCase.end();
        bool uCaseTest = std::find(upperCase.begin(), upperCase.end(), c) != upperCase.end();
        bool nTest = std::find(numerics.begin(), numerics.end(), c) != numerics.end();

        bool uTest = c == '-' || c == '_';

        bool compare = lCaseTest | uCaseTest | nTest | uTest;
        return compare;
    }

    Specifity CssParser::specificity(SimpleSelector _simple) {

        int _aCount = 0;
        auto _a = _simple.id.has_value();
        if(_a)
            _aCount = 1;

        auto _b = _simple._class.size();
        int _cCount = 0;
        auto _c = _simple.tag_name.has_value();
        if(_c)
            _cCount += 1;

        Specifity _specific = {};
        _specific.x = _aCount;
        _specific.y = _b;
        _specific.z = _cCount;

        return _specific;
    }

    std::vector<Selector> CssParser::parse_selectors() {
        std::vector<Selector> _selectors;
        std::vector<Specifity> spec;

        while(1) {
            Selector _selector = {};
            _selector.Simple = parse_simple_selector();

            _selectors.push_back(_selector);
            consume_whitespace();

            char nChar = next_char();
            if(nChar == ',') {
                consume_char();
                consume_whitespace();
            } else if (nChar == '{') {
                break;
            } else {
                throw std::runtime_error("Unexpected character");
            }
        }

        while(1) {
            std::vector<Selector> _tmpSelector;
            std::vector<Specifity> _specific;

            for(int i = 0; i < _selectors.size(); i++) {
                Selector _aElem = _selectors[0];
                Selector _bElem;
                if(i + 1 == _selectors.size())
                    _bElem = _selectors[i - 1];
                else
                    _bElem = _selectors[i + 1];

                auto _a_tuple = specificity(_aElem.Simple);
                auto _b_tuple = specificity(_bElem.Simple);
                if(_a_tuple.x < _b_tuple.x) {
                    _specific.push_back(_b_tuple);
                    _specific.push_back(_a_tuple);

                    _tmpSelector.push_back(_bElem);
                    _tmpSelector.push_back(_aElem);
                }
            }


            spec = _specific;
            _selectors = _tmpSelector;

            //check break
            bool sorted = true;
            auto _tVal = spec[0];
            for(int i = 0; i < spec.size() && sorted; i++) {
                auto _sortTest = spec[i];
                if(_tVal.x >= _sortTest.x)
                    sorted = true;
                else
                    sorted = false;
            }

            if(sorted)
                break;
        }

        return _selectors;
    }
}