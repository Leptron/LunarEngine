#include <iostream>
#include <LunarRenderer.h>
#include <LunarVkDatatypes.h>

int main() {
	//layer testing
	std::vector<LunarRenderer::Vertex> layerTestVerts = {
		{{1.0f,  1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
		{ { -1.0f,  1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
		{ {  0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } }
	};

	std::vector<uint32_t> layerTestIndices = {
		0, 1, 2
	};

	//create a geometry object
	LunarRenderer::Geometry layerTestGeometry = {};
	//only set those two
	layerTestGeometry.Vertices = layerTestVerts;
	layerTestGeometry.Indices = layerTestIndices;

	LunarRenderer::LunarRenderer rendererSandbox;
	rendererSandbox.InitResources();

	int i = rendererSandbox.AddGeometry(layerTestGeometry);
	int x = rendererSandbox.FlushGeometry();

	std::cout << x << std::endl;

	rendererSandbox.MainLoop();

	return 0;
}