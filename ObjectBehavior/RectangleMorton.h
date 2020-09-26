#pragma once
#include "define.h"
#include "Morton.h"
#include "RectangleObject.h"

class RectangleMorton : public Morton {
public:
	RectangleMorton(Object* self);

public:
	void updateMorton() override;
};