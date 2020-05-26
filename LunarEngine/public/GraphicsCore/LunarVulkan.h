#ifndef LUNARVULKAN_H
#define LUNARVULKAN_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <optional>
#include <set>
#include <cstdint>
#include <algorithim>

#include "LunarWindow.h"

namespace LunarCoreGraphics {
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData);
    	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

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

	class LunarVulkan {
		public:
			void InitVulkan();
			void Clean();

			void PassLNWindow(LunarWindow window);
		private:
			LunarWindow window;

			void createInstance();
			VkInstance instance;

			bool checkValidationLayerSupport();
			std::vector<const char*> getRequiredExtensions();
			const std::vector<const char*> validationLayers = {
                "VK_LAYER_KHRONOS_validation"
        	};

			void setupDebugMessenger();
			void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
			VkDebugUtilsMessengerEXT debugMessenger;

			void pickPhysicalDevice();
			bool isDeviceSuitable(VkPhysicalDevice device);
			QueueFamilyIndicies findQueueFamilies(VkPhysicalDevice device);
			VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

			void createLogicalDevice();
			VkDevice device;
			VkQueue graphicsQueue;
			VkQueue presentQueue;

			void createSurface();
			VkSurfaceKHR surface;

			bool checkDeviceExtensionSupport(VkPhysicalDevice device);
			const std::vector<const char*> deviceExtensions = {
					VK_KHR_SWAPCHAIN_EXTENSION_NAME
			};

			SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
			VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
			VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
			VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

			void createSwapChain();

			VkSwapchainKHR swapChain;
			std::vector<VkImage> swapChainImages;
			VkFormat swapChainImageFormat;
			VkExtent2D swapChainExtent;

			void createImageViews();
			std::vector<VkImageView> swapChainImageViews;

			//FOR PRODUCTION TURN ELSE OFF
	#ifndef _DEBUG
			const bool enableValidationLayers = true;
	#else
			const bool enableValidationLayers = false;
	#endif
	};
}

#endif
