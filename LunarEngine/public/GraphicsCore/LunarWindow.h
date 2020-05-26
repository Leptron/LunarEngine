#ifndef LUNARWINDOW_H
#define LUNARWINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace LunarCoreGraphics {
	class LunarWindow {
		public:
			LunarWindow();
			~LunarWindow();

			void InitWindow();
			void Clean();
			VkExtent2D GetActualExtent();

			GLFWwindow* GetWindowInst();
		private:
			GLFWwindow* window;

			int width = 1280;
			int height = 720;
	};
}

#endif
