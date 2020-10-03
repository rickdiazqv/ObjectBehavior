#include "PlaneObject.h"

PlaneObject::PlaneObject() : Object(0, 0, Layer::Character, true, SHAPE) {

}

PlaneObject::~PlaneObject() {

}

void PlaneObject::update() {
	Object::update();
}

void PlaneObject::draw() {

}