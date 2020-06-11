#include "../../public/LunarEngine.h"

namespace LunarEngine {
    LunarEngine::LunarEngine() {
    }

    LunarEngine::~LunarEngine() {

    }

    void LunarEngine::InitResources() {
        width = 1280;
        height = 720;

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

        //test shader
        LunarRenderer::LunarShader testShader("shaders/shader.vert", "shaders/shader.frag");
        shaders.push_back(testShader);
    }

    void LunarEngine::MainLoop() {
        std::vector<float> vertices ({
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left 
        });
        std::vector<unsigned int> indices ({  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        });

        LunarRenderer::LunarOpenglObject testObject(vertices, indices, &shaders[0]);

        while (!glfwWindowShouldClose(window)) {
            processInput();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            testObject.Draw();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        testObject.Clean();

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