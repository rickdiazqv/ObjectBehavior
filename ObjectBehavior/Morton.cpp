#include "Morton.h"
#include "Object.h"
#include "ObjectManager.h"
#include "ObjectPlate.h"

Morton::Morton(Object* const self) :
	_plate(ObjectPlate::DEFAULT_PLATE), _self(self) {

	for (int i = 0; i < DEPTH; i++) {
		_id[i] = ID;
		_oldId[i] = _id[i];
	}
}

Morton::~Morton() {

}

void Morton::updateMortonParam() {
	float x = _self->getWorldX();
	float y = _self->getWorldY();
	int id = getOrder(x, y);

	if (id < 0 || ObjectManager::CELL <= id) {
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
	float DX = float(WINDOW_X) / float(SQUARE);
	float DY = float(WINDOW_Y) / float(SQUARE);
	for (int i = 1; i < SQUARE; i++) {
		DrawLineAA(.0f, i * DY, WINDOW_X, i * DY, 0x00ff00);
		DrawLineAA(i * DX, .0f, i * DX, WINDOW_Y, 0x00ff00);
	}
	for (int i = 0; i < SQUARE; i++) {
		for (int j = 0; j < SQUARE; j++) {
			DrawFormatString(
				j * DX, i * DY, 0xffffff, "%4d",
				getOrder(j * DX, i * DY, DX, DY, WINDOW_X, WINDOW_Y));
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
	if (x >= getWidth()) { return X_OVER; }
	if (y < .0f) { return Y_UNDER; }
	if (y >= getHeight()) { return Y_OVER; }

	int cx = int(x / getDX());
	int cy = int(y / getDY());
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

int Morton::getOrder(
	float x, float y, float dx, float dy, float width, float height) {

	if (x < .0f) { return X_UNDER; }
	if (x >= width) { return X_OVER; }
	if (y < .0f) { return Y_UNDER; }
	if (y >= height) { return Y_OVER; }

	int cx = int(x / dx);
	int cy = int(y / dy);
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

inline float Morton::getWidth() { return getPlate()->getWidth(); }
inline float Morton::getHeight() { return getPlate()->getHeight(); }