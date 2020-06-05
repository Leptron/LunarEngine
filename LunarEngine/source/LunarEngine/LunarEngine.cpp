#include "../../public/LunarEngine.h"

namespace LunarEngine {
    LunarEngine::LunarEngine() {
    }

    LunarEngine::~LunarEngine() {

    }

    void LunarEngine::InitResources() {
        renderer.InitResources();
        LunarRenderer::EngineRelinquish rel = renderer.RelinquishEngine();
        this->device = rel.device;
        this->window = rel.window;

        std::vector<LunarRenderer::Vertex> testQuad = {
            {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
            {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
        };

        std::vector<uint32_t> testIndicies = {
            0, 1, 2, 2, 3, 0
        };

        // attach
        manager = LunarRenderer::LayerManager(&renderer.globConstruct());
        renderer.AttachManager(&manager);

        manager.CreateObject(testQuad, testIndicies, "basic_pos", false, "epic");
        manager.AllocateObjects();

        renderer.CreateCommandBuffers();
    }

    void LunarEngine::MainLoop() {
        while(!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            renderer.drawFrame();
            manager.updateUniformBuffer();
        }

        vkDeviceWaitIdle(device);
        renderer.cleanup();
    }
}