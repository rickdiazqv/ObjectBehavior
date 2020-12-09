#include "Window.h"
#include "SpriteManager.h"

Window::Window(
	float x,
	float y,
	float width,
	float height,
	string&& master,
	vector<int>&& varX,
	vector<int>&& varY) :
	_id("wnd" + to_string(wndCnt++)),
	_master(move(master)),
	RectangleObject(x, y, width, height, Layer::UI) {

	Sprite* sprite = SpriteManager::getInstance()->getSprite(_master);

	sprite->load();
	_renderer.Renderer::setScaleX(getWidth() / (float)sprite->getSizeX());
	_renderer.Renderer::setScaleY(getHeight() / (float)sprite->getSizeY());
	_renderer.setVarArea(move(varX), move(varY));
}

Window::~Window() {

}

void Window::update() {

}

void Window::draw() {
	_renderer.render();
}