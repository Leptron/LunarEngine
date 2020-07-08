#include "../../public/LunarGUI/LunarLayout.h"

namespace LunarGUI {
    LayoutManager::LayoutManager() {

    }

    LayoutManager::~LayoutManager() {

    }

    LayoutBox LayoutManager::BuildLayoutTree(StyledNode _sNode) {
        LayoutBox rootBox = {};
        

        rootBox.nodeName = _sNode.nodeName;
        rootBox.anonBox = false;
        rootBox._properties = _sNode._properties;

        auto _displayRequest = _sNode._displayType;
        if(_displayRequest == Display::Block) {
            BoxTypeS _boxType = {};

            _boxType._node    = &_sNode;
            _boxType._boxType = BoxTypeE::BlockNode;
            rootBox.box_type = _boxType;
        } else if (_displayRequest == Display::Inline) {
            BoxTypeS _boxType = {};

            _boxType._node    = &_sNode;
            _boxType._boxType = BoxTypeE::InlineNode;
            rootBox.box_type = _boxType;
        }

        for(auto _child : _sNode.children)
            if(_child._displayType == Display::Block)
                rootBox.children.push_back(BuildLayoutTree(_child));
            else if (_child._displayType == Display::Inline)
                get_inline_container(rootBox)->children.push_back(BuildLayoutTree(_child));
            
        return rootBox;
    }

    LayoutBox* LayoutManager::get_inline_container(LayoutBox& root) {
        if(root.children.size() != 0) {
            auto _lastNode = root.children.back();

            if(_lastNode.anonBox && _lastNode.box_type._boxType == BoxTypeE::BlockNode)
                return &root.children[root.children.size() - 1];
            else {
                LayoutBox anonBox = {};
                anonBox.box_type._boxType = BoxTypeE::BlockNode;
                anonBox.anonBox = true;
                anonBox.nodeName = "Anonymous box";

                root.children.push_back(anonBox);
                return &root.children[root.children.size() - 1];
            }
        } else {
            LayoutBox anonBox = {};
            anonBox.box_type._boxType = BoxTypeE::BlockNode;
            anonBox.anonBox = true;
            anonBox.nodeName = "Anonymous box";

            root.children.push_back(anonBox);
            return &root.children[root.children.size() - 1];
        }
    }
}