#include "ObjectMorton.h"

ObjectMorton::ObjectMorton(Object* self) : Morton(self){

}

void ObjectMorton::updateMortonParam() {
	float x = _self->getWorldX();
	float y = _self->getWorldY();
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