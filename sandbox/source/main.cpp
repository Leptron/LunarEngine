#include <iostream>
#include <LunarEngine.h>

int main() {
	LunarEngine::LunarEngine engine;
	engine.InitResources();
	engine.MainLoop();
}