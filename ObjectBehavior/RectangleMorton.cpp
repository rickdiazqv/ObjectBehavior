#include "RectangleMorton.h"


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
	//0011
	//1001
	//1010

	_depth = DEPTH - 1 - shift;
	id1 >>= 2 * shift;
	for (int i = _depth; i >= 0; i--, id1 >>= 2) {
		_id[i] = id1 % 4;
	}
}