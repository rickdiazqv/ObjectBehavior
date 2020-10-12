#pragma once
#include "package.h"
#include "Object.h"

class CircleObject : public Object {
protected:
	inline static const float RADIUS = 1.f;
	inline static const int POS_NUM = 64;

private:
	inline static const Shape SHAPE = Shape::Circle;

private:
	float _radius = RADIUS;
	float _radSq = _radius * _radius;

public:
	CircleObject(Layer layer, bool pers = false);
	CircleObject(float x, float y, Layer layer, bool pers = false);
	CircleObject(float radius, Layer layer, bool pers = false);
	CircleObject(float x, float y, float radius, Layer layer, bool pers = false);
	~CircleObject();

protected:
	void createMorton() override;

public:
	float getRadius() {
		return _radius;
	}

	float getRadSq() {
		return  _radSq;
	}

public:
	void update() override;
	void draw() override;
};