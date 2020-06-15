#include "../../public/LunarImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <tinygltf/stb_image.h>

namespace LunarUtils {
	LunarImageLoader::LunarImageLoader() {

	}

	LunarImageLoader::~LunarImageLoader() {

	}

	ImageLoaded LunarImageLoader::load(const char* path) {
		int width, height, nrChannels;
		imageData = stbi_load(path, &width, &height, &nrChannels, 0);

		ImageLoaded loadRet = {};
		loadRet.imageData = imageData;
		loadRet.width = width;
		loadRet.height = height;
		loadRet.nrChannels = nrChannels;

		return loadRet;
	}

	void LunarImageLoader::free() {
		stbi_image_free(imageData);
	}
}