#include "../../public/LunarIMGUI.h"


namespace LunarEditor {
    LunarEditorGUI::LunarEditorGUI(LunarRenderer::LayerManager *manager) : manager(manager) {
        this->device = manager->device;
        ImGui::CreateContext();
        std::cout << "creating editor gui" << std::endl;
    }

    LunarEditorGUI::LunarEditorGUI() {

    }

    LunarEditorGUI::~LunarEditorGUI() {
        if (resourceAcquired) {
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

    void LunarEditorGUI::init(float width, float height) {
        //color scheme
        ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[ImGuiCol_TitleBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.6f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(1.0f, 0.0f, 0.0f, 0.8f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.4f);
        style.Colors[ImGuiCol_Header] = ImVec4(1.0f, 0.0f, 0.0f, 0.4f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
        //dims
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(width, height);
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    }

    void LunarEditorGUI::setImageLayout(
			VkCommandBuffer cmdbuffer,
			VkImage image,
			VkImageLayout oldImageLayout,
			VkImageLayout newImageLayout,
			VkImageSubresourceRange subresourceRange,
			VkPipelineStageFlags srcStageMask,
			VkPipelineStageFlags dstStageMask) {
                VkImageMemoryBarrier imageMemoryBarrier = {};
                imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
                imageMemoryBarrier.oldLayout = oldImageLayout;
                imageMemoryBarrier.newLayout = newImageLayout;
                imageMemoryBarrier.image = image;
                imageMemoryBarrier.subresourceRange = subresourceRange;

                switch(oldImageLayout) {
                case VK_IMAGE_LAYOUT_UNDEFINED:
                    imageMemoryBarrier.srcAccessMask = 0;
                    break;
                case VK_IMAGE_LAYOUT_PREINITIALIZED:
                    imageMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
                    break;
                case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
                    imageMemoryBarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
                    break;
                case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
                    imageMemoryBarrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
                    break;
                case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
                    imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
                    break;
                case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
                    imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
                    break;
                case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
                    imageMemoryBarrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
                    break;
                default:
                    break;
                }

                switch (newImageLayout) {
                case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
                    imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
				    break;
                case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
                    imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
				    break;
                case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
                    imageMemoryBarrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				    break;
                case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
                    imageMemoryBarrier.dstAccessMask = imageMemoryBarrier.dstAccessMask | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
				    break;
                case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
                    if (imageMemoryBarrier.srcAccessMask == 0)
                        imageMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
                    imageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
                    break;
                default:
                    break;
                }

                vkCmdPipelineBarrier(
                    cmdbuffer, 
                    srcStageMask,
                    dstStageMask,
                    0,
                    0, nullptr,
                    0, nullptr,
                    1, &imageMemoryBarrier
                );
            }

    void LunarEditorGUI::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
        VkBufferCreateInfo bufferInfo = {};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to create buffer!");
        }

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = manager->findMemoryType(memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate buffer memory!");
        }

        vkBindBufferMemory(device, buffer, bufferMemory, 0);
    }

    VkDescriptorPoolSize LunarEditorGUI::descriptorPoolSize(VkDescriptorType type, uint32_t descriptorCount) {
        VkDescriptorPoolSize descriptorPoolSize {};
        descriptorPoolSize.type = type;
        descriptorPoolSize.descriptorCount = descriptorCount;
        return descriptorPoolSize;
    }
}