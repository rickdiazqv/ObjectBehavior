#include "Plane.h"

Plane::Plane() : Object(0, 0, Layer::Character, true) {

}

Plane::~Plane() {

}

void Plane::update() {
	Object::update();
}

void Plane::draw() {

}