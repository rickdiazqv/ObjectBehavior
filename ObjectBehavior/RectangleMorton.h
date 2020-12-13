#pragma once
#include "define.h"
#include "Morton.h"

class RectangleMorton : public Morton {
public:
	RectangleMorton(Object* self);

protected:
	void updateMortonParam() override;

protected:
	void updateRectangleMorton(
		float left, float top, float right, float bottom);
};