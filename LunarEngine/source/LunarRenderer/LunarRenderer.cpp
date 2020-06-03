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
        int w = 0, h = 0;
        glfwGetFramebufferSize(window, &w, &h);
        while (w == 0 || height == 0) {
            glfwGetFramebufferSize(window, &w, &h);
            glfwWaitEvents();
        }

        vkDeviceWaitIdle(device);

        cleanupSwapChain();

        createSwapChain();
        createImageViews();
        createRenderPass();
        CreateMaterial("", 1298719287);
        createFrameBuffer();
        FlushToCommandBuffer();
    }

    void LunarRenderer::cleanupSwapChain() {
        for (auto framebuffer : swapChainFrameBuffers) {
            vkDestroyFramebuffer(device, framebuffer, nullptr);
        }

        vkFreeCommandBuffers(device, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

        cleanMaterials();
        vkDestroyRenderPass(device, renderPass, nullptr);

        for (auto imageView : swapChainImageViews) {
            vkDestroyImageView(device, imageView, nullptr);
        }

        vkDestroySwapchainKHR(device, swapChain, nullptr);
    }

    void LunarRenderer::cleanup() {
        cleanupSwapChain();
        cleanAllLayers();
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(device, inFlightFences[i], nullptr);
        }

        vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);

        vkDestroyCommandPool(device, commandPool, nullptr);

        vkDestroyDevice(device, nullptr);

        if (enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }

        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
    }
}