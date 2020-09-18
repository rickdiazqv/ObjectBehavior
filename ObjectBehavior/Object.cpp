#include "Object.h"

Object::Object() : Object(X, Y, LAYER, PERS) {

}

Object::Object(int x, int y, Layer layer, bool pers) : Worker(
	// proc comparator
	nullptr,

	// draw comparator
	[](Worker* self, Worker* other) {
		Object* slf = nullptr, * otr = nullptr;
		int comp = 0;

		try {
			slf = (Object*)self;
			otr = (Object*)other;
		}
		catch (bad_cast e) {
			printfDx("bad cast\n");
			return comp;
		}

		comp = int(slf->getLayer()) - int(otr->getLayer());
		if (comp == 0) {
			bool pslf = slf->getPers();
			bool potr = otr->getPers();

			if (pslf && potr) {
				comp = slf->getY() - otr->getY();
			}
			else if (pslf && !potr) {
			}
			else if (!pslf && potr) {
				comp = -1;
			}
			else {

			}
		}

		return comp;
	}) {
	printfDx("Object\n");
	_layer = layer;
	_pers = pers;

	_x = x;
	_y = y;

	Awake();
}

Object::~Object() {

}

void Object::update() {
	_x_hist = _x;
	_y_hist = _y;

	_x += vx;
	_y += vy;

	vx += ax;
	vy += ay;

	int dy = getDY();
	if (getX() == 111 && getY() >= 444) {
		int a = 0;
	}
	if (dy != 0) { sortSelf(this, dy); }
}

string Object::toString() {
	ostringstream oss;
	oss << "Layer: " << int(getLayer()) << ", pers: " << getPers() << ", (" << _x << ", " << _y << ")";
	return oss.str();
}

void Object::Awake() {

}

void Object::Start() {

}

void Object::Update() {

}

void Object::Draw() {

}