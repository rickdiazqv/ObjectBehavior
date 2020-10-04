#include "RectangleMorton.h"
#include "ObjectManager.h"

RectangleMorton::RectangleMorton(Object* self) : Morton(self) {

}

void RectangleMorton::updateMortonParam() {
	updateOldParam();

	RectangleObject* rect = (RectangleObject*)_self;
	float left = rect->getLeft();
	float top = rect->getTop();
	float right = left + rect->getWidth();
	float bottom = top + rect->getHeight();

	updateRectangleMorton(this, left, top, right, bottom);
}

void RectangleMorton::updateRectangleMorton(Morton* const morton, float& left, float& top, float& right, float& bottom) {

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
				}
			}
			if (in[0] < 0) {
				morton->resetMorton(); 
				return;
			}
			if (in[1] < 0) { in[1] = in[0]; }
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

	cur >>= 2 * shift;
	if (depth == morton->getDepth() && cur == morton->getAbsMorton()) { return; }

	morton->setDepth(depth);
	morton->setMorton(cur % 4, depth);
	morton->setAbsMorton(cur);
	cur >>= 2;
	for (int i = depth - 1; i >= 0; i--, cur >>= 2) {
		morton->setMorton(cur % 4, i);
	}
}