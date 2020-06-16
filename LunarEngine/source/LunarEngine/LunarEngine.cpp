#include "../../public/LunarEngine.h"

namespace LunarEngine {
    LunarEngine::LunarEngine() {
    }

    LunarEngine::~LunarEngine() {

    }

    void LunarEngine::InitResources() {
        width = 1280;
        height = 720;

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
        testSpriteManager.CreateSprite("zhongou");
    }

    void LunarEngine::MainLoop() {
        LunarLogger::Logger::getInstance()->log("Created Opengl Rendering Loop", "Engine", "MAGENTA");

        //fps counting
        int frames = 0;
        double t, t0, fps;
        t0 = glfwGetTime();

        while (!glfwWindowShouldClose(window)) {
            processInput();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (auto layer : layers)
                layer.Draw();
            
            testSpriteManager.Draw();

            t = glfwGetTime();
            if ((t - t0) > 1.0 || frames == 0) {
                fps = (double)frames / (t - t0);
                
                std::stringstream messageStream;
                messageStream << "Lunar Engine fps " << fps;
                LunarLogger::Logger::getInstance()->log(messageStream.str(), "Performance", "green");

                t0 = t;
                frames = 0;
            }

            frames++;

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
    }
}