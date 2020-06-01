#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

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

#include "LunarVkDatatypes.h"

namespace LunarRenderer {
    struct LunarLayerConstructInfo {
        VkDevice device;
        VkExtent2D swapChainExtent;
        VkRenderPass renderPass;
    };
    
    class LunarLayer {
    public:
        LunarLayer();
        LunarLayer(LunarLayerConstructInfo constructInfo);
        ~LunarLayer();

        void CreateMaterial(std::string materialName);

        int AddGeometry(Geometry addGeometry);
        int FlushGeometry();
    private:
        //material helpers
        void createRenderPass();
        static std::vector<char> readFile(const std::string& filename);
        VkShaderModule createShaderModule(const std::vector<char>& code);

        LunarLayerConstructInfo construct;

        GeometryLayer layer;
        std::vector<Geometry> tmpGeometryBuffer;
        
        int geomIndex = 0;
        int currGeomLayer = 0;
    };
}