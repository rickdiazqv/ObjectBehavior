#pragma once
#include "define.h"
#include "Object.h"

class PlaneObject : public Object {
private:
	inline static const Shape SHAPE = Shape::Circle;

public:
	PlaneObject();
	~PlaneObject();

public:
	void update() override;
	void draw() override;
};
