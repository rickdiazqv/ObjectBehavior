#include "Object.h"

Object::Object() : Worker(nullptr, nullptr) {

}

Object::Object(int x, int y, Layer layer, bool pers) : Worker(
	[](Task* self, Task* other) {
		Object* slf = nullptr, * otr = nullptr;
		int comp = 0;

		try {
			slf = (Object*)self;
			otr = (Object*)other;
		}
		catch (bad_cast e) {
			return comp;
		}

		comp = int(slf->getLayer()) - int(otr->getLayer());
		if (comp == 0 && slf->getPers()) {
			comp = slf->getY() - otr->getY();
		}

		return comp;
	},

	[](Task* self, const char* args) {
		printfDx("init\n");
		auto obj = (Object*)self;
		obj->_x = va_arg(args, int);
		obj->_y = va_arg(args, int);
		obj->_layer = va_arg(args, Layer);
		obj->_pers = va_arg(args, bool);
		va_end(args);

		printfDx("%x, %s\n", obj, obj->toString().c_str());
	}, nullptr, x, y, layer, pers) {

	Awake();
}

Object::~Object() {

}

void Object::Awake() {

}

void Object::Start() {

}

void Object::Update() {

}

void Object::Draw() {

}

string Object::toString() {
	ostringstream oss;
	printfDx("toString\n");
	oss << "Layer: " << int(getLayer()) << ", pers: " << getPers() << ", (" << _x << ", " << _y << ")";
	return oss.str();
}