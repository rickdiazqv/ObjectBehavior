#pragma once
#include "define.h"
#include "Object.h"
#include "ObjectPlate.h"

class Camera : public Object {
private:
	inline static const int PROC_PRIORITY = 4;
	inline static const int DRAW_PRIORITY = 4;

private:
	ObjectPlate* const _plate = nullptr;

public:
	Camera(float x, float y, ObjectPlate* plate);
	~Camera();
};