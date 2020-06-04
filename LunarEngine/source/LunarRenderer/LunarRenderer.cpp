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
    }

    void LunarRenderer::cleanupSwapChain() {
        for (size_t i = 0; i < this->swapChainFrameBuffers.size(); i++) {
            vkDestroyFramebuffer(device, this->swapChainFrameBuffers[i], nullptr);
        }

        vkFreeCommandBuffers(device, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

        vkDestroyPipeline(device, graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
        vkDestroyRenderPass(device, renderPass, nullptr);

        for (size_t i = 0; i < swapChainImageViews.size(); i++) {
            vkDestroyImageView(device, swapChainImageViews[i], nullptr);
        }

        vkDestroySwapchainKHR(device, swapChain, nullptr);
    }

    LunarLayerConstruction LunarRenderer::globConstruct() {
        LunarLayerConstruction construct = {};

        construct.device = device;
        construct.physicalDevice = physicalDevice;
        construct.renderPass = renderPass;
        construct.swapChainExtent = swapChainExtent;
        construct.swapChainImages = swapChainImages;
        construct.commandPool = commandPool;
        construct.graphicsQueue = graphicsQueue;
        construct.swapChainFrameBuffers = swapChainFrameBuffers;

        return construct;
    }

    void LunarRenderer::cleanup() {
        //call all the various sub cleaning functions
        cleanupSwapChain();
        //semaphores
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(device, inFlightFences[i], nullptr);
        }
        //command pool
        vkDestroyCommandPool(device, commandPool, nullptr);
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