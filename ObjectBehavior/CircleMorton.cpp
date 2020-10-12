#include "CircleMorton.h"
#include "RectangleMorton.h"
#include "CircleObject.h"

CircleMorton::CircleMorton(Object* self) : Morton(self) {

}

void CircleMorton::updateMortonParam() {
	CircleObject* cir = (CircleObject*)_self;
	float x = cir->getX();
	float y = cir->getY();
	float r = cir->getRadius();

	RectangleMorton::updateRectangleMorton(this, x - r, y - r, x + r, y + r);
}