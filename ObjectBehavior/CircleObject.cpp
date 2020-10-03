#include "CircleObject.h"

CircleObject::CircleObject(Layer layer, bool pers) : CircleObject(X, Y, RADIUS, layer, pers) {

}

CircleObject::CircleObject(float x, float y, Layer layer, bool pers) : CircleObject(x, y, RADIUS, layer, pers) {

}

CircleObject::CircleObject(float radius, Layer layer, bool pers) : CircleObject(X, Y, radius, layer, pers) {

}

CircleObject::CircleObject(float x, float y, float radius, Layer layer, bool pers) : Object(x, y, layer, pers, SHAPE) {

	_radius = radius;
	_radSq = _radius * _radius;
}

CircleObject::~CircleObject() {

}