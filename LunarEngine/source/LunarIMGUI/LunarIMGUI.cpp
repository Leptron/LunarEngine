#include "../../public/LunarIMGUI.h"

namespace LunarEditor {
    LunarEditorGUI::LunarEditorGUI(LunarRenderer::LayerManager *manager) : manager(manager) {
        device = manager->device;
        ImGui::CreateContext();
    }

    LunarEditorGUI::~LunarEditorGUI() {
        ImGui::DestroyContext();

        vkDestroyBuffer(device, indexBuffer, nullptr);
        vkFreeMemory(device, indexBufferMemory, nullptr);

        vkDestroyBuffer(device, vertexBuffer, nullptr);
        vkFreeMemory(device, vertexBufferMemory, nullptr);

        vkDestroyImage(device, fontImage, nullptr);
        vkDestroyImageView(device, fontView, nullptr);
        vkFreeMemory(device, fontMemory, nullptr);

        vkDestroySampler(device, sampler, nullptr);

        vkDestroyPipelineCache(device, pipelineCache, nullptr);
        vkDestroyPipeline(device, pipeline, nullptr);
        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);

        vkDestroyDescriptorPool(device, descriptorPool, nullptr);
        vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
    }
}