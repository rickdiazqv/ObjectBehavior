#pragma once
#include "define.h"
#include "Morton.h"

class RectangleMorton : public Morton {
public:
	RectangleMorton(Object* self);

public:
	void updateMortonParam() override;

public:
	static void updateRectangleMorton(Morton* const morton, float left, float top, float right, float bottom);
};