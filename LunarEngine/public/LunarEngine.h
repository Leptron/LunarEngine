#include <vector>
#include <string>
#include <stdexcept>
#include <array>
#include <sstream>

#include "../public/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "LuanarShader.h"
#include "LunarObject.h"
#include "LunarLayer.h"
#include "LunarShaderGen.h"
#include "LunarShaderManager.h"
#include "LunarPrimitives/SpriteManager.h"
#include "LunarLogger.h"
#include "LunarPrimitives/SpriteSheetRenderer.h"
#include "LunarManager/LunarAnimationManager.h"
#include "LunarBatching/StaticSquareBatch.h"

namespace LunarEngine {
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    class LunarEngine {
    public:
        LunarEngine();
        ~LunarEngine();

        void InitResources();
        void MainLoop();
        
        //vars
        static int width, height;
        static bool dimsChanged;
    private:
        GLFWwindow* window;

        std::vector<LunarRenderer::LunarShader> shaders;
        std::array<LunarRenderer::Layer, 1> layers;

        //sprite manager
        Lunar2D::SpriteManager testSpriteManager;

        //shader manager
        LunarUtils::ShaderManager shaderManager;

        //anim manager
        LunarAnimation::LunarSpriteAnimationManager _animationManager;

        //test batching
        LunarBatching::StaticSquareBatch _testBatch;

        //time
        float prevTime;
        float deltaTime;
        
        //ortho
        glm::mat4 orthoProjection;
    private:
        //methods
        void processInput();
    };
}
