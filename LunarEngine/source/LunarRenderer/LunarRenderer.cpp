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
        //image views
        for (auto imageView : swapChainImageViews) {
            vkDestroyImageView(device, imageView, nullptr);
        }
        //swapcahinm
        vkDestroySwapchainKHR(device, swapChain, nullptr);
        //cleanup device
        vkDestroyDevice(device, nullptr);
        //destroy debugging
        if(enableValidationLayers)
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        //destroy surface
        vkDestroySurfaceKHR(instance, surface, nullptr);
        //destroy instance
        vkDestroyInstance(instance, nullptr);
        //destroy window
        glfwDestroyWindow(window);

        //terminate glfw
        glfwTerminate();
    }
}