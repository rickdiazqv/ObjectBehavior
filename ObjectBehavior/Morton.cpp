#include "Morton.h"

Morton::Morton() {
	for (int i = 0; i < DEPTH; i++) {
		_id[i] = ID;
	}
}

Morton::~Morton() {

}

void Morton::setMorton(float x, float y) {
	int id = getOrder(x, y);
	int deep = id % 4;
	_scale = SCALE;

	if (deep == _id[DEPTH - 1]) { return; }

	_id[DEPTH - 1] = deep;
	_absId = id;
	id >>= 2;
	for (int i = DEPTH - 2; i >= 0; i--, id >>= 2) {
		_id[i] = id % 4;
	}
}

void Morton::drawGrid() {
	for (int i = 1; i < pow(2, DEPTH); i++) {
		DrawLineAA(.0f, i * DY, winx, i * DY, 0x00ff00);
		DrawLineAA(i * DX, .0f, i * DX, winy, 0x00ff00);
	}
}

int Morton::getOrder(float x, float y) {
	int cx = int(x / DX);
	int cy = int(y / DY);
	int dig = 0;
	int res = 0;

	if (cx > cy) { dig = log2(cx); }
	else { dig = log2(cy); }
	//if (dig % 2) { dig++; }

	for (int i = 0; i < dig; i++, cx >>= 1, cy >>= 1) {
		res += (cx % 2) << (2 * i);
		res += (cy % 2) << (2 * i + 1);
	}

	return res;
}

int Morton::log2(int v) {
	int res = 1;
	while ((v /= 2) != 0) { res++; }
	return res;
}