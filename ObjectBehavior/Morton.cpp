#include "Morton.h"
#include "Object.h"
#include "ObjectManager.h"

Morton::Morton(Object* const self) : _self(self) {
	for (int i = 0; i < DEPTH; i++) {
		_id[i] = ID;
		_oldId[i] = _id[i];
	}
}

Morton::~Morton() {

}

void Morton::updateMortonParam() {
	updateOldParam();

	float x = _self->getX();
	float y = _self->getY();
	int id = getOrder(x, y);

	if ( id < 0 || ObjectManager::CELL <= id) {
		resetMorton();
		return;
	}

	_depth = DEPTH - 1;
	if (id == _absId) { return; }

	_id[DEPTH - 1] = id % 4;
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
	int c = 0;
	while (val != 0) {
		val >>= 2;
		c++;
	}

	return c;
}

int Morton::getOrder(float x, float y) {
	if (x < .0f) { return X_UNDER; }
	if (x >= (int)winx) { return X_OVER; }
	if (y < .0f) { return Y_UNDER; }
	if (y >= (int)winy) { return Y_OVER; }

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