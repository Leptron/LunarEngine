#pragma once

namespace LunarUtils {
	struct ImageLoaded {
		int width, height, nrChannels;
		unsigned char* imageData;
	};
	class LunarImageLoader {
	public:
		unsigned char* imageData;

		LunarImageLoader();
		~LunarImageLoader();

		ImageLoaded load(const char* path);
		void free();
	};
}