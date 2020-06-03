#include <iostream>
#include <LunarRenderer.h>
#include <LunarVkDatatypes.h> 

int main() {
	//layer testing
	std::vector<LunarRenderer::Vertex> layerTestVerts = {
		{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
	};

	std::vector<uint32_t> layerTestIndices = {
		 0, 1, 2, 2, 3, 0
	};

	//create a geometry object
	LunarRenderer::Geometry layerTestGeometry = {};
	//only set those two
	layerTestGeometry.Vertices = layerTestVerts;
	layerTestGeometry.Indices = layerTestIndices;
	layerTestGeometry.materialIndex = 0;

	LunarRenderer::LunarRenderer rendererSandbox;
	rendererSandbox.InitResources();
	
	
	int i = rendererSandbox.AddGeometry(layerTestGeometry);
	int x = rendererSandbox.FlushGeometry();
	

	rendererSandbox.CreateMaterial("basic_pos", 1);

	rendererSandbox.FlushToCommandBuffer();

	rendererSandbox.MainLoop();

	return 0;
}