#include "../LunarLogger.h"

#include <string>

namespace LunarGUI {
    class GUIManager {
    public:
        GUIManager();
        ~GUIManager();

        void CreateGUIPane(std::string paneDefLoc);
    };
}