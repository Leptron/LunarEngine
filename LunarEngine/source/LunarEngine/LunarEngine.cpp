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

        std::vector<float> vertices({
            0.2f,  0.2f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
             0.2f, -0.2f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.2f, -0.2f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.2f,  0.2f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
        });
        std::vector<unsigned int> indices({  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        });

        LunarUtils::LunarShaderGenerator vertShader;

        vertShader.AddLayout("0", "vec3", "aPos");
        vertShader.AddLayout("1", "vec3", "aColor");
        vertShader.AddLayout("2", "vec2", "aTexCoord");

        vertShader.AddOutput("ourColor", "vec3");
        vertShader.AddOutput("TexCoord", "vec2");

        vertShader.SetVertexPosition("aPos");
        vertShader.SetVariable("ourColor", "aColor");
        vertShader.SetVariable("TexCoord", "aTexCoord");

        LunarUtils::LunarShaderGenerator fragShader;

        fragShader.AddOutput("FragColor", "vec4");
        
        fragShader.AddInput("ourColor", "vec3");
        fragShader.AddInput("TexCoord", "vec2");
        fragShader.AddUniform("ourTexture", "sampler2D");

        fragShader.SetVariable("FragColor", fragShader.ShaderTexture("ourTexture", "TexCoord"));

        LunarRenderer::LunarOpenglObject testObject(vertices, indices, &shaders[0]);
        layers[0].addObject(testObject, "quad");
    }

    void LunarEngine::MainLoop() {

        while (!glfwWindowShouldClose(window)) {
            processInput();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (auto layer : layers)
                layer.Draw();

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