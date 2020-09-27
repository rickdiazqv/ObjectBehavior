#include "RectangleMorton.h"
#include "ObjectManager.h"

RectangleMorton::RectangleMorton(Object* self) : Morton(self) {

}

void RectangleMorton::updateMorton() {
	RectangleObject* rect = (RectangleObject*)_self;
	float left = rect->getLeft();
	float top = rect->getTop();
	float right = left + rect->getWidth();
	float bottom = top + rect->getHeight();
	int id1 = getOrder(left, top);
	int id2 = getOrder(right, bottom);
	int shift = getUpperShiftCount(id1 ^ id2);
	int depth = DEPTH - 1 - shift;

	if (id1 >= ObjectManager::CELL ||
		id2 >= ObjectManager::CELL) {
		return;
	}

	id1 >>= 2 * shift;
	if (depth == _depth && id1 == _absId) { return; }

	_depth = depth;
	_id[_depth] = id1 % 4;
	_absId = id1;
	id1 >>= 2;
	for (int i = _depth - 1; i >= 0; i--, id1 >>= 2) {
		_id[i] = id1 % 4;
	}
}