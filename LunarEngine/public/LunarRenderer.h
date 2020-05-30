#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <optional>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace LunarRenderer {
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

    struct QueueFamilyIndicies {
        std::optional<uint32_t> graphicsFamily;

        bool isComplete() {
            return graphicsFamily.has_value();
        }
    };
    
    class LunarRenderer {
    public:
        LunarRenderer();
        ~LunarRenderer();

        // Initialization
        void InitResources();
        void MainLoop();

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
        std::vector<const char*> getRequiredExtensions();
        void setupDebugMessenger();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        //physical device + logical device
        void pickPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice device);
        QueueFamilyIndicies findQueueFamilies(VkPhysicalDevice device);

        void createLogicalDevice();

        //variables and handles
        //physical device
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        //validation layers
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        #ifdef NDEBUG
            const bool enableValidationLayers = false;
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