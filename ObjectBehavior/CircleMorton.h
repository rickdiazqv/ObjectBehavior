#pragma once
#include "RectangleMorton.h"

class CircleMorton : public RectangleMorton {
public:
	CircleMorton(Object* self);

protected:
	void updateMortonParam() override;
};

