#include "../../public/LunarGUI/XMLParser.h"

namespace LunarGUI {
    XMLParser::XMLParser() {

    }

    XMLParser::~XMLParser() {

    }

    Node XMLParser::Parse(std::string input) {
        this->input = input;

        characters = std::vector<char>(this->input.begin(), this->input.end());

        std::vector<Node> nodes = parseNodes();

        Node rootNode = {};
        rootNode.children = nodes;
        rootNode.textNode = false;
        rootNode.nodeType = "root";

        return rootNode;
    }

    std::vector<Node> XMLParser::parseNodes() {
        std::vector<Node> nodes;

        while(!_break) {
            consumeWhiteSpace();
            
            std::string compound;
            compound += nextChar();
            compound += nnChar();

            
            if(_break)
                break;
            if(currPos == characters.size() - 1 || compound == "</")
                break;

            if (characters[currPos] == ' ')
                consumeChar();
            if (characters[currPos] == '\n')
                consumeChar();
            if (characters[currPos] == '\t')
                consumeChar();
            if (characters[currPos] == '\r\n')
                consumeChar();
            if(characters[currPos] == '<')
                nodes.push_back(parseNode());
            else
                nodes.push_back(parseText());
        }

        return nodes;
    }

    Node XMLParser::parseNode() {
        if(consumeChar() != '<')
            std::cout << "ok" << std::endl;

        char n_char = nextChar();
        std::string tagName;

        while(n_char != '>') {
            tagName += consumeChar();
            n_char = nextChar();
        }
        
        tagName += consumeChar();
        consumeChar();

        auto _children = parseNodes();

        consumeChar();
        consumeChar();

        std::string endTagName;
        n_char = nextChar();
        while(n_char != '>') {
            endTagName += consumeChar();
            n_char = nextChar();
        }

        endTagName += consumeChar();
        
        consumeChar();
        if(endTagName == "/GUIPane")
            _break = true;

        std::stringstream ss(tagName);
        std::string token;
        std::vector<std::string> tok;
        while(std::getline(ss, token, ' '))
            tok.push_back(token);
        
        std::string name = tok[0];
        tok.erase(tok.begin());
        
        std::unordered_map<std::string, std::string> _attributes;
        for(auto _tok : tok) {
            bool valFound = false;
            std::string identifier;
            std::string value;

            std::vector<char> _tokCharacters;
            _tokCharacters = std::vector<char>(_tok.begin(), _tok.end());

            //loop through the characters
            for(auto _char : _tokCharacters) {
                if(_char == '=') {
                    valFound = true;
                    continue;
                } else if(!valFound) {
                    identifier += _char;
                } else if(valFound) {
                    value += _char;
                }
            }

            _attributes[identifier] = value;
        }

        Node _node = {};
        _node.textNode = false;
        _node.children = _children;
        _node.attributes = _attributes;
        _node.nodeType = name;        

        return _node;
    }

    Node XMLParser::parseText() {
        Node _node = {};

        std::string text;
        char n_char = nextChar();
        while(n_char != '<') {
            text += consumeChar();
            n_char = nextChar();
        }

        _node.textNode = true;
        _node.text = text;

        return _node;
    }

    char XMLParser::nextChar() {
        int tmpPos = currPos + 1;
        return characters[tmpPos];
    }

    char XMLParser::nnChar() {
        int tmpPos = currPos + 2;
        return characters[tmpPos];
    }

    char XMLParser::consumeChar() {
        char retChar = characters[currPos];
        currPos++;

        return retChar;
    }

    std::string XMLParser::consumeTagName() {
        bool test = true;
        std::string value;

        while(test) {
            char nChar = nextChar();

            bool tOne = std::find(validLowerCaseChars.begin(), validLowerCaseChars.end(), nChar) != validLowerCaseChars.end();
            bool tTwo = std::find(validUpperCase.begin(), validUpperCase.end(), nChar) != validUpperCase.end();
            bool tThree = std::find(validNumbers.begin(), validNumbers.end(), nChar) != validNumbers.end();

            test = tOne || tTwo || tThree;


            value += consumeChar();
        }

        return value;
    }

    void XMLParser::consumeEndTag() {
        bool test = true;

        while(test) {
            char nChar = nextChar();
            test = nChar != '>';

            if(test)
                consumeChar();
        }

        consumeChar();
    }

    bool whiteSpace(char nChar) {
        bool test;
        test = nChar == ' ' || nChar == '\n' || nChar == '\t' || nChar == '\r';

        return test;
    }

    void XMLParser::consumeWhiteSpace() {
        while(true) {
            if(whiteSpace(nextChar()))
                consumeChar();
            else
                break;
        }
    }
}