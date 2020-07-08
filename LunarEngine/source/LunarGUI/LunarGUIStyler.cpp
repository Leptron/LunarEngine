#include "../../public/LunarGUI/LunarGUIStyler.h"

namespace LunarGUI {
    NodeStyler::NodeStyler() {

    }

    NodeStyler::~NodeStyler() {

    }

    StyledNode NodeStyler::StyleNodes(Stylesheet _stylesheet, Node rootNode) {
        this->_stylesheet = _stylesheet;
        this->rootNode = rootNode;

        for(auto _rule : _stylesheet.rules) {
            for(auto _selector : _rule.selectors) {
                if(!check_key(_selector))
                    _attrValues[_selector] = std::unordered_map<std::string, std::string>();

                for(std::pair<std::string, std::string> elem : _rule.declarations) {
                    _attrValues[_selector][elem.first] = elem.second;
                    //std::cout << _attrValues[_selector][elem.first] << std::endl;
                }
            }
        }

        std::vector<Node> _n = {
            rootNode
        };

        std::vector<std::tuple<std::string, std::string>> _pAttrs = {
            //std::make_tuple("clear", "black")
        };
        auto _output = StyleNode(_n, _pAttrs);

        return _output[0];
    }

    std::vector<StyledNode> NodeStyler::StyleNode(std::vector<Node> _nodes, std::vector<std::tuple<std::string, std::string>> _pAttrs) {
        std::vector<StyledNode> _styled_nodes;

        for(auto _node : _nodes) {
            StyledNode _sNode = {};

            std::vector<std::string> selector;

            if(_node.attributes.find("id") == _node.attributes.end()) {
                std::string _tmp_id = _node.attributes["id"];
                _tmp_id.erase(std::remove_if(_tmp_id.begin(), _tmp_id.end(), std::isspace), _tmp_id.end());
                
                if(_tmp_id.size() == 0)
                    selector.push_back(_node.nodeType);
                else
                    selector.push_back("#" + _node.attributes["id"]);
            }
            else
                selector.push_back(_node.nodeType);


            std::vector<std::tuple<std::string, std::string>> _tmpAttrs;

            bool hasClear  = false;
            bool hasWidth  = false;
            bool hasHeight = false;
            bool hasBlock  = false;

            if(_node.nodeType == "root") {
                auto _clearTup = std::make_tuple("clear", "white");
                hasClear = true;
                _tmpAttrs.push_back(_clearTup);
            }  

            for(auto _attr : _pAttrs) {
                std::string selector = std::get<0>(_attr);
                std::string value = std::get<1>(_attr);
                auto _pTup = std::make_tuple(selector, value);

                if(selector == "clear" && !hasClear) {
                    _tmpAttrs.push_back(_pTup);
                    hasClear = true;
                } else if (selector == "clear" && hasClear) {
                    for(int i = 0; i < _tmpAttrs.size(); i++) {
                        auto _g = _tmpAttrs[i];
                        if(std::get<0>(_g) == "clear")
                            _tmpAttrs[i] = _pTup;
                    }
                }

                if(selector == "width" && !hasWidth) {
                    _tmpAttrs.push_back(_pTup);
                    hasWidth = true;
                } else if (selector == "width" && hasWidth) {
                    for(int i = 0; i < _tmpAttrs.size(); i++) {
                        auto _g = _tmpAttrs[i];
                        if(std::get<0>(_g) == "width")
                            _tmpAttrs[i] = _pTup;
                    }
                }

                if(selector == "height" && !hasHeight) {
                    _tmpAttrs.push_back(_pTup);
                    hasHeight = true;
                } else if (selector == "height" && hasHeight) {
                    for(int i = 0; i < _tmpAttrs.size(); i++) {
                        auto _g = _tmpAttrs[i];
                        if(std::get<0>(_g) == "height")
                            _tmpAttrs[i] = _pTup;
                    }
                }

                if(selector == "block" && !hasBlock) {
                    _tmpAttrs.push_back(_pTup);
                    hasBlock = true;

                    if(value == "block") {
                        _sNode._displayType = Display::Block;
                    } else if (value == "inline") {
                        _sNode._displayType = Display::Inline;
                    } else if (value == "none") {
                        _sNode._displayType = Display::NoneD;
                    }
                } else if (selector == "block" && hasBlock) {
                    for(int i = 0; i < _tmpAttrs.size(); i++) {
                        auto _g = _tmpAttrs[i];
                        if(std::get<0>(_g) == "block") {
                            _tmpAttrs[i] = _pTup;

                            if(value == "block") {
                                _sNode._displayType = Display::Block;
                            } else if (value == "inline") {
                                _sNode._displayType = Display::Inline;
                            } else if (value == "none") {
                                _sNode._displayType = Display::NoneD;
                            }
                        }
                    }
                }
            }

            _sNode._displayType = Display::Block;

            for(auto _selec : selector) {
                std::unordered_map<std::string, std::string> _selectorStyles;
                if(check_key(_selec)) 
                    _selectorStyles = _attrValues[_selec];

                for(std::pair<std::string, std::string> elem : _selectorStyles) {
                    std::string value = elem.second;
                    auto _tup = std::make_tuple(elem.first, elem.second);

                    if(elem.first == "clear" && !hasClear) {     
                        _tmpAttrs.push_back(_tup);
                        hasClear = true;
                    } else if(elem.first == "clear" && hasClear) {
                        for(int i = 0; i < _tmpAttrs.size(); i++) {
                            auto _g = _tmpAttrs[i];
                            if(std::get<0>(_g) == "clear")
                                _tmpAttrs[i] = _tup;
                        }
                    }

                    if(elem.first == "width" && !hasWidth) {     
                        _tmpAttrs.push_back(_tup);
                        hasWidth = true;
                    } else if(elem.first == "width" && hasWidth) {
                        for(int i = 0; i < _tmpAttrs.size(); i++) {
                            auto _g = _tmpAttrs[i];
                            if(std::get<0>(_g) == "width")
                                _tmpAttrs[i] = _tup;
                        }
                    }

                    if(elem.first == "height" && !hasHeight) {     
                        _tmpAttrs.push_back(_tup);
                        hasHeight = true;
                    } else if(elem.first == "height" && hasHeight) {
                        for(int i = 0; i < _tmpAttrs.size(); i++) {
                            auto _g = _tmpAttrs[i];
                            if(std::get<0>(_g) == "height")
                                _tmpAttrs[i] = _tup;
                        }
                    }

                    if(elem.first == "block" && !hasBlock) {     
                        _tmpAttrs.push_back(_tup);
                        hasBlock = true;

                        if(value == "block") {
                            _sNode._displayType = Display::Block;
                        } else if (value == "inline") {
                            _sNode._displayType = Display::Inline;
                        } else if (value == "none") {
                            _sNode._displayType = Display::NoneD;
                        }
                    } else if(elem.first == "block" && hasBlock) {
                        for(int i = 0; i < _tmpAttrs.size(); i++) {
                            auto _g = _tmpAttrs[i];
                            if(std::get<0>(_g) == "block") {
                                _tmpAttrs[i] = _tup;

                                if(value == "block") {
                                    _sNode._displayType = Display::Block;
                                } else if (value == "inline") {
                                    _sNode._displayType = Display::Inline;
                                } else if (value == "none") {
                                    _sNode._displayType = Display::NoneD;
                                }
                            }
                        }
                    }
                }             
            }

            //do the node attribute stylea
            for(std::pair<std::string, std::string> elem : _node.attributes) {
                std::string value = elem.second;
                
                
                auto _tup = std::make_tuple(elem.first, elem.second);

                if(elem.first == "clear" && !hasClear) {     
                    _tmpAttrs.push_back(_tup);
                    hasClear = true;
                } else if(elem.first == "clear" && hasClear) {
                    for(int i = 0; i < _tmpAttrs.size(); i++) {
                        auto _g = _tmpAttrs[i];
                        if(std::get<0>(_g) == "clear")
                            _tmpAttrs[i] = _tup;
                    }
                }

                if(elem.first == "width" && !hasWidth) {     
                    _tmpAttrs.push_back(_tup);
                    hasWidth = true;
                } else if(elem.first == "width" && hasWidth) {
                    for(int i = 0; i < _tmpAttrs.size(); i++) {
                        auto _g = _tmpAttrs[i];
                        if(std::get<0>(_g) == "width")
                            _tmpAttrs[i] = _tup;
                    }
                }

                if(elem.first == "height" && !hasHeight) {     
                    _tmpAttrs.push_back(_tup);
                    hasHeight = true;
                } else if(elem.first == "height" && hasHeight) {
                    for(int i = 0; i < _tmpAttrs.size(); i++) {
                        auto _g = _tmpAttrs[i];
                        if(std::get<0>(_g) == "height")
                            _tmpAttrs[i] = _tup;
                    }
                }

                if(elem.first == "block" && !hasBlock) {     
                    _tmpAttrs.push_back(_tup);
                    hasBlock = true;

                    if(value == "block") {
                        _sNode._displayType = Display::Block;
                    } else if (value == "inline") {
                        
                        _sNode._displayType = Display::Inline;
                    } else if (value == "none") {
                        _sNode._displayType = Display::NoneD;
                    }
                } else if(elem.first == "block" && hasBlock) {
                    for(int i = 0; i < _tmpAttrs.size(); i++) {
                        auto _g = _tmpAttrs[i];
                        if(std::get<0>(_g) == "block") {
                            _tmpAttrs[i] = _tup;

                            if(value == "block") {
                                _sNode._displayType = Display::Block;
                            } else if (value == "inline") {
                                _sNode._displayType = Display::Inline;
                            } else if (value == "none") {
                                _sNode._displayType = Display::NoneD;
                            }
                        }
                    }
                }
            }



            auto _children = StyleNode(_node.children, _tmpAttrs);
            
            _sNode.node = &_node;
            _sNode._properties = _tmpAttrs;
            _sNode.children = _children;
            _sNode.nodeName = _node.nodeType;

            _styled_nodes.push_back(_sNode);
        }

        return _styled_nodes;
    }

    bool NodeStyler::check_key(std::string key) {
        if(_attrValues.find(key) == _attrValues.end())
            return true;

        return false;
    }
}