#include "PlaneObject.h"

PlaneObject::PlaneObject() : Object(0, 0, Layer::Character, true) {

}

PlaneObject::~PlaneObject() {

}

void PlaneObject::update() {
	Object::update();
}

void PlaneObject::draw() {

}