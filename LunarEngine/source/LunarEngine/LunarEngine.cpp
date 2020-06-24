#include "../../public/LunarEngine.h"

namespace LunarEngine {
    LunarEngine::LunarEngine() {
    }

    LunarEngine::~LunarEngine() {

    }
    
    int LunarEngine::width = 1280;
    int LunarEngine::height = 720;
    bool LunarEngine::dimsChanged = false;

    void LunarEngine::InitResources() {
        _manager.CreateGUIPane("shaders/test.lnGUI");
		orthoProjection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
        testSpriteManager.UpdateScreenDims(width, height);

        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        //creating the window
        window = glfwCreateWindow(width, height, "Lunar Engine", NULL, NULL);
        if (window == NULL) {
            glfwTerminate();
            throw std::runtime_error("failed to create a glfw window");
            return;
        }
        glfwMakeContextCurrent(window);

        LunarLogger::Logger::getInstance()->log("Created Opengl Window", "Engine", "MAGENTA");

        //load glad
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("failed to load GLAD");

        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        LunarLogger::Logger::getInstance()->log("Created Opengl Instance", "Engine", "MAGENTA");

        testSpriteManager.InitResources();
        testSpriteManager.CreateTiledSprite("lol");

        //setup animation manager
        _animationManager.PassManager(&testSpriteManager);
        
        //test animation
        std::vector<int> frames = { 0, 1, 2, 3 };
        _animationManager.CreateAnimation("testAnimation", "lol", frames, 10);
        _animationManager.PlayAnimation("testAnimation");

        LunarBatching::LunarBatchedColor colors = {};
        colors.lColor = glm::vec3(1.0f, 0.8f, 0.8f);
        colors.lTColor = glm::vec3(1.0f);
        colors.rColor = glm::vec3(1.0f);
        colors.rTColor = glm::vec3(1.0f);

        _testBatch.CreateQuad(glm::vec2(300.0f, 300.0f), glm::vec2(50.0f, 200.0f), 0.0f, colors);
        _testBatch.UpdateOrtho(orthoProjection);
        _testBatch.Batch();
    }

    void LunarEngine::MainLoop() {
        LunarLogger::Logger::getInstance()->log("Created Opengl Rendering Loop", "Engine", "MAGENTA");

        prevTime = glfwGetTime();
        bool test = true;

        while (!glfwWindowShouldClose(window)) {
            processInput();

            if (dimsChanged) {
                orthoProjection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
                _testBatch.UpdateOrtho(orthoProjection);
                testSpriteManager.UpdateScreenDims(width, height);

                dimsChanged = false;
            }

            float now = glfwGetTime();
            deltaTime = now - prevTime;
            prevTime = now;
            _animationManager.Update(deltaTime);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (auto layer : layers)
                layer.Draw();

            testSpriteManager.Draw();
            _testBatch.Draw();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        for (auto layer : layers)
            layer.Clean();

        for(auto shader : shaders)
            shader.Clean();

        LunarLogger::Logger::getInstance()->log("Destroyed all resources", "Engine", "MAGENTA");
        glfwTerminate();
    }

    void LunarEngine::processInput() {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        std::stringstream messageStream;
        messageStream << "Opengl Viewport resized to " << width << " by " << height;

        LunarLogger::Logger::getInstance()->log(messageStream.str(), "Engine", "MAGENTA");
        glViewport(0, 0, width, height);
        
        LunarEngine::width = width;
        LunarEngine::height = height;
        LunarEngine::dimsChanged = true;
    }
}
