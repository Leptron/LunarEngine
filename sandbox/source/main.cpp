#include <iostream>
#include "../../LunarEngine/public/LunarEngineBase.h"

#if defined(_WIN32)
// Windows entry point
LunarEngine::LunarEngineRenderer *vulkanExample;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (vulkanExample != NULL)
	{
		vulkanExample->handleMessages(hWnd, uMsg, wParam, lParam);
	}
	return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	for (size_t i = 0; i < __argc; i++) { LunarEngine::LunarEngineRenderer::args.push_back(__argv[i]); };
	vulkanExample = new LunarEngine::LunarEngineRenderer();
	vulkanExample->initVulkan();
	vulkanExample->setupWindow(hInstance, WndProc);
	vulkanExample->prepare();
	vulkanExample->renderLoop();
	delete(vulkanExample);
	return 0;
}

#elif defined(__ANDROID__)
// Android entry point
VulkanExample *vulkanExample;
void android_main(android_app* state)
{
	vulkanExample = new VulkanExample();
	state->userData = vulkanExample;
	state->onAppCmd = VulkanExample::handleAppCommand;
	state->onInputEvent = VulkanExample::handleAppInput;
	androidApp = state;
	vulkanExample->renderLoop();
	delete(vulkanExample);
}
#elif defined(_DIRECT2DISPLAY)

// Linux entry point with direct to display wsi
// Direct to Displays (D2D) is used on embedded platforms
VulkanExample *vulkanExample;
static void handleEvent()
{
}
int main(const int argc, const char *argv[])
{
	for (size_t i = 0; i < argc; i++) { VulkanExample::args.push_back(argv[i]); };
	vulkanExample = new VulkanExample();
	vulkanExample->initVulkan();
	vulkanExample->prepare();
	vulkanExample->renderLoop();
	delete(vulkanExample);
	return 0;
}
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
VulkanExample *vulkanExample;
int main(const int argc, const char *argv[])
{
	for (size_t i = 0; i < argc; i++) { VulkanExample::args.push_back(argv[i]); };
	vulkanExample = new VulkanExample();
	vulkanExample->initVulkan();
	vulkanExample->setupWindow();
	vulkanExample->prepare();
	vulkanExample->renderLoop();
	delete(vulkanExample);
	return 0;
}
#elif defined(__linux__)

// Linux entry point
VulkanExample *vulkanExample;
static void handleEvent(const xcb_generic_event_t *event)
{
	if (vulkanExample != NULL)
	{
		vulkanExample->handleEvent(event);
	}
}
int main(const int argc, const char *argv[])
{
	for (size_t i = 0; i < argc; i++) { VulkanExample::args.push_back(argv[i]); };
	vulkanExample = new VulkanExample();
	vulkanExample->initVulkan();
	vulkanExample->setupWindow();
	vulkanExample->prepare();
	vulkanExample->renderLoop();
	delete(vulkanExample);
	return 0;
}
#endif