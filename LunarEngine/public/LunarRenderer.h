#pragma once

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <optional>
#include <set>
#include <algorithm>
#include <fstream>
#include <glm/glm.hpp>
#include <array>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstdint>

#include "LunarVkDatatypes.h"

namespace LunarRenderer {
    const int MAX_FRAMES_IN_FLIGHT = 2;


    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    struct QueueFamilyIndicies {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    
    class LunarRenderer {
    public:
        LunarRenderer();
        ~LunarRenderer();

        // Initialization
        void InitResources();
        void MainLoop();
        bool framebufferResized = false;

        //layer prototypes
        

    private:
        void cleanup();

        //create the window
        void initWindow();

        //initialize vulkan
        void initVulkan();
        //create instance
        void createInstance();
        //validaton and debugging layer funcs
        bool checkValidationLayerSupport();
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        std::vector<const char*> getRequiredExtensions();
        void setupDebugMessenger();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        //physical device + logical device
        void pickPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice device);
        QueueFamilyIndicies findQueueFamilies(VkPhysicalDevice device);
        
        void createLogicalDevice();

        //presentation
        void createSurface();
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        void createSwapChain();
        void createImageViews();

        //graphics pipeline (eventual layer implementation)
        void createGraphicsPipeline();
        void createRenderPass();
        static std::vector<char> readFile(const std::string& filename);
        VkShaderModule createShaderModule(const std::vector<char>& code);

        //layer prototypes
        void prepareUniformBuffers();

        //drawing
        void createFrameBuffer();
        void createCommandPool();
        void createCommandBuffers();
        void drawFrame();
        void createSyncObjects();

        //recreate swap chain
        void recreateSwapChain();
        void cleanupSwapChain();

        //variables and handles
        //drawing
        std::vector<VkFramebuffer> swapChainFrameBuffers;
        std::vector<VkCommandBuffer> commandBuffers;
        VkCommandPool commandPool;

        //semaphores
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        size_t currentFrame = 0;

        std::vector<GeometryLayer> layers;
        

        //pipeline
        VkPipeline graphicsPipeline;
        VkRenderPass renderPass;
        VkPipelineLayout pipelineLayout;
        //surface + presentation
        VkSurfaceKHR surface;
        VkQueue presentQueue;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        //Queue
        VkQueue graphicsQueue;
        //physical device
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        //validation layers
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        //extensions
        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        #ifdef NDEBUG
            const bool enableValidationLayers = true;
        #else
            const bool enableValidationLayers = true;
        #endif

        VkDebugUtilsMessengerEXT debugMessenger;
        //GLFW window and width / height
        GLFWwindow* window;
        uint32_t width = 1280;
        uint32_t height = 720;

        //vulkan handler
        //vulkan instance
        VkInstance instance;
    };
}