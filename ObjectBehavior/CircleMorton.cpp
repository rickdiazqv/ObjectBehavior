#include "CircleMorton.h"
#include "CircleObject.h"

CircleMorton::CircleMorton(Object* self) : RectangleMorton(self) {

}

void CircleMorton::updateMortonParam() {
	CircleObject* cir = (CircleObject*)_self;
	float x = cir->getWorldX();
	float y = cir->getWorldY();
	float r = cir->getRadius();

	RectangleMorton::updateRectangleMorton(x - r, y - r, x + r, y + r);
}