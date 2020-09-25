#include "Object.h"

Object::Object() : Object(X, Y, LAYER, PERS) {

}

Object::Object(float x, float y, Layer layer, bool pers) : Worker(PROC_PRIORITY, DRAW_PRIORITY){
	printfDx("Object\n");
	_layer = layer;
	_pers = pers;

	_x = x;
	_y = y;
	_x_hist = getX();
	_y_hist = getY();

	morton.setMorton(getX(), getY());

	Awake();
}

Object::~Object() {

}

void Object::update() {
	_x_hist = getX();
	_y_hist = getY();

	_x += vx;
	_y += vy;

	vx += ax;
	vy += ay;

	float dx = getDX(), dy = getDY();
	if (dy != .0f) { sortSelf(this, dy >= .0f ? 1 : -1); }
	if (isMove()) {
		morton.setMorton(getX(), getY());
	}
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

int Object::drawCompareTo(Worker* other) {
	Object* otr = dynamic_cast<Object*>(other);
	int comp = 0;
	if (!otr) {
		printfDx("can not cast\n");
		return this->getDrawPriority() - other->getDrawPriority();
	}

	comp = int(this->getLayer()) - int(otr->getLayer());
	if (comp == 0) {
		bool pslf = this->getPers();
		bool potr = otr->getPers();

		if (pslf && potr) {
			comp = (this->getY() - otr->getY()) >= .0f ? 1 : -1;
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
}