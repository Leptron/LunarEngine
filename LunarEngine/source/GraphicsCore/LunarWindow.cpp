#include "../../public/GraphicsCore/LunarWindow.h"

namespace LunarCoreGraphics {
	LunarWindow::LunarWindow() {
	}

	LunarWindow::~LunarWindow() {
	}

	void LunarWindow::InitWindow() {
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, "TBD", nullptr, nullptr);
	}

	GLFWwindow* LunarWindow::GetWindowInst() {
		return window;
	}

	void LunarWindow::Clean() {
		glfwDestroyWindow(window);
	}

	VkExtent2D LunarWindow::GetActualExtent() {
		VkExtent2D actualExtent = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
		return actualExtent;
	}
}
