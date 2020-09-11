#include "RectangleObject.h"

RectangleObject::RectangleObject() {

}

RectangleObject::RectangleObject(int width, int height) : RectangleObject(LEFT, TOP, width, height){

}

RectangleObject::RectangleObject(int left, int top, int width, int height) : RectangleObject(){
	_left = left;
	_top = top;
	_width = width;
	_height = height;
}

RectangleObject::~RectangleObject() {

}

void RectangleObject::update() {

}

void RectangleObject::draw() {
	DrawBox(_left, _top, _left + _width, _top + _height, 0xff0000, TRUE);
}