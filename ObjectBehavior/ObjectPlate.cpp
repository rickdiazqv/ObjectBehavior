#include "ObjectPlate.h"

ObjectPlate::ObjectPlate(float width, float height,
	Layer layer, bool pers) :
	ObjectPlate(X, Y, width, height, layer, pers) {

}

ObjectPlate::ObjectPlate(float x, float y, float width, float height,
	Layer layer, bool pers) :
	RectangleObject(
		x, y, width, height, PROC_PRIORITY, DRAW_PRIORITY, layer, pers) {

}

ObjectPlate::~ObjectPlate() {

}

void ObjectPlate::update() {

}

void ObjectPlate::draw() {

}

ObjectPlate* const ObjectPlate::DEFAULT_PLATE = new ObjectPlate(
	float(WINDOW_X) * .5f, float(WINDOW_Y) * .5f,
	WINDOW_X, WINDOW_Y, Layer::Default);