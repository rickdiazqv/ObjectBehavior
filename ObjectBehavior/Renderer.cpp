#include "Renderer.h"
#include "SpriteManager.h"

Renderer::Renderer(Object* const obj, const string& sprite) :
	Renderer(obj, SpriteManager::getInstance()->getSprite(sprite)) {

}

Renderer::Renderer(
	Object* const obj,
	const string& sprite,
	const string& divSprite) :
	Renderer(obj, SpriteManager::getInstance()->getSprite(sprite, divSprite)) {
	int a = 0;
}

Renderer::Renderer(Object* const obj, Sprite* const sprite) :
	_sprite(sprite), _parent(obj) {

	setWidth((float)getSprite()->getSizeX());
	setHeight((float)getSprite()->getSizeY());
	setLeft(getX() - getWidth() / 2);
	setTop(getY() - getHeight() / 2);
}

Renderer::~Renderer() {

}


void Renderer::render() {
	float px = _parent->getX();
	float py = _parent->getY();
	float l = getLeft();
	float t = getTop();
	float fx = _parent->getX() + getLeft();
	float fy = _parent->getY() + getTop();
	int x = (int)fx, y = (int)fy;

	if (_scaleX == 1.f && _scaleY == 1.f) {
		DrawFormatString(winx / 2, 0, 0xffffff, "%d", _sprite->getHandle());
		DrawGraph(x, y, _sprite->getHandle(), TRUE);
	}
	else {
		DrawExtendGraph(x, y, x + getWidth(), y + getHeight(), _sprite->getHandle(), TRUE);
	}
}