#include "../public/Engine.h"


#include <GLFW/glfw3.h>

namespace LunarCore {
	Engine::Engine() {
		glfwInit();
	}

	Engine::~Engine() {
	}

	void Engine::Run() {
		lunar_window.InitWindow();

		initVulkan();
		mainLoop();
		cleanup();
	}

	// other functions
	void Engine::initVulkan() {
	}

	void Engine::mainLoop() {
		while(!glfwWindowShouldClose(lunar_window.GetWindowInst())) {
			glfwPollEvents();
		}
	}

	void Engine::cleanup() {
		lunar_window.Clean();
		glfwTerminate();
	}
}	
