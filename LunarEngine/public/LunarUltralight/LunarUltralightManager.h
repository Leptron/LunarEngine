#pragma once

#include "ultralight/Ultralight/Ultralight.h"

namespace LunarGUI {
    class UltralightManager {
    public:
        UltralightManager();
        ~UltralightManager();

    private:
        ultralight::RefPtr<ultralight::Renderer> renderer;
    };
}