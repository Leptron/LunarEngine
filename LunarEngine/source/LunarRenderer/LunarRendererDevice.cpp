#include "../../public/LunarRenderer.h"

namespace LunarRenderer {
    void LunarRenderer::pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if(deviceCount == 0)
            throw std::runtime_error("failed to find a gpu with vulkan support");

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        for(const auto& device : devices) {
            if(isDeviceSuitable(device)) {
                physicalDevice = device;
                break;
            }
        }

        if(physicalDevice == VK_NULL_HANDLE)
            throw std::runtime_error("failed to find a suitable GPU!");
    }

    bool LunarRenderer::isDeviceSuitable(VkPhysicalDevice device) {
        QueueFamilyIndicies indices = findQueueFamilies(device);

        return indices.isComplete();
    }

    QueueFamilyIndicies LunarRenderer::findQueueFamilies(VkPhysicalDevice device) {
        QueueFamilyIndicies indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for(const VkQueueFamilyProperties& queueFamily : queueFamilies) {
            if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                indices.graphicsFamily = i;

            if(indices.isComplete())
                break;

            i++;
        }

        return indices;
    }

    void LunarRenderer::createLogicalDevice() {
        QueueFamilyIndicies indices = findQueueFamilies(physicalDevice);

        VkDeviceQueueCreateInfo queueCreateInfo = {};
    }
}