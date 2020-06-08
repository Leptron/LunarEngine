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
        editorGUI = LunarEditor::LunarEditorGUI(&manager);

        manager.CreateObject(testQuad, testIndicies, "basic_pos", false, "epic");
        manager.AllocateObjects();

        LunarRenderer::ProjectionMatricies matricies = {};
        matricies.model = glm::mat4(1.0);
        matricies.proj = glm::perspective(glm::radians(45.0f), manager.swapChainExtent.width / (float) manager.swapChainExtent.height, 0.1f, 10.0f);

        manager.UpdateObjectUniform(matricies, "epic");

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