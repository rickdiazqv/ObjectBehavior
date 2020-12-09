#include "Camera.h"

Camera::Camera(float x, float y, ObjectPlate* plate) :
	_plate(plate),
	Object(x, y, Layer::UI, false, Shape::Dot, PROC_PRIORITY, DRAW_PRIORITY) {

	_plate->setX(_plate->getX() - getX());
	_plate->setY(_plate->getY() - getY());
}

Camera::~Camera() {

}