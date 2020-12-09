#pragma once
#include "define.h"
#include "Object.h"
#include "Sprite.h"

class Renderer {
protected:
	inline static const float SCALE = 1.f;
	inline static const float X = .0f, Y = .0f;
	inline static const float LEFT = .0f, TOP = .0f, WIDTH = .0f, HEIGHT = .0f;

private:
	Sprite* const _sprite;
	float _scaleX = SCALE, _scaleY = SCALE;
	float _x = X, _y = Y;
	float _left = LEFT, _top = TOP, _width = WIDTH, _height = HEIGHT;

	Object* const _parent = nullptr;

public:
	Renderer(Object* const parent, const string& sprite);
	Renderer(Object* const parent, const string& sprite, const string& divSprite);
	~Renderer();

private:
	Renderer(Object* const parent, Sprite* const sprite);

public:
	virtual void render();
	inline void load() { getSprite()->load(); }

public:
	inline Sprite* getSprite() { return _sprite; }
	inline float getScaleX() { return _scaleX; }
	inline float getScaleY() { return _scaleY; }
	inline float getWidth() { return _width; }
	inline float getHeight() { return _height; }
	inline float getX() { return _x; }
	inline float getY() { return _y; }

protected:
	inline Object* getParent() { return _parent; }
	inline float getLeft() { return _left; }
	inline float getTop() { return _top; }

public:
	inline virtual void setScale(float scaleX, float scaleY) {
		setScaleX(scaleX);
		setScaleY(scaleY);
	}
	inline virtual void setScaleX(float scaleX) {
		_scaleX = scaleX;
		updateWidth();
	}
	inline virtual void setScaleY(float scaleY) {
		_scaleY = scaleY;
		updateHeight();
	}
	inline virtual void setPos(float x, float y) {
		setX(x);
		setY(y);
	}
	inline virtual void setX(float x) {
		_x = x;
		updateLeft();
	}
	inline virtual void setY(float y) {
		_y = y;
		updateTop();
	}

private:
	inline void setLeft(float left) { _left = left; }
	inline void setTop(float top) { _top = top; }
	inline void setWidth(float width) {
		_width = width;
		updateLeft();
	}
	inline void setHeight(float height) {
		_height = height;
		updateTop();
	}
	inline void updateWidth() {
		setWidth(getScaleX() * (float)getSprite()->getSizeX());
	}

	inline void updateHeight() {
		setHeight(getScaleY() * (float)getSprite()->getSizeY());
	}
	inline void updateLeft() {
		setLeft(getX() - getWidth() / 2.f);
	}
	inline void updateTop() {
		setTop(getY() - getHeight() / 2.f);
	}
};

