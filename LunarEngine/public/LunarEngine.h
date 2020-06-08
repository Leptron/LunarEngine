#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include <tuple>

#include "LunarRenderer.h"
#include "LunarLayerManager.h"
#include "LunarBuffer.hpp"
#include "LunarIMGUI.h"

namespace LunarEngine {
    class LunarEngine {
    public:
        LunarEngine();
        ~LunarEngine();

        void InitResources();
        void MainLoop();
    private:
        LunarRenderer::LayerManager manager;
        LunarRenderer::LunarRenderer renderer;
        LunarEditor::LunarEditorGUI editorGUI;
    private:
        VkDevice device;
        GLFWwindow* window;
    };
}