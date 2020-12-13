#include "CircleObject.h"
#include "CircleMorton.h"

CircleObject::CircleObject(Layer layer, bool pers) : 
	CircleObject(X, Y, RADIUS, layer, pers) {

}

CircleObject::CircleObject(float x, float y, Layer layer, bool pers) : 
	CircleObject(x, y, RADIUS, layer, pers) {

}

CircleObject::CircleObject(float radius, Layer layer, bool pers) : 
	CircleObject(X, Y, radius, layer, pers) {

}

CircleObject::CircleObject(float x, float y, float radius, Layer layer, bool pers) : 
	_id("cir" + to_string(cirCnt++)),
	Object(x, y, layer, pers, SHAPE) {

	_radius = radius;
	_radSq = _radius * _radius;
}

CircleObject::~CircleObject() {

}

void CircleObject::createMorton() {
	_morton = new CircleMorton(this);
}

void CircleObject::update() {
	Object::update();
}

void CircleObject::draw() {
	DrawCircleAA(getWindowX(), getWindowY(), _radius, POS_NUM, 0xff0000, FALSE);
}