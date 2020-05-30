#include "../../public/LunarRenderer.h"

namespace LunarRenderer {
    LunarRenderer::LunarRenderer() {

    }

    LunarRenderer::~LunarRenderer() {

    }

    void LunarRenderer::InitResources() {
        initWindow();

        initVulkan();
    }

    void LunarRenderer::cleanup() {
        //call all the various sub cleaning functions
        //destroy debugging
        if(enableValidationLayers)
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        //destroy instance
        vkDestroyInstance(instance, nullptr);
        //destroy window
        glfwDestroyWindow(window);

        //terminate glfw
        glfwTerminate();
    }
}