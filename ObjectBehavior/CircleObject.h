#pragma once
#include "package.h"
#include "Object.h"

class CircleObject : public Object {
private:
	inline static const float RADIUS = 1.f;

private:
	float _radius = RADIUS;

public:
	float getRadius() {
		return _radius;
	}
};