#pragma once
#include "define.h"
#include "Object.h"
#include "RectangleMorton.h"

class RectangleObject : public Object {
protected:
	inline static const float LEFT = .0f, TOP = .0f, WIDTH = .0f, HEIGHT = .0f;

private:
	inline static const Shape SHAPE = Shape::Rectangle;
	inline static int rectCnt = 0;

protected:
	float _worldLeft = LEFT, _windowLeft = LEFT;
	float _worldTop = TOP, _windowTop = TOP;
	float _width = WIDTH, _height = HEIGHT;

private:
	const string _id;

public:
	RectangleObject(Layer layer, bool pers = false);
	RectangleObject(float width, float height,
		Layer layer, bool pers = false);
	RectangleObject(float x, float y, float width, float height,
		Layer layer, bool pers = false);
	RectangleObject(float x, float y, float width, float height,
		int procPriority, int drawPriority, Layer layer, bool pers = false);
	~RectangleObject();

protected:
	void createMorton() override;

public:
	inline float getWorldLeft() { return _worldLeft; }
	inline float getWorldTop() { return _worldTop; }
	inline float getWindowLeft() { return _windowLeft; }
	inline float getWindowTop() { return _windowTop; }
	inline float getWidth() { return _width; }
	inline float getHeight() { return _height; }
	inline string getId() override { return _id; }

protected:
	inline void setWidth(float width) {
		_width = width;
		setWorldLeft(getWorldX() - getWidth() * .5f);
	}
	inline void setHeight(float height) {
		_height = height;
		setWorldTop(getWorldY() - getHeight() * .5f);
	}

private:
	inline void setWorldLeft(float left) {
		_worldLeft = left;
		setWindowLeft(getWorldLeft() + getCorrectionX());
	}
	inline void setWorldTop(float top) {
		_worldTop = top;
		setWindowTop(getWorldTop() + getCorrectionY());
	}
	inline void setWindowLeft(float left) { _windowLeft = left; }
	inline void setWindowTop(float top) { _windowTop = top; }

public:
	void update() override;
	void draw() override;
	string toString() override;

};