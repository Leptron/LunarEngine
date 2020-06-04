#include "../../public/LunarRenderer.h"

namespace LunarRenderer {
    void LunarRenderer::initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        
        window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    }

    void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<LunarRenderer*>(glfwGetWindowUserPointer(window));
        app->framebufferResized = true;
    }

    void LunarRenderer::MainLoop() {
        while(!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            drawFrame();
        }

        vkDeviceWaitIdle(device);
        cleanup();
    }

    void LunarRenderer::LayerLoop(LayerManager* manager) {
        while(!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            drawFrame();
            manager->updateUniformBuffer();
        }

        vkDeviceWaitIdle(device);
        cleanup();
    }
}