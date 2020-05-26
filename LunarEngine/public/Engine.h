#ifndef ENGINE_H
#define ENGINE_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "GraphicsCore/LunarWindow.h"

namespace LunarCore {
	class Engine {
		public:
			Engine();
			~Engine();

			void Run();

		private:
			void initVulkan();
			void mainLoop();
			void cleanup();

			LunarCoreGraphics::LunarWindow lunar_window;
	};
}
#endif
