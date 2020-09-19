#include "Input.h"

Input::Input() : Worker([](Worker* self, Worker* other) {return -1; }, [](Worker* self, Worker* other) {return -1; }) {
	for (int i = 0; i < n_key; i++) { _key[i] = 0; }
	if (!_self) { _self = this; }
}

void Input::update() {
	if (this != _self) { return; }

	GetMousePoint(&_mx, &_my);
	GetMouseInput();
	GetHitKeyStateAll(_key);
}

void Input::draw() {

}

string Input::toString() {
	ostringstream oss;
	oss << "Input: (" << getMouseX() << ", " << getMouseY() << "), move: " << isMove();
	return oss.str();
}