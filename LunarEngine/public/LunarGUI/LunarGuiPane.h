#include "../LunarLogger.h"

#include <string>
#include <cstdio>
#include <cerrno>

//TEST
/*
    * PANE
    * BOX 1
    *   width = 20% height = 100% SET width OFFSET 20% for 100% of height
    *   CHILD TODO (Child offset resets)
    * 
    * Box 2
    *   width = 80%; height = 20px
    *   Offset = 20%;
    * Box 3
    *   width = 300px height = 30px
    *   offset = 20%
*/

namespace LunarGUI {
    class GUIPane {
    public:
        GUIPane();
        ~GUIPane();

        void CreatePane(std::string loc);
    };
}