#include "BackGround.h"
#include "SpriteManager.h"

BackGround::BackGround() : 
	_id("bgi" + to_string(bgCnt++)),
	RectangleObject(WINDOW_X / 2, WINDOW_Y / 2, WINDOW_X, WINDOW_Y,
		Layer::BackGround) {

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