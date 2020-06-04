#include <iostream>
#include <LunarLayerManager.h>
#include <LunarVkDatatypes.h>
#include <LunarRenderer.h>

int main() {
	std::vector<LunarRenderer::Vertex> layerTestVerts = {
		{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
	};

	std::vector<uint32_t> layerTestIndices = {
		 0, 1, 2, 2, 3, 0
	};

	LunarRenderer::LunarRenderer rendererSandbox;
	rendererSandbox.InitResources();
	LunarRenderer::LayerManager objectRenderer = LunarRenderer::LayerManager(&rendererSandbox.globConstruct());
	
	objectRenderer.CreateObject(layerTestVerts, layerTestIndices, "basic_pos", false);
	objectRenderer.AllocateObjects();
	
	rendererSandbox.AttachManager(&objectRenderer);
	
	rendererSandbox.CreateCommandBuffers();
	rendererSandbox.LayerLoop();
}