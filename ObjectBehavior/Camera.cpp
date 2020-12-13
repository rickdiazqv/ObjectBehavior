#include "Camera.h"

Camera::Camera(float x, float y, ObjectPlate* plate) :
	_plate(plate),
	Object(x, y, Layer::UI, false, Shape::Dot, PROC_PRIORITY, DRAW_PRIORITY) {

	_plate->setWindowX(_plate->getWindowX() - getWindowX());
	_plate->setWindowY(_plate->getWindowY() - getWindowY());

	setCollisionable(false);
}

Camera::~Camera() {

}

void Camera::update() {
	Object::update();
}

void Camera::draw() {

}