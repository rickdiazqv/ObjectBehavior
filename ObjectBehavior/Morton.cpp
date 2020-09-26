#include "Morton.h"

Morton::Morton(Object* const self) {
	_self = self;
	for (int i = 0; i < DEPTH; i++) {
		_id[i] = ID;
	}
}

Morton::~Morton() {

}

void Morton::updateMorton() {
	float x = _self->getX();
	float y = _self->getY();
	int id = getOrder(x, y);
	int deep = id % 4;

	_depth = DEPTH - 1;
	if (deep == _id[DEPTH - 1]) { return; }

	_id[DEPTH - 1] = deep;
	_absId = id;
	id >>= 2;
	for (int i = DEPTH - 2; i >= 0; i--, id >>= 2) {
		_id[i] = id % 4;
	}
}

void Morton::drawGrid() {
	for (int i = 1; i < SQUARE; i++) {
		DrawLineAA(.0f, i * DY, winx, i * DY, 0x00ff00);
		DrawLineAA(i * DX, .0f, i * DX, winy, 0x00ff00);
	}
	for (int i = 0; i < SQUARE; i++) {
		for (int j = 0; j < SQUARE; j++) {
			DrawFormatString(
				j * DX, i * DY, 0xffffff, "%4d", 
				getOrder(j * DX, i * DY));
		}
	}
}

int Morton::getUpperShiftCount(int val) {
	if (val == 0) {
		printfDx("morton error\n");
	}

	int c = 0;
	/*int v = 0;
	do {
		v = val % 4;
		val >>= 2;
		c++;
	} while (v == 0);*/
	while (val != 0) {
		val >>= 2;
		c++;
	}

	return c;
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
	while ((v >>= 1) != 0) { res++; }
	return res;
}