#include "Renderer.h"
#include "SpriteManager.h"

Renderer::Renderer(Object* obj, string sprite) :_parent(obj), _sprite(SpriteManager::getInstance()->getSprite(sprite)) {

}

Renderer::~Renderer() {

}