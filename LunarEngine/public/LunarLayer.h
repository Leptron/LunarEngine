#pragma once
#include "LunarObject.h"

#include <vector>
#include <string>

namespace LunarRenderer {
	class Layer {
	public:
		Layer();

		void addObject(LunarOpenglObject obj, std::string id);
		void Draw();
		void Clean();
	private:
		std::vector<LayerObject> objects;
	};
}