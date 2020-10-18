#include "Button.h"
#include "SpriteManager.h"

Button::Button(float x, float y) : _id("btn" + to_string(btnCnt)), RectangleObject(x, y, WIDTH, HEIGHT, Layer::UI) {
	/*for (Renderer& renderer : _renderer) {
		renderer.load();
	}*/
	SpriteManager::getInstance()->getSprite(_master)->load();

	setWidth(_renderer[0].getWidth());
	setHeight(_renderer[0].getHeight());

	//printfDx("%d\n", _renderer[0].getSprite()->getHandle());
	//printfDx("(,%d, %d), (%d,%d)\n", getX(), getY(), getLeft(), getTop());

	btnCnt++;
}

void Button::update() {
	RectangleObject::update();
}

void Button::draw() {
	if (isCollision()) {
		if (_input.isMouse(Input::LEFT)) {
			type = 1;
		}
		else {
			type = 2;
		}
	}
	else {
		type = 0;
	}
	_renderer[type].render();
	RectangleObject::draw();
}