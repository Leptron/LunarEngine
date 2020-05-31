#include "../../public/LunarRenderer.h"

namespace LunarRenderer {
    void LunarRenderer::initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
        window = glfwCreateWindow(this->width, this->height, "Vulkan", nullptr, nullptr);
    }

    void LunarRenderer::MainLoop() {
        while(!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            drawFrame();
        }

        vkDeviceWaitIdle(device);
        cleanup();
    }
}