#pragma once
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
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
#include <tuple>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstdint>

#include "../LunarLayerManager.h"

namespace Lunar2DPrimitives {
    class Quad {
    public:
        Quad();
        ~Quad();

        void AttachLayerManager(LunarRenderer::LayerManager* Lmanager);

    private:
        LunarRenderer::LayerManager *layerManager;
    };
}