#pragma once
#include "Morton.h"
class CircleMorton : public Morton {
public:
	CircleMorton(Object* self);

public:
	void updateMortonParam() override;
};

