#include "../LunarLogger.h"
#include "LunarLayoutState.h"

#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cstdio>
#include <cerrno>
#include <sstream>
#include <numeric>
#include <unordered_map>
#include <iterator>

//TEST
/*
    * PANE
    * container 1
    *   INLINE
    *   width (only 72 px)
    *   height 100%
    * container 2
    *   INLINE
    *   width (100% - 72px) (thats what a space does, takes up the rest of space)
    *   height is 100%
    *   CHILDREN
    *       container 2
    *           BLOCK
    *           Height = 20px SETS Parents children offset height to +20px
    *       container 3
    *           BLOCK
    *           width = 300px
    *           height = 30px; SETS Parents children offset height to +50 px, +20 from above, and +30 from this
*/

namespace LunarGUI {
    struct GUINode {
        bool endTag;
        std::string nodeName;

        int index;
    };

    struct GUINodeAttrib {
        bool endTag;
        bool hasAttrib;

        std::string nodeName;
        std::vector<std::tuple<std::string, std::string>> attributes;

        int index;
    };

    struct Stack {
        std::string stackElem;
        std::vector<std::tuple<std::string, std::string>> attributes;

        int startNode;
        int endNode;
    };

    enum DrawPrimitive {
        Box
    };

    enum BasicColor {
        White,
        Black
    };

    struct DrawCommand {
        DrawPrimitive cmd;
        BasicColor clearColor;

        int width, height;
        int xPos, yPos;
    };

    class GUIPane {
    public:
        GUIPane();
        ~GUIPane();

        void CreatePane(std::string loc, int width = 800, int height = 600);
        void UpdateScreenDims(int width, int height);
    private:
        void CreateNodeList(std::string contents);
        void PushStack(int attribIndex);
        void CreateLayout();
        void CreateDrawCommands();

        int width, height;
    private:
        std::vector<GUINode> nodeList;
        std::vector<GUINodeAttrib> nodeAttribList;

        std::vector<Stack> stack;  
        std::vector<DrawCommand> cmdBuffer;
    };
}