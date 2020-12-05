#include "Renderer.h"
#include "SpriteManager.h"

Renderer::Renderer(Object* const parent, const string& sprite) :
	Renderer(parent, SpriteManager::getInstance()->getSprite(sprite)) {

}

Renderer::Renderer(
	Object* const parent,
	const string& sprite,
	const string& divSprite) :
	Renderer(parent, SpriteManager::getInstance()->getSprite(sprite, divSprite)) {

}

Renderer::Renderer(Object* const parent, Sprite* const sprite) :
	_sprite(sprite), _parent(parent) {

	updateWidth();
	updateHeight();
	updateLeft();
	updateTop();
}

Renderer::~Renderer() {

}


void Renderer::render() {
	int x = (int)(getParent()->getX() + getLeft());
	int y = (int)(getParent()->getY() + getTop());

	if (_scaleX == 1.f && _scaleY == 1.f) {
		DrawFormatString(winx / 2, 0, 0xffffff, "%d", _sprite->getHandle());
		DrawGraph(x, y, getSprite()->getHandle(), TRUE);
	}
	else {
		DrawExtendGraph(x, y, x + getWidth(), y + getHeight(), getSprite()->getHandle(), TRUE);
	}
}