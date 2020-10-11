#pragma once
#include "define.h"
#include "Object.h"
#include "RectangleMorton.h"

class RectangleObject : public Object{
protected:
	inline static const float LEFT = .0f, TOP = .0f, WIDTH = .0f, HEIGHT = .0f;

private:
	inline static const Shape SHAPE = Shape::Rectangle;
	inline static int rectCnt = 0;

protected:
	float _left = LEFT, _top = TOP, _width = WIDTH, _height = HEIGHT;

private:
	const string id;

public:
	RectangleObject(Layer layer, bool pers = false);
	RectangleObject(float width, float height, Layer layer, bool pers = false);
	RectangleObject(float x, float y, float width, float height, Layer layer, bool pers = false);
	~RectangleObject();

protected:
	void createMorton() override;

public:
	inline float getLeft() { return _left; }
	inline float getTop() { return _top; }
	inline float getWidth() { return _width; }
	inline float getHeight() { return _height; }
	inline string getId() override { return id; }

public:
	void update() override;
	void draw() override;
	string toString() override;

};