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

        //load glad
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("failed to load GLAD");

        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        testSpriteManager.InitResources();
        testSpriteManager.CreateSprite("zhongou");
    }

    void LunarEngine::MainLoop() {

        while (!glfwWindowShouldClose(window)) {
            processInput();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (auto layer : layers)
                layer.Draw();
            
            testSpriteManager.Draw();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        for (auto layer : layers)
            layer.Clean();

        for(auto shader : shaders)
            shader.Clean();

        glfwTerminate();
    }

    void LunarEngine::processInput() {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        
    }
}