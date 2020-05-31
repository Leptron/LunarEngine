#include <iostream>
#include <LunarRenderer.h>

int main() {
	LunarRenderer::LunarRenderer rendererSandbox;
	rendererSandbox.InitResources();
	rendererSandbox.MainLoop();

	return 0;
}