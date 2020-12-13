#include "RectangleObject.h"

RectangleObject::RectangleObject(Layer layer, bool pers) :
	RectangleObject(WIDTH, HEIGHT, layer, pers) {

}

RectangleObject::RectangleObject(
	float width, float height, Layer layer, bool pers) :
	RectangleObject(X, Y, width, height, layer, pers) {

}

RectangleObject::RectangleObject(
	float x, float y, float width, float height, Layer layer, bool pers) :
	RectangleObject(
		x, y, width, height, PROC_PRIORITY, DRAW_PRIORITY, layer, pers) {
}

RectangleObject::RectangleObject(
	float x, float y, float width, float height,
	int procPriority, int drawPriority, Layer layer, bool pers) :
	_id("rect" + to_string(rectCnt++)),
	Object(x, y, layer, pers, SHAPE, procPriority, drawPriority) {
	setWidth(width);
	setHeight(height);

	Start();
}

RectangleObject::~RectangleObject() {

}

void RectangleObject::createMorton() {
	_morton = new RectangleMorton(this);
}

void RectangleObject::update() {
	Object::update();

	if (getWorldX() != getWorldXHist()) {
		setWorldLeft(getWorldX() - getWidth() * .5f);
	}
	if (getWorldY() != getWorldYHist()) {
		setWorldTop(getWorldY() - getHeight() * .5f);
	}
}

void RectangleObject::draw() {
	float left = getWindowLeft();
	float top = getWindowTop();
	DrawBoxAA(left, top, left + getWidth(), top + getHeight(), isCollision() ? 0x0000ff : 0xff0000, FALSE);
	DrawFormatString(left, top, 0, getId().c_str());

	/*float left = .0f;
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

	DrawBoxAA(left, top, left + scale * float(winx), top + scale * float(winy), 0xffff00, FALSE);*/
}

string RectangleObject::toString() {
	ostringstream oss;
	oss <<
		"Layer: " << int(getLayer()) <<
		", pers: " << getPers() <<
		", xy(" << getWorldX() << ", " << getWorldY() <<
		"), (" << getWindowX() << ", " << getWindowY() <<
		"), wh(" << _width << ", " << _height <<
		"), morton: " << _morton->getDepth() <<
		":" << _morton->getMorton(_morton->getDepth()) <<
		endl;
	return oss.str();
}