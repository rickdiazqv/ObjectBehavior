#include "Input.h"

Input::Input() :
	_id("in"),
	Object(X, Y, Layer::UI, true, SHAPE, PROC_PRIORITY, DRAW_PRIORITY) {
	for (int i = 0; i < n_mouse; i++) { _mouse[i] = 0; }
	setKey(path_key);
}

Input::~Input() {

}

void Input::setKey(const char* path) {
	ifstream ifs(path);
	if (ifs.fail()) {
		printfDx("Failed to open %s", path);
		return;
	}

	string str;
	while (getline(ifs, str)) {
		_key[(unsigned char)strtol(str.c_str(), nullptr, 16)] = 0;
	}

	//for (auto e = _key.begin(); e != _key.end(); e++) {
	//	printfDx("%x:%d, ", e->first, e->second);
	//}
}

void Input::update() {
	if (this != _self) { return; }

	if (_useMouse) {
		int x, y;
		GetMousePoint(&x, &y);
		setWindowVX((float)x - getWindowX());
		setWindowVY((float)y - getWindowY());
		Object::update();

		int mi = GetMouseInput();
		char& ml = _mouse[LEFT], & mm = _mouse[MIDDLE], & mr = _mouse[RIGHT];
		if (mi & MOUSE_INPUT_LEFT) {
			if (0 <= ml && ml < 2) { ml++; }
		}
		else if (ml > 0) { ml = -1; }
		else if (ml == -1) { ml = 0; }

		if (mi & MOUSE_INPUT_MIDDLE) {
			if (0 <= mm && mm < 2) { mm++; }
		}
		else if (mm > 0) { mm = -1; }
		else if (mm == -1) { mm = 0; }

		if (mi & MOUSE_INPUT_RIGHT) {
			if (0 <= mr && mr < 2) { mr++; }
		}
		else if (mr > 0) { mr = -1; }
		else if (mr == -1) { mr = 0; }


	}
	if (_useKey) {
		for (auto e = _key.begin(); e != _key.end(); e++) {
			unsigned char k = e->first;
			char& v = e->second;
			int key = CheckHitKey(k);
			if (key) { if (0 <= v && v < 2) { v++; } }
			else if (v > 0) { v = -1; }
			else if (v == -1) { v = 0; }
		}

	}
}

void Input::draw() {
	char icon[2] = { 'N', '\0' };
	char& c = icon[0];

	if (isMouse(LEFT)) {
		c = 'L';
	}
	else if (isMouse(MIDDLE)) {
		c = 'M';
	}
	else if (isMouse(RIGHT)) {
		c = 'R';
	}

	DrawFormatString(getWindowX(), getWindowY(),
		isCollision() ? 0xff0000 : 0xffffff, icon);

	DrawFormatString(200, WINDOW_Y - 200, 0xffffff, "wld(%f, %f)", getWorldX(), getWorldY());
	DrawFormatString(200, WINDOW_Y - 100, 0xffffff, "win(%f, %f)", getWindowX(), getWindowY());
}

string Input::toString() {
	ostringstream oss;
	/*oss << "xy: (" << setw(4) << getX() << ", " << setw(4) << getY() <<
		"), hist: (" << setw(4) << getXHist() << ", " << setw(4) << getYHist() <<
		"), d: (" << setw(4) << getDX() << ", " << setw(4) << getDY() <<
		"), move: " << (isMove() ? " true" : "false") <<
		", mouse: (" << setw(2) << int(_mouse[0]) << setw(2) << int(_mouse[1]) << setw(2) << int(_mouse[2]) <<
		"), \nkeysize: " << _key.size() << "key: (";

	for (auto e = _key.begin(); e != _key.end(); e++) {
		oss << setw(2) << (int)e->second;
	}
	oss << ")";*/

	return oss.str();
}