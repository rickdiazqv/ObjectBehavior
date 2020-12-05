#include "Window.h"
#include "SpriteManager.h"

Window::Window(float x, float y) : 
	Window(x, y, WIDTH, HEIGHT) {

}

Window::Window(float x, float y, float width, float height) :
	_id("wnd" + to_string(wndCnt++)),
	RectangleObject(x, y, width, height, Layer::UI) {

	Sprite* master = SpriteManager::getInstance()->getSprite(_master);

	master->load();
	_renderer.setScaleX(getWidth() / (float)master->getSizeX());
	_renderer.setScaleY(getHeight() / (float)master->getSizeY());
	_renderer.setVarAreaX(false, 3, 4);
	_renderer.setVarAreaY(false, 3, 4);
	_renderer.updateRenderingParam();
}

Window::~Window() {

}

void Window::update() {

}

void Window::draw() {
	_renderer.render();
}