#pragma once
#include "define.h"
#include "Morton.h"
#include "Object.h"

class ObjectMorton : public Morton {
public:
	ObjectMorton(Object* self);

protected:
	void updateMorton() override;
};