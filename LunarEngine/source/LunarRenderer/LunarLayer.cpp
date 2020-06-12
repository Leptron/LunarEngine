#include "../../public/LunarLayer.h"

namespace LunarRenderer {
	Layer::Layer() {

	}

	void Layer::addObject(LunarOpenglObject obj, std::string id) {
		LayerObject appendObject = {};
		appendObject.object = obj;
		appendObject.id = id;

		objects.push_back(appendObject);
	}

	void Layer::Draw() {
		for (auto object : objects)
			object.object.Draw();
	}

	void Layer::Clean() {
		for (auto object : objects)
			object.object.Clean();
	}
}