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

    void LunarRenderer::recreateSwapChain() {
        vkDeviceWaitIdle(device);

        createSwapChain();
        createImageViews();
        createRenderPass();
        createGraphicsPipeline();
        createFrameBuffer();
        createCommandBuffers();
    }

    void LunarRenderer::cleanupSwapChain() {

    }

    void LunarRenderer::cleanup() {
        //call all the various sub cleaning functions
        //semaphores
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(device, inFlightFences[i], nullptr);
        }
        //command pool
        vkDestroyCommandPool(device, commandPool, nullptr);
        //framebuffer
        for(auto framebuffer : swapChainFrameBuffers)
            vkDestroyFramebuffer(device, framebuffer, nullptr);
        //pipeline
        vkDestroyPipeline(device, graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
        vkDestroyRenderPass(device, renderPass, nullptr);
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