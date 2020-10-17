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
	Sprite* _sprite;
	float _scaleX = SCALE, _scaleY = SCALE;
	float _x = X, _y = Y;
	float _left = LEFT, _top = TOP, _width = WIDTH, _height = HEIGHT;

	Object* const _parent = nullptr;

public:
	Renderer(Object* obj, string sprite);
	~Renderer();

public:
	inline void render() {
		float fx = _parent->getX() + getLeft();
		float fy = _parent->getY() + getTop();
		int x = (int)fx, y = (int)fy;

		if (_scaleX == 1.f && _scaleY == 1.f) {
			DrawGraph(x, y, _sprite->getHandle(), TRUE);
		}
		else {
			DrawExtendGraph(x, y, x + getWidth(), y + getHeight(), _sprite->getHandle(), TRUE);
		}
	}

public:
	inline float getScaleX() { return _scaleX; }
	inline float getScaleY() { return _scaleY; }
	inline float getWidth() { return _width; }
	inline float getHeight() { return _height; }
	inline float getX() { return _x; }
	inline float getY() { return _y; }

private:
	inline float getLeft() { return _left; }
	inline float getTop() { return _top; }
};

