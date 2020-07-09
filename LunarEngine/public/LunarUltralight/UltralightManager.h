#pragma once

#include <Ultralight/Ultralight.h>
#include <Ultralight/platform/Logger.h>
#include <AppCore/Platform.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <optional>
#include <set>
#include <algorithm>
#include <array>

#include "../LunarVkDatatypes.h"
#include "../LunarLayerManager.h"

namespace LunarGUI {
    struct LayoutConstruct {
        int width, height;
        std::string name;
        std::string contents;
    };

    struct ULVertex {
        glm::vec2 pos;
        glm::vec2 uv;

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(ULVertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(ULVertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(ULVertex, uv);

            return attributeDescriptions;
        }
    };

    class UltralightManager : public ultralight::Logger, public ultralight::LoadListener {
    public:
        UltralightManager();
        ~UltralightManager();

        void PassResources(LunarRenderer::LunarLayerConstruction *construction);

        //rebuild
        void ConstructView(std::string contents, std::string tagName="index", int width = 0, int height = 0);
        void PrepareGeometry();

        //setter
        void SetFrame(std::vector<std::string> frames);

        virtual void LogMessage(ultralight::LogLevel log_level, const ultralight::String16& message) override;
        virtual void OnFinishLoading(ultralight::View* caller);
    private:
        ultralight::RefPtr<ultralight::Renderer> renderer;
        std::unordered_map<std::string, ultralight::RefPtr<ultralight::View>*> _views;
        std::unordered_map<std::string, bool> _viewDone;

        static int  windowWidth;
        static int  windowHeight;
        static bool dimsChanged;

        std::string currFrame;

    private:
        //vulkan stuff
        VkExtent2D swapChainExtent;
        VkDevice device;
        VkCommandPool commandPool;
        VkQueue graphicsQueue;

        VkRenderPass renderPass;
        std::vector<VkImage> swapChainImages;
        VkPhysicalDevice physicalDevice;
        std::vector<VkDescriptorPool> descriptorPools;
        std::vector<VkFramebuffer> swapChainFrameBuffers;

    };
}