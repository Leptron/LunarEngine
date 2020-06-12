#include <vector>
#include <string>
#include <stdexcept>
#include <array>

#include "../public/glad/glad.h"
#include <GLFW/glfw3.h>

#include "LuanarShader.h"
#include "LunarObject.h"
#include "LunarLayer.h"
#include "LunarShaderGen.h"

namespace LunarEngine {
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    class LunarEngine {
    public:
        LunarEngine();
        ~LunarEngine();

        void InitResources();
        void MainLoop();
    private:
        GLFWwindow* window;
        int width, height;

        std::vector<LunarRenderer::LunarShader> shaders;
        std::array<LunarRenderer::Layer, 1> layers;
    private:
        //methods
        void processInput();
    };
}