#include "RectangleObject.h"

RectangleObject::RectangleObject(Layer layer, bool pers) : RectangleObject(WIDTH, HEIGHT, layer, pers) {

}

RectangleObject::RectangleObject(float width, float height, Layer layer, bool pers) : RectangleObject(X, Y, width, height, layer, pers) {

}

RectangleObject::RectangleObject(float x, float y, float width, float height, Layer layer, bool pers) : id("rect" + to_string(rectCnt)), Object(x, y, layer, pers, SHAPE) {
	_width = width;
	_height = height;

	_left = _x - _width * .5f;
	_top = _y - _height * .5f;

	rectCnt++;

	Start();
}

RectangleObject::~RectangleObject() {

}

void RectangleObject::createMorton() {
	_morton = new RectangleMorton(this);
}

void RectangleObject::update() {
	Object::update();

	if (_x != _xHist) { _left = _x - _width * .5f; }
	if (_y != _yHist) { _top = _y - _height * .5f; }
}

void RectangleObject::draw() {
	DrawBoxAA(_left, _top, _left + _width, _top + _height, _collision ? 0x0000ff : 0xff0000, FALSE);
	DrawFormatString(_left, _top, 0, getId().c_str());

	float left = .0f;
	float top = .0f;
	int depth = _morton->getDepth();
	float scale = 2.f;
	for (int i = 0; i <= depth; i++) {
		int id = _morton->getMorton(i);
		scale *= .5f;
		left += scale * float(id % 2);
		top += scale * float(id >> 1);
	}
	left *= float(winx);
	top *= float(winy);

	DrawBoxAA(left, top, left + scale * float(winx), top + scale * float(winy), 0xffff00, FALSE);
}

string RectangleObject::toString() {
	ostringstream oss;
	oss <<
		"Layer: " << int(getLayer()) <<
		", pers: " << getPers() <<
		", xy(" << _x << ", " << _y <<
		"), wh(" << _width << ", " << _height <<
		"), morton: " << _morton->getDepth() <<
		":" << _morton->getMorton(_morton->getDepth()) <<
		endl;
	return oss.str();
}