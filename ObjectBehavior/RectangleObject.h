#pragma once
#include "package.h"
#include "Object.h"

class RectangleObject : public Object {
protected:
	inline static const int LEFT = 0, TOP = 0, WIDTH = 0, HEIGHT = 0;
	int _left = LEFT, _top = TOP, _width = WIDTH, _height = HEIGHT;

public:
	RectangleObject(Layer layer, bool pers = false);
	RectangleObject(int width, int height, Layer layer, bool pers = false);
	RectangleObject(int x, int y, int width, int height, Layer layer, bool pers = false);
	~RectangleObject();

public:
	void update() override;
	void draw() override;
};

