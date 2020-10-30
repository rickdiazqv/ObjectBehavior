#include "BackGround.h"
#include "SpriteManager.h"

BackGround::BackGround() : RectangleObject(winx / 2, winy / 2, WIDTH, HEIGHT, Layer::BackGround) {
	setCollisionable(false);
	SpriteManager::getInstance()->getSprite(_master)->load();
}

BackGround::~BackGround() {

}

void BackGround::update() {
	RectangleObject::update();
}

void BackGround::draw() {
	_renderer.render();
}