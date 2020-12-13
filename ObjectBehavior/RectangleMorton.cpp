#include "RectangleMorton.h"
#include "RectangleObject.h"
#include "ObjectManager.h"

RectangleMorton::RectangleMorton(Object* self) : Morton(self) {

}

void RectangleMorton::updateMortonParam() {
	RectangleObject* rect = (RectangleObject*)_self;
	float left = rect->getWorldLeft();
	float top = rect->getWorldTop();
	float right = left + rect->getWidth();
	float bottom = top + rect->getHeight();

	updateRectangleMorton(left, top, right, bottom);
}

void RectangleMorton::updateRectangleMorton(
	float left, float top, float right, float bottom) {

	float right_limit = getWidth() - 1.f;
	float bottom_limit = getHeight() - 1.f;
	int in_idx[2];
	int in_diagonal[2][2][2] = {
		{{right_limit, bottom_limit}, {.0f, bottom_limit}},
		{{right_limit, .0f}, {.0f, .0f}},
	};

	int in[2] = { -1, -1 };
	int id[2][2];
	id[0][0] = getOrder(left, top);
	id[1][1] = getOrder(right, bottom);

	bool out[2][2];
	out[0][0] = id[0][0] < 0 ||
		ObjectManager::CELL <= id[0][0];
	out[1][1] = id[1][1] < 0 ||
		ObjectManager::CELL <= id[1][1];
	if (out[0][0] || out[1][1]) {
		id[1][0] = getOrder(left, bottom);
		id[0][1] = getOrder(right, top);
		out[1][0] = id[1][0] < 0 || ObjectManager::CELL <= id[1][0];
		out[0][1] = id[0][1] < 0 || ObjectManager::CELL <= id[0][1];

		if (out[1][0] || out[0][1]) {
			int c = 0;
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					if (out[i][j]) { continue; }
					in[c++] = id[i][j];
					in_idx[0] = i, in_idx[1] = j;
				}
			}
			if (in[0] < 0) {
				resetMorton();
				return;
			}
			if (in[1] < 0) {
				int i = in_idx[0], j = in_idx[1];
				in[1] = getOrder(
					in_diagonal[i][j][0],
					in_diagonal[i][j][1]);
			}
		}
		else {
			in[0] = id[1][0];
			in[1] = id[0][1];
		}
	}
	else {
		in[0] = id[0][0];
		in[1] = id[1][1];
	}
	int shift = getUpperShiftCount(in[0] ^ in[1]);
	int depth = DEPTH - 1 - shift;
	int cur = in[0];

	cur >>= (2 * shift);
	if (depth == getDepth() && cur == getAbsMorton()) { return; }

	setDepth(depth);
	setMorton(cur % 4, depth);
	setAbsMorton(cur);
	cur >>= 2;
	for (int i = depth - 1; i >= 0; i--, cur >>= 2) {
		setMorton(cur % 4, i);
	}
}