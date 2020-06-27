#include "../../public/LunarGUI/LunarGUIParser.h"

namespace LunarGUI {
    Parser::Parser() {

    }

    Parser::~Parser() {

    }

    Node Parser::Parse(std::string input) {
        this->input = input;

        auto _nodes = parse_nodes();
        
        if(_nodes.size() == 1)
            return _nodes[0];
        
        std::unordered_map<std::string, std::string> _attr;
        return elem("html", _attr, _nodes);
    }

    char Parser::next_char() {
        return input.at(pos + 1);
    }

    bool Parser::starts_with(std::string s) {
        return input.rfind(s, pos);
    }

    bool Parser::eof() {
        return pos >= input.length();
    }

    char Parser::consume_char() {
        char cur_char = input.at(pos + 1);
        pos += 1;

        return cur_char;
    }

    bool Parser::consume_while_consume(ConsumeType consuming) {
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
        }
    }

    void Parser::consume_whitespace() {
        consume_while(ConsumeType::WhiteSpace);
    }

    std::string Parser::parse_tag_name() {
        return consume_while(ConsumeType::Characters);
    }

    std::string Parser::consume_while(ConsumeType consuming) {
        std::string result;
        while(!eof() && consume_while_consume(consuming)) {
            result += consume_char();
        }

        return result;
    }

    Node Parser::text(std::string data) {
        Node _node = {};

        NodeType _type = {};
        _type.Text = data;
        
        std::vector<Node> _child;
        _node.children = _child;
        _node.node_type = _type;

        return _node;
    }

    Node Parser::parse_text() {
        return text(consume_while(ConsumeType::Text));
    }

    Node Parser::parse_element() {
        if(consume_char()  != '<')
            throw std::runtime_error("parsing error parse element");

        auto tag_name = parse_tag_name();
        auto attributes = parse_attributes();
        if(consume_char() != '>')
            throw std::runtime_error("parsing error parse element");

        //contents
        auto _children = parse_nodes();

        //closing tag
        if(consume_char() != '<')
            throw std::runtime_error("parsing error parse element");
        if(consume_char() != '/')
            throw std::runtime_error("parsing error parse element");
        if(parse_tag_name() != tag_name)
            throw std::runtime_error("parsing error parse element");
        if(consume_char() != '>')
            throw std::runtime_error("parsing error parse element");

        return elem(tag_name, attributes, _children);
    }

    std::unordered_map<std::string, std::string> Parser::parse_attributes() {
        std::unordered_map<std::string, std::string> attributes;
        while(1) {
            consume_whitespace();
            if(next_char() == '>')
                break;
            
            auto _vTup = parse_attr();
            attributes[std::get<0>(_vTup)] = std::get<1>(_vTup);
        }

        return attributes;
    }

    std::tuple<std::string, std::string> Parser::parse_attr() {
        auto _name = parse_tag_name();
        if(consume_char() == '=')
            throw std::runtime_error("parsing error for attribute parsing");
        auto _value = parse_attr_value();

        auto _vTup = std::make_tuple(_name, _value);
        return _vTup;
    }

    std::string Parser::parse_attr_value() {
        auto _open_quoute = consume_char();
        if(_open_quoute == '"' || _open_quoute == '\'')
            throw std::runtime_error("parsing error, attribute value");
        auto _val = consume_while(ConsumeType::OpenQuote);
        if(consume_char() == _open_quoute)
            throw std::runtime_error("parsing error attrib value");
        
        return _val;
    }

    Node Parser::parse_node() {
        if(next_char() == '<') {
            return parse_element();
        } else {
            return parse_text();
        }
    }

    std::vector<Node> Parser::parse_nodes() {
        std::vector<Node> _nodes;

        while(1) {
            consume_whitespace();
            if(eof() || starts_with("</"))
                break;

            _nodes.push_back(parse_node());
        }

        return _nodes;
    }

    Node Parser::elem(std::string name, std::unordered_map<std::string, std::string> attributes, std::vector<Node> children) {
        Node _node = {};
        _node.children = children;

        ElementData _elemData = {};
        _elemData.TagName = name;
        _elemData.attribues = attributes;

        NodeType _type = {};
        _type.Element = _elemData;
        _node.node_type = _type;

        return _node;
    }
}