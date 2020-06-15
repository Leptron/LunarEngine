#include "../../../public/LunarPrimitives/LunarTexture.h"

namespace Lunar2D {
	LunarTexture::LunarTexture() {

	}

	LunarTexture::~LunarTexture() {

	}

	void LunarTexture::LoadTexture(std::string textureLoc) {
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		//wrapping / filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		LunarUtils::LunarImageLoader loader;
		LunarUtils::ImageLoaded ldata = loader.load(textureLoc.c_str());
		unsigned char* data = ldata.imageData;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ldata.width, ldata.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		loader.free();
	}

	void LunarTexture::Use() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
}