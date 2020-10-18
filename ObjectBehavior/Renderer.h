#pragma once
#include "define.h"
#include "Object.h"
#include "Sprite.h"

class Renderer {
private:
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
	Renderer(Object* const obj, const string& sprite);
	Renderer(Object* const obj, const string& sprite, const string& divSprite);
	~Renderer();

private:
	Renderer(Object* const obj, Sprite* const sprite);

public:
	void render();
	inline void load() { getSprite()->load(); }

public:
	inline Sprite* getSprite() { return _sprite; }
	inline float getScaleX() { return _scaleX; }
	inline float getScaleY() { return _scaleY; }
	inline float getWidth() { return _width; }
	inline float getHeight() { return _height; }
	inline float getX() { return _x; }
	inline float getY() { return _y; }

private:
	inline float getLeft() { return _left; }
	inline float getTop() { return _top; }
	inline void setLeft(float left) { _left = left; }
	inline void setTop(float top) { _top = top; }
	inline void setWidth(float width) { _width = width; }
	inline void setHeight(float height) { _height = height; }
};

