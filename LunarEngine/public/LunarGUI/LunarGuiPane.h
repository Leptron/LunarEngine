#include "../LunarLogger.h"
#include "LunarGUIData.h"
#include "XMLParser.h"
#include "StyleSheetParser.h"
#include "LunarGUIStyler.h"

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
        Node rootNode;
    private:
        Stylesheet _stylesheet;
    };
}