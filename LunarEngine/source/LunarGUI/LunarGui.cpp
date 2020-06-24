#include "../../public/LunarGUI/LunarGui.h"

namespace LunarGUI {
    GUIManager::GUIManager() {
        LunarLogger::Logger::getInstance()->log("Creating a GUI Manager", "GUI", "yellow");
    }

    GUIManager::~GUIManager() {

    }

    void GUIManager::CreateGUIPane(std::string paneDefLoc) {
        LunarLogger::Logger::getInstance()->log("Creating a GUI Pane", "GUI", "yellow");
        //implement TODO
        GUIPane _pane;
        _pane.CreatePane(paneDefLoc);
    }
}