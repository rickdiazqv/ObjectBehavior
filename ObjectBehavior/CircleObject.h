#pragma once
#include "package.h"
#include "Object.h"

class CircleObject : public Object {
protected:
	inline static const float RADIUS = 1.f;
	inline static const int POS_NUM = 64;

private:
	inline static const Shape SHAPE = Shape::Circle;
	inline static int cirCnt = 0;

private:
	float _radius = RADIUS;
	float _radSq = _radius * _radius;

private:
	const string _id;

public:
	CircleObject(Layer layer, bool pers = false);
	CircleObject(float x, float y, Layer layer, bool pers = false);
	CircleObject(float radius, Layer layer, bool pers = false);
	CircleObject(float x, float y, float radius, Layer layer, bool pers = false);
	~CircleObject();

protected:
	void createMorton() override;

public:
	inline string getId() override { return _id; }
	inline float getRadius() { return _radius; }
	inline float getRadSq() { return  _radSq; }

public:
	void update() override;
	void draw() override;
};