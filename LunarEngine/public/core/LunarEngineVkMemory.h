#pragma once

#include <vulkan/vulkan.h>

namespace LunarRenderingCore {
    struct Block {
        VkDeviceMemory memory;
        VkDeviceSize offset;
        VkDeviceSize size;

        bool free;
        void *ptr = nullptr; // Useless if it is a GPU allocation

        bool operator==(Block const &block);
    };

    bool Block::operator==(Block const &block) {
        if(memory == block.memory &&
            offset == block.offset &&
            size == block.size &&
            free == block.free &&
            ptr == block.ptr)
            return true;
        return false;
    }

    class Chunk  {
    public:
        Chunk(const Chunk&) = delete;
        Chunk& operator=(const Chunk&) = delete;
    public:
        Chunk(VkDevice &device, VkDeviceSize size, int memoryTypeIndex);
    }
}