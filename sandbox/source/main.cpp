#include <iostream>
#include <LunarLayerManager.h>
#include <LunarVkDatatypes.h>
#include <LunarRenderer.h>
#include <LunarEngine.h>

int main() {
	LunarEngine::LunarEngine engine;
	engine.InitResources();
	engine.MainLoop();
}