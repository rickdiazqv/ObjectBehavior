#pragma once
#include "define.h"
#include "Object.h"
#include "RectangleMorton.h"

class RectangleObject : public Object{
protected:
	inline static const float LEFT = .0f, TOP = .0f, WIDTH = .0f, HEIGHT = .0f;

private:
	inline static const Shape SHAPE = Shape::Rectangle;

protected:
	float _left = LEFT, _top = TOP, _width = WIDTH, _height = HEIGHT;

public:
	RectangleObject(Layer layer, bool pers = false);
	RectangleObject(float width, float height, Layer layer, bool pers = false);
	RectangleObject(float x, float y, float width, float height, Layer layer, bool pers = false);
	~RectangleObject();

protected:
	void createMorton() override;

public:
	float getLeft() { return _left; }
	float getTop() { return _top; }
	float getWidth() { return _width; }
	float getHeight() { return _height; }

public:
	void update() override;
	void draw() override;
	string toString() override;

};