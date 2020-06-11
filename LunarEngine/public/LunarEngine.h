#include <vector>
#include <string>
#include <stdexcept>

#include "../public/glad/glad.h"
#include <GLFW/glfw3.h>

#include "LuanarShader.h"
#include "LunarObject.h"

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
    private:
        //methods
        void processInput();
    };
}