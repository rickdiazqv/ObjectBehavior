#include "RectangleObject.h"

RectangleObject::RectangleObject(Layer layer, bool pers) : RectangleObject(WIDTH, HEIGHT, layer, pers) {

}

RectangleObject::RectangleObject(int width, int height, Layer layer, bool pers) : RectangleObject(X, Y, width, height, layer, pers) {

}

RectangleObject::RectangleObject(int x, int y, int width, int height, Layer layer, bool pers) : Object(x, y, layer, pers) {
	_width = width;
	_height = height;

	_left = _x - _width / 2;
	_top = _y - _height / 2;

	Start();
}

RectangleObject::~RectangleObject() {

}

void RectangleObject::update() {
	Object::update();

	if (_x != _x_hist) { _left = _x - _width / 2; }
	if (_y != _y_hist) { _top = _y - _height / 2; }
}

void RectangleObject::draw() {
	DrawBox(_left, _top, _left + _width, _top + _height, 0xff0000, TRUE);
	//printfDx("%s\n", toString().c_str());
}

string RectangleObject::toString() {
	ostringstream oss;
	oss << "Layer: " << int(getLayer()) << ", pers: " << getPers() << ", xy(" << _x << ", " << _y << "), wh(" << _width << ", " << _height << ")" << endl;
	return oss.str();
}