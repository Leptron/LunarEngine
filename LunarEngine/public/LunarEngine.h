#include <vector>
#include <string>
#include <stdexcept>
#include <array>
#include <sstream>

#include "../public/glad/glad.h"
#include <GLFW/glfw3.h>

#include "LuanarShader.h"
#include "LunarObject.h"
#include "LunarLayer.h"
#include "LunarShaderGen.h"
#include "LunarShaderManager.h"
#include "LunarPrimitives/SpriteManager.h"
#include "LunarLogger.h"
#include "LunarPrimitives/SpriteSheetRenderer.h"
#include "LunarManager/LunarAnimationManager.h"

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

        //sprite manager
        Lunar2D::SpriteManager testSpriteManager;

        //shader manager
        LunarUtils::ShaderManager shaderManager;

        //anim manager
        LunarAnimation::LunarSpriteAnimationManager _animationManager;

        //time
        float prevTime;
        float deltaTime;
    private:
        //methods
        void processInput();
    };
}